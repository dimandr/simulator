#ifndef BLOCK_HH
#define BLOCK_HH

class Block
{
  friend class BlockGroup;
  friend class Model;
  friend class SuperRegion;
  friend class World;
  friend class Canvas;
  friend class Cell;
public:

  /** Block Constructor. A model's body is a list of these
      blocks. The point data is copied, so pts can safely be freed
      after constructing the block.*/
  Block( BlockGroup* group,
         const std::vector<point_t>& pts,
         const Bounds& zrange );

  /** A from-file  constructor */
  Block( BlockGroup* group, Worldfile* wf, int entity);

  ~Block();

  /** render the block into the world's raytrace data structure */
  void Map( unsigned int layer );

  /** remove the block from the world's raytracing data structure */
  void UnMap( unsigned int layer );

  /** draw the block in OpenGL as a solid single color */
  void DrawSolid(bool topview);

  /** draw the projection of the block onto the z=0 plane	*/
  void DrawFootPrint();

  /** Translate all points in the block by the indicated amounts */
  void Translate( double x, double y );

  /** Return the center of the block on the X axis */
  double CenterX();

  /** Return the center of the block on the Y axis */
  double CenterY();

  /** Set the center of the block on the X axis */
  void SetCenterX( double y );

  /** Set the center of the block on the Y axis */
  void SetCenterY( double y );

  /** Set the center of the block */
  void SetCenter( double x, double y);

  /** Set the extent in Z of the block */
  void SetZ( double min, double max );

  void AppendTouchingModels( std::set<Model*>& touchers );

  /** Returns the first model that shares a bitmap cell with this model */
  Model* TestCollision();

  void Load( Worldfile* wf, int entity );

  void Rasterize( uint8_t* data,
                  unsigned int width, unsigned int height,
                  meters_t cellwidth, meters_t cellheight );

  BlockGroup* group; ///< The BlockGroup to which this Block belongs.
private:
  std::vector<point_t> pts; ///< points defining a polygon.
  Bounds local_z; ///<  z extent in local coords.
  Bounds global_z; ///< z extent in global coordinates.

  /** record the cells into which this block has been rendered so we
      can remove them very quickly. One vector for each of the two
      bitmap layers.*/
  std::vector<Cell*> rendered_cells[2];

  void DrawTop();
  void DrawSides();
};

#endif // BLOCK_HH
