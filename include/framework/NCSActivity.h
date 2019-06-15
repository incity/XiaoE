#ifndef  NCSACTIVITY_INC
#define  NCSACTIVITY_INC
//1. The .cc .cpp .cxx related header files

//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "Activity.h"
#include "ActivityStack.h"

// WARNING:
// there is a macro conflict between mgncs.h:PRIVATE and 
// android::Mutex::PRIVATE
// SO we can not include both files at the same time.
#include <mgplus/mgplus.h>
#include <mgncs/mgncs.h>
#include <mgncs4touch/mgncs4touch.h>

#define ARRAY_LEN(array)(sizeof(array)/sizeof(array[0]))
#define NCS_EVENT_HANDLER_CAST(func) reinterpret_cast<void*>(func)

/** 
 * @synopsis NCSActivity
 */
class NCSActivity : public Activity
{
// 1. public members
public:
    // 1.1. typedefs
    // 1.2. enums
    // 1.3. consts
    // 1.4. constructors
    // 1.5. destructors
    virtual ~NCSActivity();
    
    // 1.6. member functions
    void onDestroyOrigin(mWidget* widget, int msg) {
        if (m_onDestroyOrigin) {
            m_onDestroyOrigin(widget, msg);
        }
    }
    virtual int onResume();
    virtual int onPause();
    // 1.7. member variables

// 2. protected members
protected:
    // 2.1. typedefs
    // 2.2. enums
    // 2.3. consts
    // 2.4. constructors
    // tmpl or package just include content of body.
    NCSActivity(NCS_MNWND_TEMPLATE* _template);
    NCSActivity(const NCSActivity&);
    NCSActivity(HPACKAGE hPack, HICON hIcon, HMENU hMenu) : 
        m_tmpl(NULL), m_hPack(hPack), m_hIcon(hIcon), m_hMenu(hMenu)
    {
    }
    // 2.5. destructors
    // 2.6. member functions
    virtual HWND createHWND();
    void(*m_onDestroyOrigin)(mWidget*, int);
    virtual int onCancel()
    {
        ACTIVITYSTACK.pop();
        return 0;
    }
    // 2.7. member variables
    NCS_MNWND_TEMPLATE* m_tmpl;
    HPACKAGE m_hPack;
    HICON m_hIcon;
    HMENU m_hMenu;

// 3. protected members
private:
    // 3.1. typedefs
    // 3.2. enums
    // 3.3. consts
    // 3.4. constructors
    // 3.5. destructors
    // 3.6. member functions
    // 3.7. member variables
};

#endif   /* ----- #ifndef NCSACTIVITY_INC  ----- */

