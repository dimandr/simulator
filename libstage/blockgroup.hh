#ifndef BLOCKGROUP_HH
#define BLOCKGROUP_HH

class BlockGroup
{
  friend class Model;
  friend class Block;
  friend class World;
  friend class SuperRegion;

private:
  std::vector<Block> blocks; ///< Contains the blocks in this group.
  int displaylist; ///< OpenGL displaylist that renders this blockgroup.

public:    Model& mod;

private:
  void AppendBlock( const Block& block );

  void CalcSize();
  void Clear() ; /** deletes all blocks from the group */

  void AppendTouchingModels( std::set<Model*>& touchers );

  /** Returns a pointer to the first model detected to be colliding
      with a block in this group, or NULL, if none are detected. */
  Model* TestCollision();

  /** Renders all blocks into the bitmap at the indicated layer.*/
  void Map( unsigned int layer );
  /** Removes all blocks from the bitmap at the indicated layer.*/
  void UnMap( unsigned int layer );

  /** Interpret the bitmap file as a set of rectangles and add them
      as blocks to this group.*/
  void LoadBitmap( const std::string& bitmapfile, Worldfile *wf );

  /** Add a new block decribed by a worldfile entry. */
  void LoadBlock( Worldfile* wf, int entity );

  /** Render the blockgroup as a bitmap image. */
  void Rasterize( uint8_t* data,
                  unsigned int width, unsigned int height,
                  meters_t cellwidth, meters_t cellheight );

  /** Draw the block in OpenGL as a solid single color. */
  void DrawSolid( const Geom &geom);

  /** Re-create the display list for drawing this blockgroup. This
      is required whenever a member block or the owning model
      changes its appearance.*/
  void BuildDisplayList();

  /** Draw the blockgroup from the cached displaylist. */
  void CallDisplayList();

public:
  BlockGroup( Model& mod );
  ~BlockGroup();

  uint32_t GetCount() const { return blocks.size(); };
  const Block& GetBlock( unsigned int index ) const { return blocks[index]; };
  Block& GetBlockMutable( unsigned int index ) { return blocks[index]; };

  /** Return the extremal points of all member blocks in all three axes. */
  bounds3d_t BoundingBox() const;

  /** Draw the projection of the block group onto the z=0 plane. */
  void DrawFootPrint( const Geom &geom);
};

#endif // BLOCKGROUP_HH
