#ifndef BLACKSCREEN_ACTIVITY_HH
#define BLACKSCREEN_ACTIVITY_HH

#include "NCSActivity.h"

class BlackScreenActivity : public NCSActivity {
public:
    BlackScreenActivity();
    ~BlackScreenActivity();

protected:
    /* must be static because of the 'this' pointer. */
    static void onPaint(mMainWnd *self, HDC hdc, const CLIPRGN* inv);
    static BOOL onCreate(mMainWnd* self, DWORD dwAddData);
    static BOOL onEraseBackground(mWidget *self, HDC hdc, const PRECT clip);

    static NCS_EVENT_HANDLER message_handlers[];
    static NCS_MNWND_TEMPLATE window_template;
    static NCS_WND_TEMPLATE control_template[];
};
#endif

