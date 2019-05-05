#include "HomeActivity.h"

AUTO_REGISTER_ACTIVITY(HomeActivity);

#define LOG_TAG "HomeActivity"

enum {
    ID_SWIPER = 100,
    ID_LEDLABEL,
    ID_MARQUEE,
    ID_BUTTON_HOME,
    ID_TIMER,
};

void HomeActivity::onPaint(mMainWnd *self, HDC hdc, const CLIPRGN* inv)
{
    //RECT rc;
    //GetClientRect(self->hwnd, &rc);
    //DrawText(hdc, "Hello, XiaoE!（你好，小易）", -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
}

BOOL HomeActivity::onEraseBackground(mWidget *self, HDC hdc, const PRECT clip)
{
    RECT rc;
    GetClientRect(self->hwnd, &rc);

    if(background_image) {
        FillBoxWithBitmap(hdc, 0, 0, RECTW(rc), RECTH(rc), background_image);
    }
    
    return TRUE;
}

static BOOL updateLedLabel(mLEDLabel *listener, mTimer* sender,
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

BOOL HomeActivity::onCreate(mMainWnd* self, DWORD dwAddData )
{
    db_debug(" >> \n");
	mTimer *timer = SAFE_CAST(mTimer,
					_c(self)->getChild(self, ID_TIMER));
	if(timer) {
        db_debug("timer@%p installed.\n", timer);
		ncsAddEventListener((mObject*)timer,
						(mObject*)ncsGetChildObj(self->hwnd, ID_LEDLABEL),
						(NCS_CB_ONPIECEEVENT)updateLedLabel,
						MSG_TIMER);
		_c(timer)->start(timer);
	}
    
    return TRUE;
}

BOOL HomeActivity::onScreensave(mWidget* self, int message, WPARAM wParam, LPARAM lParam)
{
    return TRUE; // enable screensave
}

NCS_EVENT_HANDLER HomeActivity::message_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(HomeActivity::onCreate)},
    {MSG_PAINT, NCS_EVENT_HANDLER_CAST(HomeActivity::onPaint)},
    {MSG_ERASEBKGND, NCS_EVENT_HANDLER_CAST(HomeActivity::onEraseBackground)},
    {Activity::MSG_SCREENSAVE, NCS_EVENT_HANDLER_CAST(HomeActivity::onScreensave)},
    {0, NULL}
};

static NCS_PROP_ENTRY swiper_props[] = {
    {NCSP_ANMT_DIR, (DWORD)"./res/images/home/ad"},
    {NCSP_ANMT_INTERVAL, (DWORD)500},
    //{NCSP_SWIPER_PAGINATION_BULLET_COLOR, (DWORD)0xFFFFFFFF},
    //{NCSP_SWIPER_PAGINATION_BULLET_HILIGHT_COLOR, (DWORD)0xFFF48924},
    //{NCSP_SWIPER_PAGINATION_BGCOLOR, (DWORD)0x40C9C2BD},
    //{NCSP_SWIPER_PAGINATION_BULLET_MARGIN, (DWORD)5},
    {0, 0},
};

static NCS_RDR_INFO home_button_render[] = {
    {"skin", "skin", NULL}
};

static NCS_PROP_ENTRY home_button_props[] = {
    {0, 0},
};
    
static NCS_PROP_ENTRY timer_props[] = {
    {NCSP_TIMER_INTERVAL, 100},//unit:10ms
    {0, 0},
};

static NCS_PROP_ENTRY ledlabel_props[] = {
    {NCSP_LEDLBL_HEIGHT, 35},
    {0, 0},
};

static BOOL home_button_onCreate(mButton* self, DWORD dwAddData )
{
    DWORD key = (DWORD)Str2Key("images/home/home_button.png");

    ncsSetElement(self, NCS_IMAGE_BUTTON, key);

    return TRUE;
}

static void home_button_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    ACTIVITYSTACK->navigateTo("UnlockingActivity");
}

static void marquee_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    ACTIVITYSTACK->navigateTo("BulletinActivity");
}

static NCS_EVENT_HANDLER home_button_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(home_button_onCreate)},
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, home_button_notify),
	{0, NULL}	
};

static NCS_EVENT_HANDLER marquee_handlers [] = {
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, marquee_notify),
	{0, NULL}	
};

NCS_WND_TEMPLATE HomeActivity::control_template[] = {
    {
        NCSCTRL_SWIPER,
        ID_SWIPER,
        0, 0, 800, 420,
        WS_VISIBLE | NCSS_ANMT_AUTOPLAY | NCSS_ANMT_AUTOLOOP,
        WS_EX_NONE,
        NULL, /* caption */
        swiper_props, /* props */
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_LEDLABEL,
        ID_LEDLABEL,
        0, 423, 140, 55,
        WS_VISIBLE,
        WS_EX_TRANSPARENT,
        "00:00", /* caption */
        ledlabel_props, /* props */
        NULL,
        NULL, NULL, 0, 0 
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
        marquee_handlers, NULL, 0, 0 
    },
    {
        NCSCTRL_TIMER,
        ID_TIMER,
        0, 0, 0, 0,
        WS_NONE,
        WS_EX_NONE,
        NULL, /* caption */
        timer_props, /* props */
        NULL,
        NULL, NULL, 0, 0 
    },
    {
        NCSCTRL_BUTTON,
        ID_BUTTON_HOME,
        684, 369, 106, 106,
        WS_VISIBLE | NCSS_BUTTON_IMAGE,
        WS_EX_TRANSPARENT,
        NULL,
        home_button_props,
        home_button_render,
        home_button_handlers, NULL, 0, 0
    },
};

NCS_MNWND_TEMPLATE HomeActivity::window_template = {
        NCSCTRL_DIALOGBOX, 
        1,
        0, 0, 800, 480,
        WS_NONE,
        WS_EX_AUTOSECONDARYDC,
        NULL, /* caption */
        NULL,
        NULL,
        HomeActivity::message_handlers,
        HomeActivity::control_template,
        ARRAY_LEN(HomeActivity::control_template),
        0,
        0, 0,
};

const BITMAP*HomeActivity::background_image = NULL;

HomeActivity::HomeActivity() : NCSActivity(&HomeActivity::window_template){
    m_style = STYLE_PUSH;
    background_image = RetrieveRes("images/background.jpg");
    if(!background_image) {
        db_error("background image not found!\n");
    }
}

HomeActivity::~HomeActivity() {
}

