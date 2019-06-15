#ifndef  XIAOEACTIVITY_INC
#define  XIAOEACTIVITY_INC
//1. The .cc .cpp .cxx related header files
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "NCSActivity.h"

#define REPEAT_4(x) x, x, x, x
#define REPEAT_7(x) REPEAT_4(x), x, x, x
#define REPEAT_9(x) REPEAT_7(x), x, x
#define REPEAT_11(x) REPEAT_9(x), x, x

#define CTRL_TEMPL_ZERO_AFTER_PROPS REPEAT_11(0)
#define CTRL_TEMPL_ZERO_AFTER_HANDLERS REPEAT_9(0)
#define CTRL_TEMPL_ZERO_AFTER_FONTNAME REPEAT_4(0)

#define XIAOE_WINDOW_TEMPLATE(caption, ctrls)      \
{                                                  \
        NCSCTRL_DIALOGBOX,                         \
        1,                                         \
        0, 0, 800, 480,                            \
        WS_NONE,                                   \
        WS_EX_AUTOSECONDARYDC,                     \
        (caption), /* caption */                   \
        NULL,                                      \
        NULL,                                      \
        XiaoEActivity::_message_handlers,          \
        (ctrls),                                   \
        ARRAY_LEN((ctrls)),                        \
        0,    /* user data */                      \
        0,    /* back color */                     \
        NULL, /* font name */                      \
        0, 0, NULL, 0                              \
} 
/** 
 * @synopsis XiaoEActivity
 */
class XiaoEActivity : public NCSActivity
{
// 1. public members
public:
    // 1.1. typedefs
    typedef void (*Handler)(mMainWnd*, DWORD);
    // 1.2. enums
    enum MESSAGE
    {
        MSG_CALLBACK = NCSActivity::MSG_FRAMEWORK,
    };
    // 1.3. consts
    // 1.4. constructors
    
    // 1.5. destructors
    virtual ~XiaoEActivity();
    
    // 1.6. member functions
    static bool runOnUiThread(HWND hWnd,
                                     Handler handler,
                                     DWORD param)
    {
        // TODO: check the if clause
        //if(hWnd && ACTIVITYSTACK.top()->hwnd() == hWnd)
            return PostMessage(hWnd, MSG_CALLBACK, 
                               (WPARAM)handler, (LPARAM)param) == 0;

        //return false;
    }
    // 1.7. member variables

// 2. protected members
protected:
    // 2.1. typedefs
    // 2.2. enums
    // 2.3. consts
    // 2.4. constructors
    // tmpl or package just include content of body.
    XiaoEActivity(NCS_MNWND_TEMPLATE* _template);
    XiaoEActivity(const XiaoEActivity&);

    // 2.5. destructors
    // 2.6. member functions
    virtual BOOL onCreate(mMainWnd* self, DWORD dwAddData){return 0;}
    virtual void onPaint(mMainWnd *self, HDC hdc, const CLIPRGN* inv){}
    virtual BOOL onEraseBackground(mMainWnd *self, HDC hdc, const PRECT clip){return 0;}
    virtual BOOL onScreensave(mMainWnd* self, int message, WPARAM wParam, LPARAM lParam){return 0;}
    
    // 2.7. member variables
    static NCS_EVENT_HANDLER _message_handlers[];

// 3. private members
private:
    // 3.1. typedefs
    // 3.2. enums
    // 3.3. consts
    // 3.4. constructors
    // 3.5. destructors
    // 3.6. member functions
    static BOOL _onCreate(mMainWnd* self, DWORD dwAddData);
    static void _onPaint(mMainWnd *self, HDC hdc, const CLIPRGN* inv);
    static BOOL _onEraseBackground(mMainWnd *self, HDC hdc, const PRECT clip);
    static BOOL _onScreensave(mMainWnd* self, int message, WPARAM wParam, LPARAM lParam);
    static BOOL _onCallback(mMainWnd* self, int message, WPARAM wParam, LPARAM lParam);
    
    // 3.7. member variables
};

#endif   /* ----- #ifndef XIAOEACTIVITY_INC  ----- */
