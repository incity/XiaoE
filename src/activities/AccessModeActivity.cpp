#include "AccessModeActivity.h"

AUTO_REGISTER_ACTIVITY(AccessModeActivity);

#define ACTIVITY_NAME "AccessModeActivity"
#undef LOG_TAG
#define LOG_TAG ACTIVITY_NAME

enum {
    ID_BUTTON_MAIN = StatusActivity::ID_END,
    ID_LABEL_ACCESSMODE,
    ID_BUTTON_PASSWORD,
    ID_BUTTON_TOKEN,
    ID_BUTTON_QRCODE,
};
    
// +++++++++++++++++++++++++++++++++++++++++++++
// |   0. static members                       |
// +++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++
// |  control properties  |
// ++++++++++++++++++++++++
static NCS_PROP_ENTRY _button_props[] = {
    {0, 0},
};

// ++++++++++++++++++++++++
// |  control render      |
// ++++++++++++++++++++++++
static NCS_RDR_INFO _button_render[] = {
    {"skin", "skin", NULL}
};

// ++++++++++++++++++++++++
// |  control handlers    |
// ++++++++++++++++++++++++
static BOOL _home_button_onCreate(mButton* self, DWORD add_data )
{
    DWORD key = (DWORD)Str2Key("images/unlocking/home_button.png");
    ncsSetElement(self, NCS_IMAGE_BUTTON, key);

    return TRUE;
}

static BOOL _password_button_onCreate(mButton* self, DWORD add_data )
{
    DWORD key = (DWORD)Str2Key("images/unlocking/password.png");
    ncsSetElement(self, NCS_IMAGE_BUTTON, key);

    return TRUE;
}

static BOOL _token_button_onCreate(mButton* self, DWORD add_data )
{
    DWORD key = (DWORD)Str2Key("images/unlocking/token.png");
    ncsSetElement(self, NCS_IMAGE_BUTTON, key);

    return TRUE;
}

static BOOL _qrcode_button_onCreate(mButton* self, DWORD add_data )
{
    DWORD key = (DWORD)Str2Key("images/unlocking/qrcode.png");
    ncsSetElement(self, NCS_IMAGE_BUTTON, key);

    return TRUE;
}

static void _home_button_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    ACTIVITYSTACK.back();
}

static void _password_button_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    ACTIVITYSTACK.navigateTo("AccessPwdStep1Activity");
}

static void _token_button_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    ACTIVITYSTACK.navigateTo("AccessTokenActivity");
}

static void _qrcode_button_notify(mWidget *self, int id, int nc, DWORD add_data)
{
}

static NCS_EVENT_HANDLER _home_button_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(_home_button_onCreate)},
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, _home_button_notify),
	{0, NULL}	
};

static NCS_EVENT_HANDLER _password_button_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(_password_button_onCreate)},
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, _password_button_notify),
	{0, NULL}	
};

static NCS_EVENT_HANDLER _token_button_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(_token_button_onCreate)},
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, _token_button_notify),
	{0, NULL}	
};

static NCS_EVENT_HANDLER _qrcode_button_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(_qrcode_button_onCreate)},
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, _qrcode_button_notify),
	{0, NULL}	
};

// ++++++++++++++++++++++++
// |  controls            |
// ++++++++++++++++++++++++
NCS_WND_TEMPLATE AccessModeActivity::control_templates[] = {
    {
        NCSCTRL_BUTTON,
        ID_BUTTON_MAIN,
        684, 369, 106, 106,
        WS_VISIBLE | NCSS_BUTTON_IMAGE,
        WS_EX_TRANSPARENT,
        NULL,
        _button_props,
        _button_render,
        _home_button_handlers,
        CTRL_TEMPL_ZERO_AFTER_HANDLERS
    },
    {
        NCSCTRL_BUTTON,
        ID_BUTTON_PASSWORD,
        137, 147, 135, 135,
        WS_VISIBLE | NCSS_BUTTON_IMAGE,
        WS_EX_TRANSPARENT,
        "Password",
        _button_props,
        _button_render,
        _password_button_handlers,
        CTRL_TEMPL_ZERO_AFTER_HANDLERS
    },
    {
        NCSCTRL_BUTTON,
        ID_BUTTON_TOKEN,
        335, 147, 135, 135,
        WS_VISIBLE | NCSS_BUTTON_IMAGE,
        WS_EX_TRANSPARENT,
        NULL,
        _button_props,
        _button_render,
        _token_button_handlers,
        CTRL_TEMPL_ZERO_AFTER_HANDLERS
    },
    {
        NCSCTRL_BUTTON,
        ID_BUTTON_QRCODE,
        533, 147, 135, 135,
        WS_VISIBLE | NCSS_BUTTON_IMAGE,
        WS_EX_TRANSPARENT,
        NULL,
        _button_props,
        _button_render,
        _qrcode_button_handlers,
        CTRL_TEMPL_ZERO_AFTER_HANDLERS
    },

};

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
AccessModeActivity::AccessModeActivity()
{
    m_style = STYLE_ZOOM;
    addControl(control_templates, ARRAY_LEN(control_templates));
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
AccessModeActivity::~AccessModeActivity()
{
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   3. private members                      |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   3.8. member functions |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   3.9. member variables |
// +++++++++++++++++++++++++++

