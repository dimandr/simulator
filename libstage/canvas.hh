#include <stack>

#include "stage.hh"
#include "option.hh"
#include "../qtlogo.h"
namespace Stg
{
  class Canvas  : public QGLWidget
  {
      Q_OBJECT
         friend class WorldGui; // allow access to private members
         friend class Model;

  private:

         class GlColorStack
         {
         public:
                GlColorStack() : colorstack() {}
                ~GlColorStack() {}

                void Push( double r, double g, double b, double a=1.0 )
                {
                  Push( Color(r,g,b,a) );
                }

                void Push( Color col )
                {
                  colorstack.push( col );
                  glColor4f( col.r, col.g, col.b, col.a );
                }

                void Pop()
                {
                  if( colorstack.size() < 1 )
                         PRINT_WARN1( "Attempted to ColorStack.Pop() but ColorStack %p is empty",
                                                          this );
                  else
                         {
                                Color& old = colorstack.top();
                                colorstack.pop();
                                glColor4f( old.r, old.g, old.b, old.a );
                         }
                }

                unsigned int Length()
                { return colorstack.size(); }

         private:
                std::stack<Color> colorstack;
         } colorstack;

         std::list<Model*> models_sorted;

         Camera* current_camera;
         OrthoCamera camera;
         PerspectiveCamera perspective_camera;
         bool dirty_buffer;
         Worldfile* wf;

         bool _isValid;

         int startx, starty;
         bool selectedModel;
         bool clicked_empty_space;
         int empty_space_startx, empty_space_starty;
         std::list<Model*> selected_models;
         Model* last_selection; ///< the most recently selected model
         ///(even if it is now unselected).

         msec_t interval; // window refresh interval in ms

         void RecordRay( double x1, double y1, double x2, double y2 );
         void DrawRays();
         void ClearRays();
         void DrawGlobalGrid();

         void AddModel( Model* mod );
         void RemoveModel( Model* mod );

         Option //showBlinken,
                showBBoxes,
                showBlocks,
                showBlur,
                showClock,
                showData,
                showFlags,
                showFollow,
                showFootprints,
                showGrid,
                showOccupancy,
                showScreenshots,
                showStatus,
                showTrailArrows,
                showTrailRise,
                showTrails,
                showVoxels,
                pCamOn,
                visualizeAll;

  public:
         Canvas( WorldGui* world, int x, int y, int width, int height,QWidget *parent = 0);
         ~Canvas();

         bool graphics;
         WorldGui* world;
         unsigned long frames_rendered_count;
         int screenshot_frame_skip;

//         std::map< std::string, Option* > _custom_options;

         void Screenshot();
         void InitTextures();
//	 void createMenuItems( Fl_Menu_Bar* menu, std::string path );

         void FixViewport(int W,int H);
         void DrawFloor(); //simpler floor compared to grid
         void DrawBlocks();
         void DrawBoundingBoxes();
         void resetCamera();
         virtual void renderFrame();
         void CanvasToWorld( int px, int py, double *wx, double *wy, double* wz );

         Model* getModel( int x, int y );
         bool selected( Model* mod );
         void select( Model* mod );
         void unSelect( Model* mod );
         void unSelectAll();

         inline void setDirtyBuffer( void ) { dirty_buffer = true; }
         inline bool dirtyBuffer( void ) const { return dirty_buffer; }

         void PushColor( Color col )
         { colorstack.Push( col ); }

         void PushColor( double r, double g, double b, double a )
         { colorstack.Push( r,g,b,a ); }

         void PopColor(){ colorstack.Pop(); }

         void InvertView( uint32_t invertflags );

         //bool VisualizeAll(){ return ! visualizeAll; }

        //	 static void perspectiveCb( Fl_Widget* w, void* p );

         void EnterScreenCS();
         void LeaveScreenCS();

         void createMenuItems( QMenu* menu);

         void Load( Worldfile* wf, int section );
         void Save( Worldfile* wf, int section );

         bool IsTopView(){ return( (fabs( camera.yaw() ) < 0.1) && (fabs( camera.pitch() ) < 0.1) ); }
  protected:
      void initializeGL();
      void paintGL();
      void resizeGL(int width, int height);
      void mousePressEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *event);
      void wheelEvent(QWheelEvent *event);

  public slots:
      void TimerCallback( );
  };

} // namespace Stg
