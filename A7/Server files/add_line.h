#ifndef _ADD_LINE_
#define _ADD_LINE_

#include "change_line.h"

using namespace std;

class AddLine : public ChangeLine  {
public:
    AddLine( int _lineNum ) : ChangeLine(_lineNum) {};
    changeType getType() { return _AddLine_; }
private:
};

#endif /* _ADD_LINE_ */
