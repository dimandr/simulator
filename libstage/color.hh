#ifndef COLOR_HH
#define COLOR_HH

#include <QtOpenGL>
#include <QColor>

#include "libstage/worldfile.hh"

class Color
{

public:
  double r,g,b,a;

  Color();

  Color( double r, double g, double b, double a=1.0 );
/*
  Color( const std::string& name );


  bool operator!=( const Color& other ) const;
  bool operator==( const Color& other ) const;
*/
  static Color RandomColor();
  void Print( const char* prefix ) const;

  /** convenient constants */
 // static const Color blue, red, green, yellow, magenta, cyan;

  const Color& Load( Worldfile* wf, int entity );

  void GLSet( void ) { glColor4f( r,g,b,a ); }
};

#endif // COLOR_HH
