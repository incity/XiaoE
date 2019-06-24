#include "AccessPwdStep2Activity.h"
#include "Toast.h"
#include "AccessController.h"

AUTO_REGISTER_ACTIVITY(AccessPwdStep2Activity);

#define ACTIVITY_NAME "AccessPwdStep2Activity"
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
	{NCSP_PASSWORDBOX_MAX_LENGTH, (DWORD)6},
	{0, 0}
};

// ++++++++++++++++++++++++
// |  control render      |
// ++++++++++++++++++++++++
// ++++++++++++++++++++++++
// |  control handlers    |
// ++++++++++++++++++++++++
// the callback is call within the main UI thread.
static void _on_password_validated(mMainWnd *self, DWORD param)
{
    printf("%s %d : param=0x%lx \n", __func__, __LINE__, param);
    mPasswordBox *pb = (mPasswordBox *)ncsGetChildObj(self->hwnd, ID_PASSWORDBOX);
    _c(pb)->clear(pb);

    ExcludeWindowStyle(pb->hwnd, WS_DISABLED);

    if(!param) {
        ACTIVITYSTACK.home();
        Toast::makeText("门已开启，请进~")->show();
        return;
    }

    Toast::makeText("密码错误，请重新输入~")->show();
}

static void _passwordbox_notify(mPasswordBox *self, int id, int nc, DWORD add_data)
{
    if(GetWindowStyle(self->hwnd) & WS_DISABLED)
        return;
    
    db_debug(" >> self(@%p) id(%d)\n", self, id);
    size_t len = strlen(self->password);
    if(len) {
        IncludeWindowStyle(self->hwnd, WS_DISABLED);
        ACCESSCONTROLLER.work("PasswordValidator",
                              self->password,
                              (Handler)_on_password_validated,
                              NULL,
                              GetMainWindowHandle(self->hwnd));
        //_c(self)->clear(self);
    }
}

static NCS_EVENT_HANDLER passwordbox_handlers[] = {
    NCS_MAP_NOTIFY(NCSN_PASSWORDBOX_ENTERED, _passwordbox_notify),
    {0, NULL}
};

// ++++++++++++++++++++++++
// |  controls            |
// ++++++++++++++++++++++++
NCS_WND_TEMPLATE AccessPwdStep2Activity::control_templates[] = {
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
AccessPwdStep2Activity::AccessPwdStep2Activity()
{
    m_style = STYLE_ZOOM;
    addControl(control_templates, ARRAY_LEN(control_templates));
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
AccessPwdStep2Activity::~AccessPwdStep2Activity()
{
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   3. private members                      |
// +++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++
// |   3.8. member functions |
// +++++++++++++++++++++++++++
BOOL AccessPwdStep2Activity::onCreate(mMainWnd* self, DWORD dwAddData )
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
