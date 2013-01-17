#ifndef _OPTION_H_
#define _OPTION_H_

#include <string>
#include "worldfile.hh"

#include <QCheckBox>

namespace Stg {
	class World;
	/** option.hh
	 Class that encapsulates a boolean and pairs it with a string description
	 Used to pass settings between the GUI and the drawing classes
	 
	 Author: Jeremy Asher, Richard Vaughan
	 SVN: $Id$
	 */	
        class Option : public QCheckBox {

	public:
                Option();

                Option(const std::string& tok, bool v);
                inline bool val() const { return value; }
                inline operator bool() { return val(); }
		void Load( Worldfile* wf, int section );
                void Save( Worldfile* wf, int section );

        private:
                std::string wf_token;
                bool value;
	};
}
	
#endif
