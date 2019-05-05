/*!============================================================================
 * @file NCSActivity.hh 
 * @Synopsis  
 * @author DongKai
 * @version 1.0
 *  Company: Beijing Feynman Software Technology Co., Ltd.
 */

#ifndef  NCSACTIVITY_INC
#define  NCSACTIVITY_INC

#include "Activity.h"
#include "ActivityStack.h"

#define ARRAY_LEN(array)(sizeof(array)/sizeof(array[0]))
#define NCS_EVENT_HANDLER_CAST(func) reinterpret_cast<void*>(func)

/** 
 * @synopsis NCSActivity 
 */
class NCSActivity : public Activity 
{
public:
    virtual ~NCSActivity();

    void onDestroyOrigin(mWidget* widget, int msg) {
        if (m_onDestroyOrigin) {
            m_onDestroyOrigin(widget, msg);
        }
    }

    virtual int onResume();
    virtual int onPause();
protected:
    // tmpl or package just include content of body.
    NCSActivity(NCS_MNWND_TEMPLATE* _template);

    NCSActivity(HPACKAGE hPack, HICON hIcon, HMENU hMenu) : 
        m_tmpl(NULL), m_hPack(hPack), m_hIcon(hIcon), m_hMenu(hMenu)
    {
    }

    virtual int onCancel()
    {
        ActivityStack::singleton()->pop();
        return 0;
    }

    NCSActivity(const NCSActivity&);
    virtual HWND createHWND();

    NCS_MNWND_TEMPLATE* m_tmpl;
    HPACKAGE m_hPack;
    HICON m_hIcon;
    HMENU m_hMenu;
    void(*m_onDestroyOrigin)(mWidget*, int);
};

#endif   /* ----- #ifndef NCSACTIVITY_INC  ----- */

