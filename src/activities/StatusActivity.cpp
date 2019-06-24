#include "StatusActivity.h"

//AUTO_REGISTER_ACTIVITY(StatusActivity);

#define ACTIVITY_NAME "StatusActivity"
#undef LOG_TAG
#define LOG_TAG ACTIVITY_NAME

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
StatusActivity::StatusActivity() : XiaoEActivity(&StatusActivity::window_template){
    background_image = RetrieveRes("images/background.jpg");
    if(!background_image) {
        db_error("background image not found!\n");
    }
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
StatusActivity::~StatusActivity() {
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   2. protected members                    |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   2.8. member functions |
// +++++++++++++++++++++++++++
int StatusActivity::onPause()
{
    mMarquee* marquee = (mMarquee *)ncsGetChildObj(hwnd(), ID_MARQUEE);
    _c(marquee)->pauseResume(marquee);

    mTimer *timer = (mTimer *)ncsGetChildObj(hwnd(), ID_TIMER);
    _c(timer)->stop(timer);

    return 0;
}

int StatusActivity::onResume()
{
    mMarquee* marquee = (mMarquee *)ncsGetChildObj(hwnd(), ID_MARQUEE);
    _c(marquee)->pauseResume(marquee);

    mTimer *timer = (mTimer *)ncsGetChildObj(hwnd(), ID_TIMER);
    _c(timer)->start(timer);

    return 0;
}

static BOOL _updateLedLabel(mLEDLabel *, mTimer*, int , DWORD);
BOOL StatusActivity::onCreate(mMainWnd* self, DWORD dwAddData )
{
    db_debug(" >> \n");
    mTimer *timer = SAFE_CAST(mTimer,
                                _c(self)->getChild(self, ID_TIMER));
    if(timer) {
        db_debug("timer@%p installed.\n", timer);
        ncsAddEventListener((mObject*)timer,
                        (mObject*)ncsGetChildObj(self->hwnd, ID_LEDLABEL),
                        (NCS_CB_ONPIECEEVENT)_updateLedLabel,
                        MSG_TIMER);
        _c(timer)->start(timer);
    }
    
    return TRUE;
}

BOOL StatusActivity::onEraseBackground(mMainWnd *self, HDC hdc, const PRECT clip)
{
    RECT rc;
    GetClientRect(self->hwnd, &rc);

    if(background_image) {
        FillBoxWithBitmap(hdc, 0, 0, RECTW(rc), RECTH(rc), background_image);
    }
    
    return TRUE;
}

BOOL StatusActivity::onScreensave(mMainWnd* self, int message, WPARAM wParam, LPARAM lParam)
{
    return TRUE; // enable screensave
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   3. private members                      |
// +++++++++++++++++++++++++++++++++++++++++++++

// ++++++++++++++++++++++++
// |  control properties  |
// ++++++++++++++++++++++++
static NCS_PROP_ENTRY _ledlabel_props[] = {
    {NCSP_LEDLBL_HEIGHT, 35},
    {0, 0},
};

static NCS_PROP_ENTRY _timer_props[] = {
    {NCSP_TIMER_INTERVAL, 100},//unit:10ms
    {0, 0},
};

// ++++++++++++++++++++++++
// |  control render      |
// ++++++++++++++++++++++++

// ++++++++++++++++++++++++
// |  control handlers    |
// ++++++++++++++++++++++++
static BOOL _updateLedLabel(mLEDLabel *listener, mTimer* sender,
                            int id, DWORD total_count)
{
    char szText[8];
    time_t tim;
    struct tm *ptm;
    static int show_dot=0;

    time(&tim);
    ptm = localtime(&tim);

    sprintf(szText, "%02d%s%02d", ptm->tm_hour, show_dot?" ":":",ptm->tm_min);
    SetWindowText(listener->hwnd, szText);
    InvalidateRect(listener->hwnd, NULL, TRUE);
    show_dot = (show_dot+1)%2;
    
    return FALSE;
}

static void _marquee_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    ACTIVITYSTACK.navigateTo("BulletinActivity");
}

static NCS_EVENT_HANDLER _marquee_handlers [] = {
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, _marquee_notify),
    {0, NULL}
};

// +++++++++++++++++++++++++++
// |   3.9. member variables |
// +++++++++++++++++++++++++++
const BITMAP*StatusActivity::background_image = NULL;

NCS_WND_TEMPLATE StatusActivity::control_templates[] = {
    {
        NCSCTRL_LEDLABEL,
        ID_LEDLABEL,
        0, 423, 140, 55,
        WS_VISIBLE,
        WS_EX_TRANSPARENT,
        "00:00", /* caption */
        _ledlabel_props, /* props */
        CTRL_TEMPL_ZERO_AFTER_PROPS
    },
    {
        NCSCTRL_MARQUEE,
        ID_MARQUEE,
        235, 423, 450, 55,
        WS_VISIBLE | NCSS_NOTIFY | NCSS_MARQUEE_AUTOPLAY | NCSS_MARQUEE_DIRECTION_RIGHT | NCSS_MARQUEE_BEHAVIOR_SCROLL,
        WS_EX_TRANSPARENT,
        "^_^非常感谢您使用小易门禁^_^", /* caption */
        NULL, /* props */
        NULL,
        _marquee_handlers,
        NULL, 0, 0, 0,
        "*-simfang-rrT*nn-*-26-UTF-8",
        CTRL_TEMPL_ZERO_AFTER_FONTNAME
    },
    {
        NCSCTRL_TIMER,
        ID_TIMER,
        0, 0, 0, 0,
        WS_NONE,
        WS_EX_NONE,
        NULL, /* caption */
        _timer_props, /* props */
        CTRL_TEMPL_ZERO_AFTER_PROPS
    },
};

NCS_MNWND_TEMPLATE StatusActivity::window_template = 
    XIAOE_WINDOW_FULLSCREEN_TEMPLATE(ACTIVITY_NAME, StatusActivity::control_templates);

