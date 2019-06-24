#include "PowerManager.h"
#include "Toast.h"

//AUTO_REGISTER_ACTIVITY(Toast);

#define ACTIVITY_NAME "Toast"
#undef LOG_TAG
#define LOG_TAG ACTIVITY_NAME
#define HORIZONTAL_PADDING 10
#define VERTICAL_PADDING   10

enum {
    ID_STATIC = 100,
    ID_TIMER,
};

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
Toast::Toast(const char* caption) : XiaoEActivity(&Toast::window_template)
{
    m_style = STYLE_NONE;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
Toast::~Toast()
{
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   3. private members                      |
// +++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++
// |  control properties  |
// ++++++++++++++++++++++++
static NCS_PROP_ENTRY _timer_props[] = {
    {NCSP_TIMER_INTERVAL, 400},//unit:10ms
    {0, 0},
};

// ++++++++++++++++++++++++
// |  control render      |
// ++++++++++++++++++++++++

// ++++++++++++++++++++++++
// |  control handlers    |
// ++++++++++++++++++++++++
static BOOL _timer_onTimer(mTimer*, DWORD);
static NCS_EVENT_HANDLER _home_button_handlers [] = {
    {MSG_TIMER, NCS_EVENT_HANDLER_CAST(_timer_onTimer)},
	{0, NULL}	
};

// +++++++++++++++++++++++++++
// |   3.8. member functions |
// +++++++++++++++++++++++++++
BOOL Toast::onCreate(mMainWnd* self, DWORD dwAddData)
{
    db_debug(" >> \n");
    
    mTimer *timer = SAFE_CAST(mTimer, _c(self)->getChild(self, ID_TIMER));
    if(timer)
        _c(timer)->start(timer);
    
    return TRUE;
}

void Toast::onPaint(mMainWnd *self, HDC hdc, const CLIPRGN* inv)
{
    const char* caption = GetWindowCaption(self->hwnd);

    SetBkColor(hdc, GetWindowBkColor(self->hwnd));
    TextOut (hdc, HORIZONTAL_PADDING, VERTICAL_PADDING, caption);
}

#if 0
BOOL Toast::onIntent(mMainWnd* self, int message, WPARAM wParam, LPARAM lParam)
{
    db_debug(" >> \n");
    Intent *intent;

    intent = (Intent *)wParam;
    if (intent != NULL && intent->action() == Intent::ACTION_VIEW) {
        const char* caption = intent->getCString("caption");
        setCaption(caption);
        autosize();
    }

    return TRUE;    
}
#endif

void Toast::autosize()
{
    SIZE size;
    HDC hdc = GetClientDC(hwnd());
    const char* caption = GetWindowCaption(hwnd());
    GetTextExtent (hdc, caption, -1, &size);
    
    int x, y, w, h;
    w = size.cx + HORIZONTAL_PADDING*2;
    h = size.cy + VERTICAL_PADDING*2;
    x = (800 - w) / 2;
    y = (480 - h) * 3 / 4;
    
    MoveWindow(hwnd(), x, y, w, h, FALSE); 
    ReleaseDC (hdc);
}

static BOOL _timer_onTimer(mTimer* timer, DWORD total_count)
{
    HWND hwnd = _c(timer)->getParent(timer);
    XiaoEActivity* _this = (XiaoEActivity*)Activity::getActivityFromHWND(hwnd);
    SendNotifyMessage(_this->hwnd(), MSG_CLOSE, 0, 0);
    return TRUE;
}

// +++++++++++++++++++++++++++
// |   3.9. member variables |
// +++++++++++++++++++++++++++
NCS_WND_TEMPLATE Toast::control_templates[] = {
    {
        NCSCTRL_TIMER,
        ID_TIMER,
        0, 0, 0, 0,
        WS_NONE,
        WS_EX_NONE,
        NULL, /* caption */
        _timer_props, /* props */
        NULL,
        _home_button_handlers,
        CTRL_TEMPL_ZERO_AFTER_HANDLERS
    },
};

NCS_MNWND_TEMPLATE Toast::window_template = 
    XIAOE_WINDOW_TEMPLATE(0, 0, 0, 0,
                          WS_NONE,
                          WS_EX_TOPMOST | WS_EX_TROUNDCNS | WS_EX_BROUNDCNS,
                          ACTIVITY_NAME,
                          Toast::control_templates);

