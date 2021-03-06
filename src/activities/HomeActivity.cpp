#include "HomeActivity.h"

AUTO_REGISTER_ACTIVITY(HomeActivity);

#define ACTIVITY_NAME "HomeActivity"
#undef LOG_TAG
#define LOG_TAG ACTIVITY_NAME

enum {
    ID_SWIPER = StatusActivity::ID_END,
    ID_BUTTON_HOME,
};

// +++++++++++++++++++++++++++++++++++++++++++++
// |   0. static members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// ++++++++++++++++++++++++
// |  control properties  |
// ++++++++++++++++++++++++
static NCS_PROP_ENTRY _swiper_props[] = {
    {NCSP_ANMT_DIR, (DWORD)"./res/images/home/ad"},
    {NCSP_ANMT_INTERVAL, (DWORD)500},
    //{NCSP_SWIPER_PAGINATION_BULLET_COLOR, (DWORD)0xFFFFFFFF},
    //{NCSP_SWIPER_PAGINATION_BULLET_HILIGHT_COLOR, (DWORD)0xFFF48924},
    //{NCSP_SWIPER_PAGINATION_BGCOLOR, (DWORD)0x40C9C2BD},
    //{NCSP_SWIPER_PAGINATION_BULLET_MARGIN, (DWORD)5},
    {0, 0},
};

static NCS_PROP_ENTRY _home_button_props[] = {
    {0, 0},
};

// ++++++++++++++++++++++++
// |  control render      |
// ++++++++++++++++++++++++
static NCS_RDR_INFO _home_button_render[] = {
    {"skin", "skin", NULL}
};

// ++++++++++++++++++++++++
// |  control handlers    |
// ++++++++++++++++++++++++
static BOOL _home_button_onCreate(mButton* self, DWORD dwAddData )
{
    DWORD key = (DWORD)Str2Key("images/home/home_button.png");

    ncsSetElement(self, NCS_IMAGE_BUTTON, key);

    return TRUE;
}

static void _home_button_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    ACTIVITYSTACK.navigateTo("AccessModeActivity");
}

static NCS_EVENT_HANDLER _home_button_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(_home_button_onCreate)},
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, _home_button_notify),
    {0, NULL}
};

// ++++++++++++++++++++++++
// |  controls            |
// ++++++++++++++++++++++++
NCS_WND_TEMPLATE HomeActivity::control_templates[] = {
    {
        NCSCTRL_SWIPER,
        ID_SWIPER,
        0, 0, 800, 420,
        WS_VISIBLE | NCSS_ANMT_AUTOPLAY | NCSS_ANMT_AUTOLOOP,
        WS_EX_NONE,
        NULL, /* caption */
        _swiper_props, /* props */
        CTRL_TEMPL_ZERO_AFTER_PROPS
    },
    {
        NCSCTRL_BUTTON,
        ID_BUTTON_HOME,
        684, 369, 106, 106,
        WS_VISIBLE | NCSS_BUTTON_IMAGE,
        WS_EX_TRANSPARENT,
        NULL,
        _home_button_props,
        _home_button_render,
        _home_button_handlers,
        CTRL_TEMPL_ZERO_AFTER_HANDLERS
    },
};

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
HomeActivity::HomeActivity()
{
    m_style = STYLE_PUSH;
    addControl(control_templates, ARRAY_LEN(control_templates));
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
HomeActivity::~HomeActivity()
{
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   2. protected members                    |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   2.8. member functions |
// +++++++++++++++++++++++++++
int HomeActivity::onPause()
{
    StatusActivity::onPause();
     mSwiper* swiper = (mSwiper *)ncsGetChildObj(hwnd(), ID_SWIPER);
    _c(swiper)->pauseResume(swiper);

    return 0;
}

int HomeActivity::onResume()
{
    StatusActivity::onResume();
    mSwiper* swiper = (mSwiper *)ncsGetChildObj(hwnd(), ID_SWIPER);
    _c(swiper)->pauseResume(swiper);

    return 0;
}

BOOL HomeActivity::onCreate(mMainWnd* self, DWORD dwAddData )
{
    db_debug(" >> \n");
    StatusActivity::onCreate(self, dwAddData);

    return TRUE;
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   3. private members                      |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   3.9. member variables |
// +++++++++++++++++++++++++++

