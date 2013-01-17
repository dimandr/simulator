#ifndef GL_HH
#define GL_HH

/** Convenient OpenGL drawing routines, used by visualization
    code. */
namespace Gl
{
  void pose_shift( const Pose &pose );
  void pose_inverse_shift( const Pose &pose );
  void coord_shift( double x, double y, double z, double a  );
  void draw_grid( bounds3d_t vol );
  /** Render a string at [x,y,z] in the current color */
  void draw_string( float x, float y, float z, const char *string);
  void draw_string_multiline( float x, float y, float w, float h,
                              const char *string, Fl_Align align );
  void draw_speech_bubble( float x, float y, float z, const char* str );
  void draw_octagon( float w, float h, float m );
  void draw_octagon( float x, float y, float w, float h, float m );
  void draw_vector( double x, double y, double z );
  void draw_origin( double len );
  void draw_array( float x, float y, float w, float h,
                   float* data, size_t len, size_t offset,
                   float min, float max );
  void draw_array( float x, float y, float w, float h,
                   float* data, size_t len, size_t offset );
  /** Draws a rectangle with center at x,y, with sides of length dx,dy */
  void draw_centered_rect( float x, float y, float dx, float dy );
} // namespace Gl

#endif // GL_HH
