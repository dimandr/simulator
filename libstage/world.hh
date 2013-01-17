#ifndef WORLD_HH
#define WORLD_HH

/// %World class
class World : public Ancestor
{
public:
  friend class Block;
  friend class Model; // allow access to private members
  friend class ModelFiducial;
  friend class Canvas;
  friend class WorkerThread;

public:
  /** contains the command line arguments passed to Stg::Init(), so
      that controllers can read them. */
  static std::vector<std::string> args;
  static std::string ctrlargs;

private:

  static std::set<World*> world_set; ///< all the worlds that exist
  static bool quit_all; ///< quit all worlds ASAP
  static void UpdateCb( World* world);
  static unsigned int next_id; ///<initially zero, used to allocate unique sequential world ids

  bool destroy;
  bool dirty; ///< iff true, a gui redraw would be required

  /** Pointers to all the models in this world. */
  std::set<Model*> models;

  /** pointers to the models that make up the world, indexed by name. */
  std::map<std::string, Model*> models_by_name;

  /** pointers to the models that make up the world, indexed by worldfile entry index */
  std::map<int,Model*> models_by_wfentity;

  /** Keep a list of all models with detectable fiducials. This
      avoids searching the whole world for fiducials. */
  std::vector<Model*> models_with_fiducials;

  struct ltx
  {
    bool operator()(const Model* a, const Model* b) const;
  };

  struct lty
  {
    bool operator()(const Model* a, const Model* b) const;
  };

  /** maintain a set of models with fiducials sorted by pose.x, for
      quickly finding nearby fidcucials */
  std::set<Model*,ltx> models_with_fiducials_byx;

  /** maintain a set of models with fiducials sorted by pose.y, for
      quickly finding nearby fidcucials */
  std::set<Model*,lty> models_with_fiducials_byy;

  /** Add a model to the set of models with non-zero fiducials, if not already there. */
  void FiducialInsert( Model* mod )
  {
    FiducialErase( mod ); // make sure it's not there already
    models_with_fiducials.push_back( mod );
  }

  /** Remove a model from the set of models with non-zero fiducials, if it exists. */
  void FiducialErase( Model* mod )
  {
    EraseAll( mod, models_with_fiducials );
  }

  double ppm; ///< the resolution of the world model in pixels per meter
  bool quit; ///< quit this world ASAP
  bool show_clock; ///< iff true, print the sim time on stdout
  unsigned int show_clock_interval; ///< updates between clock outputs

  //--- thread sync ----
  pthread_mutex_t sync_mutex; ///< protect the worker thread management stuff
  unsigned int threads_working; ///< the number of worker threads not yet finished
  pthread_cond_t threads_start_cond; ///< signalled to unblock worker threads
  pthread_cond_t threads_done_cond; ///< signalled by last worker thread to unblock main thread
  int total_subs; ///< the total number of subscriptions to all models
  unsigned int worker_threads; ///< the number of worker threads to use

protected:

  std::list<std::pair<world_callback_t,void*> > cb_list; ///< List of callback functions and arguments
  bounds3d_t extent; ///< Describes the 3D volume of the world
  bool graphics;///< true iff we have a GUI

  //std::set<Option*> option_table; ///< GUI options (toggles) registered by models
  std::list<PowerPack*> powerpack_list; ///< List of all the powerpacks attached to models in the world
  /** World::quit is set true when this simulation time is reached */
  usec_t quit_time;
  std::list<float*> ray_list;///< List of rays traced for debug visualization
  usec_t sim_time; ///< the current sim time in this world in microseconds
  std::map<point_int_t,SuperRegion*> superregions;

  uint64_t updates; ///< the number of simulated time steps executed so far
  Worldfile* wf; ///< If set, points to the worldfile used to create this world

  void CallUpdateCallbacks(); ///< Call all calbacks in cb_list, removing any that return true;

public:

  uint64_t UpdateCount(){ return updates; }

  bool paused; ///< if true, the simulation is stopped

  virtual void Start(){ paused = false; };
  virtual void Stop(){ paused = true; };
  virtual void TogglePause(){ paused ? Start() : Stop(); };

  bool Paused() const { return( paused ); };

  /** Force the GUI to redraw the world, even if paused. This
      imlementation does nothing, but can be overridden by
      subclasses. */
  virtual void Redraw( void ){ }; // does nothing

  std::vector<point_int_t> rt_cells;
  std::vector<point_int_t> rt_candidate_cells;

  static const int DEFAULT_PPM = 50;  // default resolution in pixels per meter

  /** Attach a callback function, to be called with the argument at
      the end of a complete update step */
  void AddUpdateCallback( world_callback_t cb, void* user );

  /** Remove a callback function. Any argument data passed to
      AddUpdateCallback is not automatically freed. */
  int RemoveUpdateCallback( world_callback_t cb, void* user );

  /** Log the state of a Model */
  void Log( Model* mod );

  /** hint that the world needs to be redrawn if a GUI is attached */
  void NeedRedraw(){ dirty = true; };

  /** Special model for the floor of the world */
  Model* ground;

  /** Get human readable string that describes the current simulation
      time. */
  virtual std::string ClockString( void ) const;

  Model* CreateModel( Model* parent, const std::string& typestr );

  void LoadModel(      Worldfile* wf, int entity );
  void LoadBlock(      Worldfile* wf, int entity );
  void LoadBlockGroup( Worldfile* wf, int entity );
  void LoadSensor(     Worldfile* wf, int entity );

  virtual Model* RecentlySelectedModel() const { return NULL; }

  /** Add the block to every raytrace bitmap cell that intersects
      the edges of the polygon.*/
  void MapPoly( const std::vector<point_int_t>& poly,
                Block* block,
                unsigned int layer );

  SuperRegion* AddSuperRegion( const point_int_t& coord );
  SuperRegion* GetSuperRegion( const point_int_t& org );
  SuperRegion* GetSuperRegionCreate( const point_int_t& org );

  /** convert a distance in meters to a distance in world occupancy
      grid pixels */
  int32_t MetersToPixels( meters_t x ) const
  { return (int32_t)floor(x * ppm); };

  /** Return the bitmap coordinates corresponding to the location in meters. */
  point_int_t MetersToPixels( const point_t& pt ) const
  { return point_int_t( MetersToPixels(pt.x), MetersToPixels(pt.y)); };

  // dummy implementations to be overloaded by GUI subclasses
  virtual void PushColor( Color col )
  { /* do nothing */  (void)col; };
  virtual void PushColor( double r, double g, double b, double a )
  { /* do nothing */ (void)r; (void)g; (void)b; (void)a; };

  virtual void PopColor(){ /* do nothing */  };

  SuperRegion* CreateSuperRegion( point_int_t origin );
  void DestroySuperRegion( SuperRegion* sr );

  /** trace a ray. */
  RaytraceResult Raytrace( const Ray& ray );

  RaytraceResult Raytrace( const Pose& pose,
                           const meters_t range,
                           const ray_test_func_t func,
                           const Model* finder,
                           const void* arg,
                           const bool ztest );

  void Raytrace( const Pose &gpose, // global pose
                 const meters_t range,
                 const radians_t fov,
                 const ray_test_func_t func,
                 const Model* model,
                 const void* arg,
                 const bool ztest,
                 std::vector<RaytraceResult>& results );

  /** Enlarge the bounding volume to include this point */
  inline void Extend( point3_t pt );

  virtual void AddModel( Model* mod );
  virtual void RemoveModel( Model* mod );

  void AddModelName( Model* mod, const std::string& name );

  void AddPowerPack( PowerPack* pp );
  void RemovePowerPack( PowerPack* pp );

  void ClearRays();

  /** store rays traced for debugging purposes */
  void RecordRay( double x1, double y1, double x2, double y2 );

  /** Returns true iff the current time is greater than the time we
      should quit */
  bool PastQuitTime();

  static void* update_thread_entry( std::pair<World*,int>* info );

  class Event
  {
  public:

    Event( usec_t time, Model* mod, model_callback_t cb, void* arg )
      : time(time), mod(mod), cb(cb), arg(arg) {}

    usec_t time; ///< time that event occurs
    Model* mod; ///< model to pass into callback
    model_callback_t cb;
    void* arg;

    /** order by time. Break ties by value of Model*, then cb*.
        @param event to compare with this one. */
    bool operator<( const Event& other ) const;
  };

  /** Queue of pending simulation events for the main thread to handle. */
  std::vector<std::priority_queue<Event> > event_queues;

  /** Queue of pending simulation events for the main thread to handle. */
  std::vector<std::queue<Model*> > pending_update_callbacks;

  /** Create a new simulation event to be handled in the future.

      @param queue_num Specify which queue the event should be on. The main
      thread is 0.

      @param delay The time from now until the event occurs, in
      microseconds.

      @param mod The model that should have its Update() method
      called at the specified time.
  */
  void Enqueue( unsigned int queue_num, usec_t delay, Model* mod, model_callback_t cb, void* arg )
  {  event_queues[queue_num].push( Event( sim_time + delay, mod, cb, arg ) ); }

  /** Set of models that require energy calculations at each World::Update(). */
  std::set<Model*> active_energy;
  void EnableEnergy( Model* m ) { active_energy.insert( m ); };
  void DisableEnergy( Model* m ) { active_energy.erase( m ); };

  /** Set of models that require their positions to be recalculated at each World::Update(). */
  std::set<ModelPosition*> active_velocity;

  /** The amount of simulated time to run for each call to Update() */
  usec_t sim_interval;

  // debug instrumentation - making sure the number of update callbacks
  // in each thread is consistent with the number that have been
  // registered globally
  int update_cb_count;

  /** consume events from the queue up to and including the current sim_time */
  void ConsumeQueue( unsigned int queue_num );

  /** returns an event queue index number for a model to use for
      updates */
  unsigned int GetEventQueue( Model* mod ) const;

public:
  /** returns true when time to quit, false otherwise */
  static bool UpdateAll();

/** run all worlds.
 *  If only non-gui worlds were created, UpdateAll() is
 *  repeatedly called.
 *  To simulate a gui world only a single gui world may
 *  have been created. This world is then simulated.
 */
static void Run();

  World( const std::string& name = "MyWorld",
         double ppm = DEFAULT_PPM );

  virtual ~World();

  /** Returns the current simulated time in this world, in microseconds. */
  usec_t SimTimeNow(void) const { return sim_time; }

  /** Returns a pointer to the currently-open worlddfile object, or
      NULL if there is none. */
  Worldfile* GetWorldFile()	{ return wf; };

  /** Returns true iff this World implements a GUI. The base World
      class returns false, but subclasses can override this
      behaviour. */
  virtual bool IsGUI() const { return false; }

  /** Open the file at the specified location, create a Worldfile
      object, read the file and configure the world from the
      contents, creating models as necessary. The created object
      persists, and can be retrieved later with
      World::GetWorldFile(). */
  virtual void Load( const std::string& worldfile_path );

  virtual void UnLoad();

  virtual void Reload();

  /** Save the current world state into a worldfile with the given
      filename.  @param Filename to save as. */
  virtual bool Save( const char* filename );

  /** Run one simulation timestep. Advances the simulation clock,
      executes all simulation updates due at the current time, then
      queues up future events. */
  virtual bool Update(void);

  /** Returns true iff either the local or global quit flag was set,
      which usually happens because someone called Quit() or
      QuitAll(). */
  bool TestQuit() const { return( quit || quit_all );  }

  /** Request the world quits simulation before the next timestep. */
  void Quit(){ quit = true; }

  /** Requests all worlds quit simulation before the next timestep. */
  void QuitAll(){ quit_all = true; }

  /** Cancel a local quit request. */
  void CancelQuit(){ quit = false; }

  /** Cancel a global quit request. */
  void CancelQuitAll(){ quit_all = false; }

  void TryCharge( PowerPack* pp, const Pose& pose );

  /** Get the resolution in pixels-per-metre of the underlying
      discrete raytracing model */
  double Resolution() const { return ppm; };

  /** Returns a pointer to the model identified by name, or NULL if
      nonexistent */
  Model* GetModel( const std::string& name ) const;

  /** Returns a const reference to the set of models in the world. */
  const std::set<Model*> GetAllModels() const { return models; };

  /** Return the 3D bounding box of the world, in meters */
  const bounds3d_t& GetExtent() const { return extent; };

  /** Return the number of times the world has been updated. */
  uint64_t GetUpdateCount() const { return updates; }

  /// Register an Option for pickup by the GUI
  void RegisterOption( Option* opt );

  /// Control printing time to stdout
  void ShowClock( bool enable ){ show_clock = enable; };

  /** Return the floor model */
  Model* GetGround() {return ground;};

};

#endif // WORLD_HH
