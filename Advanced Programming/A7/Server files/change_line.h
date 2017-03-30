#ifndef _CHANGE_LINE_
#define _CHANGE_LINE_

using namespace std;

enum changeType { _AddLine_, _EditLine_, _DeleteLine_ };

class ChangeLine {
public:
    ChangeLine( int _lineNum ) : lineNum(_lineNum) {};
    int getLineNum() { return lineNum; }
    virtual changeType getType() = 0;
protected:
    int lineNum;
};

#endif /* _CHANGE_LINE_ */
