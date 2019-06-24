#include "AccessPwdStep1Activity.h"
#include "Toast.h"

AUTO_REGISTER_ACTIVITY(AccessPwdStep1Activity);

#define ACTIVITY_NAME "AccessPwdStep1Activity"
#undef LOG_TAG
#define LOG_TAG ACTIVITY_NAME

enum {
    ID_PASSWORDBOX = DialpadStatusActivity::ID_END,
};

// +++++++++++++++++++++++++++++++++++++++++++++
// |   0. static members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// ++++++++++++++++++++++++
// |  control properties  |
// ++++++++++++++++++++++++
static NCS_PROP_ENTRY passwordbox_props[] = {
	{NCSP_PASSWORDBOX_MAX_LENGTH, (DWORD)4},
	{0, 0}
};

// ++++++++++++++++++++++++
// |  control render      |
// ++++++++++++++++++++++++

// ++++++++++++++++++++++++
// |  control handlers    |
// ++++++++++++++++++++++++
static void _passwordbox_notify(mPasswordBox *self, int id, int nc, DWORD add_data)
{
    if(GetWindowStyle(self->hwnd) & WS_DISABLED)
        return;
    
    db_debug(" >> \n");
    size_t len = strlen(self->password);
    if(len) {
        ACTIVITYSTACK.navigateTo("AccessPwdStep2Activity");
    }
}

static NCS_EVENT_HANDLER passwordbox_handlers[] = {
    NCS_MAP_NOTIFY(NCSN_PASSWORDBOX_ENTERED, _passwordbox_notify),
    {0, NULL}
};

// ++++++++++++++++++++++++
// |  controls            |
// ++++++++++++++++++++++++
NCS_WND_TEMPLATE AccessPwdStep1Activity::control_templates[] = {

    {
        NCSCTRL_PASSWORDBOX, 
        ID_PASSWORDBOX,
        210, 55, 380, 60,
        WS_VISIBLE,
        WS_EX_TRANSPARENT,
        NULL,
        passwordbox_props, //props,
        NULL, //rdr_info
        passwordbox_handlers, //handlers,
        NULL, 0, 0, 0,
        "*-simfang-rrT*nn-*-32-UTF-8",
        CTRL_TEMPL_ZERO_AFTER_FONTNAME
    }
};

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
AccessPwdStep1Activity::AccessPwdStep1Activity()
{
    m_style = STYLE_ZOOM;
    addControl(control_templates, ARRAY_LEN(control_templates));
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
AccessPwdStep1Activity::~AccessPwdStep1Activity()
{
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   3. private members                      |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   3.8. member functions |
// +++++++++++++++++++++++++++
BOOL AccessPwdStep1Activity::onCreate(mMainWnd* self, DWORD dwAddData )
{
    db_debug(" >> \n");
    DialpadStatusActivity::onCreate(self, dwAddData);
    
    mPasswordBox *pb = (mPasswordBox*)_c(self)->getChild (self, ID_PASSWORDBOX);
    mDialPad *dp = (mDialPad*)_c(self)->getChild (self, DialpadStatusActivity::ID_DIALPAD);

    _c(dp)->setProperty(dp, NCSP_DIALPAD_TARGET_HWND, (DWORD)pb->hwnd);
    return TRUE;
}

// +++++++++++++++++++++++++++
// |   3.9. member variables |
// +++++++++++++++++++++++++++
