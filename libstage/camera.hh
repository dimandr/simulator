#include "libstage/worldfile.hh"

#ifndef CAMERA_HH
#define CAMERA_HH

/** convert an angle in degrees to radians. */
inline double dtor( double d ){ return( d*M_PI/180.0 ); }

class Camera
{
public:
  double _pitch; //left-right (about y)
  double _yaw; //up-down (about x)
  int _x, _y, _z;

public:
  Camera() : _pitch( 0 ), _yaw( 0 ), _x( 0 ), _y( 0 ), _z( 0 ) { }
  virtual ~Camera() { }

  virtual void Draw( void ) const = 0;
  virtual void SetProjection( void ) const = 0;

  double yaw( void ) const { return _yaw; }
  double pitch( void ) const { return _pitch; }

  double x( void ) const { return _x; }
  double y( void ) const { return _y; }
  double z( void ) const { return _z; }

  virtual void reset() = 0;
  virtual void Load( Worldfile* wf, int sec ) = 0;

  //TODO data should be passed in somehow else. (at least min/max stuff)
  //virtual void SetProjection( float pixels_width, float pixels_height, float y_min, float y_max ) const = 0;
};

class PerspectiveCamera : public Camera
{
private:
  double _z_near;
  double _z_far;
  double _vert_fov;
  double _horiz_fov;
  double _aspect;

public:
  PerspectiveCamera( void );

  virtual void Draw( void ) const;
  virtual void SetProjection( void ) const;
  //void SetProjection( double aspect ) const;
  void update( void );

  void strafe( double amount );
  void forward( double amount );

  void setPose( double x, double y, double z ) { _x = x; _y = y; _z = z; }
  void addPose( double x, double y, double z ) { _x += x; _y += y; _z += z; if( _z < 0.1 ) _z = 0.1; }
  void move( double x, double y, double z );
  void setFov( double horiz_fov, double vert_fov ) { _horiz_fov = horiz_fov; _vert_fov = vert_fov; }
  ///update vertical fov based on window aspect and current horizontal fov
  void setAspect( double aspect ) { _aspect = aspect; }
  void setYaw( double yaw ) { _yaw = yaw; }
  double horizFov( void ) const { return _horiz_fov; }
  double vertFov( void ) const { return _vert_fov; }
  void addYaw( double yaw ) { _yaw += yaw; }
  void setPitch( double pitch ) { _pitch = pitch; }
  void addPitch( double pitch ) { _pitch += pitch; if( _pitch < 0 ) _pitch = 0; else if( _pitch > 180 ) _pitch = 180; }

  double realDistance( double z_buf_val ) const {
    return _z_near * _z_far / ( _z_far - z_buf_val * ( _z_far - _z_near ) );
  }
  void scroll( double dy ) { _z += dy; }
  double nearClip( void ) const { return _z_near; }
  double farClip( void ) const { return _z_far; }
  void setClip( double near, double far ) { _z_far = far; _z_near = near; }

  void reset() { setPitch( 70 ); setYaw( 0 ); }

  void Load( Worldfile* wf, int sec );
  void Save( Worldfile* wf, int sec );
};

class OrthoCamera : public Camera
{
private:
  double _scale;
  double _pixels_width;
  double _pixels_height;
  double _y_min;
  double _y_max;

public:
  OrthoCamera( void ) :
              _scale( 15 ),
              _pixels_width(0),
              _pixels_height(0),
              _y_min(0),
              _y_max(0)
       { }

  virtual void Draw() const;

  virtual void SetProjection( double pixels_width,
                                                                                double pixels_height,
                                                                                double y_min,
                                                                                double y_max );

  virtual void SetProjection( void ) const;

  void move( double x, double y );

  void setYaw( double yaw ) { _yaw = yaw;	}

  void setPitch( double pitch ) { _pitch = pitch; }

  void addYaw( double yaw ) { _yaw += yaw;	}

  void addPitch( double pitch ) {
    _pitch += pitch;
    if( _pitch > 90 )
      _pitch = 90;
    else if( _pitch < 0 )
      _pitch = 0;
  }

  void setScale( double scale ) { _scale = scale; }
  void setPose( double x, double y) { _x = x; _y = y; }

  void scale( double scale, double shift_x = 0, double h = 0, double shift_y = 0, double w = 0 );
  void reset( void ) { _pitch = _yaw = 0; }

  double scale() const { return _scale; }

  void Load( Worldfile* wf, int sec );
  void Save( Worldfile* wf, int sec );
};

#endif // CAMERA_HH
