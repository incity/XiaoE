#include "PowerManager.h"
#include "BlackScreenActivity.h"

AUTO_REGISTER_ACTIVITY(BlackScreenActivity);

#undef LOG_TAG
#define LOG_TAG "BlackScreenActivity"

enum {
    ID_STATIC = 100,
};

BOOL BlackScreenActivity::onCreate(mMainWnd* self, DWORD dwAddData)
{
    db_debug(" >> \n");
    POWERMANAGER->screenOff();

    return TRUE;
}

void BlackScreenActivity::onPaint(mMainWnd *self, HDC hdc, const CLIPRGN* inv)
{
#if 0
    HDC hdc = BeginPaint(self->hwnd);
    RECT rc;
    GetClientRect(self->hwnd, &rc);
    
    ncsCommRDRFillHalfRoundRect(hdc, &rc, 0, 0, COLOR_black, 0);
    EndPaint(self->hwnd, hdc);
#endif
}

BOOL BlackScreenActivity::onEraseBackground(mWidget *self, HDC hdc, const PRECT clip)
{
    return TRUE;
}

static void static_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    db_debug("Exit idle state. back to ^_^|HomeActivity|^_^\n");
    POWERMANAGER->screenOn();
    ACTIVITYSTACK->home();
}

static NCS_EVENT_HANDLER static_handlers [] = {
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, static_notify),
	{0, NULL}
};

NCS_EVENT_HANDLER BlackScreenActivity::message_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(BlackScreenActivity::onCreate)},
    {MSG_PAINT, NCS_EVENT_HANDLER_CAST(BlackScreenActivity::onPaint)},
    {MSG_ERASEBKGND, NCS_EVENT_HANDLER_CAST(BlackScreenActivity::onEraseBackground)},
    {0, NULL}
};

NCS_WND_TEMPLATE BlackScreenActivity::control_template[] = {
    {
        NCSCTRL_STATIC,
        ID_STATIC,
        0, 0, 800, 480,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_TRANSPARENT,
        NULL, /* caption */
        NULL, /* props */
        NULL,
        static_handlers,
        NULL,
        0, 0,
        0xFF000000,
    },
};

NCS_MNWND_TEMPLATE BlackScreenActivity::window_template = {
        NCSCTRL_DIALOGBOX, 
        1,
        0, 0, 800, 480,
        WS_NONE,
        WS_EX_NONE,
        NULL, /* caption */
        NULL,
        NULL,
        BlackScreenActivity::message_handlers,
        BlackScreenActivity::control_template,
        ARRAY_LEN(BlackScreenActivity::control_template),
        0,
        0, 0,
};

BlackScreenActivity::BlackScreenActivity() : NCSActivity(&BlackScreenActivity::window_template){
    m_style = STYLE_ALPHA;
}

BlackScreenActivity::~BlackScreenActivity() {
}

