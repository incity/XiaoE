#ifndef DIALPAD_STATUS_ACTIVITY_H
#define DIALPAD_STATUS_ACTIVITY_H

#include "macros.h"
#include "StatusActivity.h"

class DialpadStatusActivity : public StatusActivity
{
// 1. public members
public:
    // 1.1. typedefs
    // 1.2. nested enums    
    enum {
        ID_BUTTON_MAIN = StatusActivity::ID_END,
        ID_DIALPAD,
        ID_END
    };
    // 1.3. nested structs
    // 1.4. nested classes
    // 1.5. consts
    // 1.6. constructors
    DialpadStatusActivity();
    // 1.7. destructors
    ~DialpadStatusActivity();
    // 1.8. member functions
    // 1.9. member variables

// 2. protected members 
protected:
    // 2.1. typedefs
    // 2.2. nested enums
    // 2.3. nested structs
    // 2.4. nested classes
    // 2.5. consts
    // 2.6. constructors
    // 2.7. destructors
    // 2.8. member functions
    BOOL onCreate(mMainWnd* self, DWORD dwAddData);
    // 2.9. member variables
// 3. private members   
private:
    // 3.1. typedefs
    // 3.2. nested enums
    // 3.3. nested structs
    // 3.4. nested classes
    // 3.5. consts
    // 3.6. constructors
    // 3.7. destructors
    // 3.8. member functions
    static NCS_WND_TEMPLATE control_templates[];
    DISALLOW_COPY_AND_ASSIGN(DialpadStatusActivity);
    // 3.9. member variables

};
#endif

