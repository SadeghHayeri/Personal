#ifndef _EDIT_LINE_
#define _EDIT_LINE_

#include <string>
#include "change_line.h"

using namespace std;

class EditLine : public ChangeLine  {
public:
    EditLine( int _lineNum, string _lineText ) : ChangeLine(_lineNum), lineText(_lineText) {};
    changeType getType() { return _EditLine_; }
    string getText() { return lineText; }
private:
    string lineText;
};

#endif /* _EDIT_LINE_ */
