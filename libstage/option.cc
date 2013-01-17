
#include "stage.hh"
#include "worldfile.hh"
#include "option.hh"
#include "canvas.hh"
using namespace Stg;


Option::Option()
{ 
  /* do nothing */ 
}

Option::Option(const std::string& tok, bool v)
    :
      wf_token( tok ),
      value(v)
{
  /* do nothing */
}

void Option::Load( Worldfile* wf, int section )
{
  //printf( "loading wf key %s\n", wf_token.c_str() );
  this->setChecked((bool)wf->ReadInt( section, wf_token.c_str(), value ));
}

void Option::Save( Worldfile* wf, int section )
{
  wf->WriteInt(section, wf_token.c_str(), value );
}

