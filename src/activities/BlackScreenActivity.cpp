#include "PowerManager.h"
#include "BlackScreenActivity.h"

AUTO_REGISTER_ACTIVITY(BlackScreenActivity);

#define ACTIVITY_NAME "BlackScreenActivity"
#undef LOG_TAG
#define LOG_TAG ACTIVITY_NAME

enum {
    ID_STATIC = 100,
};

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
BlackScreenActivity::BlackScreenActivity()
                 : XiaoEActivity(&BlackScreenActivity::window_template)
{
    m_style = STYLE_ALPHA;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
BlackScreenActivity::~BlackScreenActivity()
{
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   3. private members                      |
// +++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++
// |  control properties  |
// ++++++++++++++++++++++++

// ++++++++++++++++++++++++
// |  control render      |
// ++++++++++++++++++++++++

// ++++++++++++++++++++++++
// |  control handlers    |
// ++++++++++++++++++++++++
static void static_notify(mWidget *, int, int, DWORD);
static NCS_EVENT_HANDLER static_handlers [] = {
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, static_notify),
	{0, NULL}
};

// +++++++++++++++++++++++++++
// |   3.8. member functions |
// +++++++++++++++++++++++++++
BOOL BlackScreenActivity::onCreate(mMainWnd* self, DWORD dwAddData)
{
    db_debug(" >> \n");
    POWERMANAGER.screenOff();

    return TRUE;
}

static void static_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    db_debug("Exit idle state. back to ^_^|HomeActivity|^_^\n");
    ACTIVITYSTACK.home();
    POWERMANAGER.screenOn();
}

// +++++++++++++++++++++++++++
// |   3.9. member variables |
// +++++++++++++++++++++++++++
NCS_WND_TEMPLATE BlackScreenActivity::control_templates[] = {
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
        NULL, 0, 0, NULL, 0
    },
};

NCS_MNWND_TEMPLATE BlackScreenActivity::window_template = 
    XIAOE_WINDOW_FULLSCREEN_TEMPLATE(ACTIVITY_NAME, BlackScreenActivity::control_templates);

