/**
  \defgroup stage The Stage standalone robot simulator.

  USAGE:  stage [options] <worldfile1> [worldfile2 ... ]

  Available [options] are:

    --clock        : print simulation time peridically on standard output

    -c             : equivalent to --clock

    --gui          : run without a GUI

    -g             : equivalent to --gui

    --help         : print this message

    --args \"str\"   : define an argument string to be passed to all controllers

    -a \"str\"       : equivalent to --args "str"

    -h             : equivalent to --help"

    -?             : equivalent to --help
 */

#include <getopt.h>
#include <QtGui/QApplication>
#include "interfaceWindow.h"


#include "libstage/stage.hh"
using namespace Stg;

/*
*/
int main( int argc, char* argv[] )
{
  QApplication app(argc, argv);
  QTextCodec::setCodecForTr( QTextCodec::codecForName("utf8") );
  Stg::Init( &argc, &argv );

  interfaceWindow window;

#if defined(Q_OS_SYMBIAN)
  window.showMaximized();
#else
  window.show();
#endif

return app.exec();
}
