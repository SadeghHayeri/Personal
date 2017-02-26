#ifndef _DELETE_LINE_
#define _DELETE_LINE_

#include "change_line.h"

using namespace std;

class DeleteLine : public ChangeLine {
public:
    DeleteLine( int _lineNum ) : ChangeLine(_lineNum) {};
    changeType getType() { return _DeleteLine_; }
private:
};

#endif /* _DELETE_LINE_ */
