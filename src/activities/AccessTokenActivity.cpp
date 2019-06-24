#include "AccessTokenActivity.h"
#include "Toast.h"
#include "AccessController.h"

AUTO_REGISTER_ACTIVITY(AccessTokenActivity);

#define ACTIVITY_NAME "AccessTokenActivity"
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
    ACTIVITYSTACK.home();

   //Intent* intent = Intent::newIntent(Intent::ACTION_VIEW);
   //intent->putExtra("caption", (const char *)"门已开启，请进~");
   //ACTIVITYSTACK.push("Toast", intent);

   Toast::makeText("门已开启，请进~")->show();
}

static void _passwordbox_notify(mPasswordBox *self, int id, int nc, DWORD add_data)
{
    if(GetWindowStyle(self->hwnd) & WS_DISABLED)
        return;
    
    db_debug(" >> \n");
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
NCS_WND_TEMPLATE AccessTokenActivity::control_templates[] = {
    {
        NCSCTRL_PASSWORDBOX, 
        ID_PASSWORDBOX,
        210, 55, 380, 60,
        WS_VISIBLE,
        WS_EX_TRANSPARENT,
        NULL,
        NULL, //props,
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
AccessTokenActivity::AccessTokenActivity()
{
    m_style = STYLE_ZOOM;
    addControl(control_templates, ARRAY_LEN(control_templates));
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
AccessTokenActivity::~AccessTokenActivity()
{
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   3. private members                      |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   3.8. member functions |
// +++++++++++++++++++++++++++
BOOL AccessTokenActivity::onCreate(mMainWnd* self, DWORD dwAddData )
{
    db_debug(" >> \n");
    DialpadStatusActivity::onCreate(self, dwAddData);
    
    mPasswordBox *pb = (mPasswordBox*)_c(self)->getChild(self, ID_PASSWORDBOX);
    mDialPad *dp = (mDialPad*)_c(self)->getChild(self, DialpadStatusActivity::ID_DIALPAD);

    _c(dp)->setProperty(dp, NCSP_DIALPAD_TARGET_HWND, (DWORD)pb->hwnd);
    return TRUE;
}
// +++++++++++++++++++++++++++
// |   3.9. member variables |
// +++++++++++++++++++++++++++
