#include "DialpadStatusActivity.h"

AUTO_REGISTER_ACTIVITY(DialpadStatusActivity);

#define ACTIVITY_NAME "DialpadStatusActivity"
#undef LOG_TAG
#define LOG_TAG ACTIVITY_NAME
    
// +++++++++++++++++++++++++++++++++++++++++++++
// |   0. static members                       |
// +++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++
// |  control properties  |
// ++++++++++++++++++++++++
static NCS_PROP_ENTRY _home_button_props[] = {
    {0, 0},
};
    
static const char *dialpad_key_numbers[] = {
    "1", "2", "3", "[./res/images/unlocking/delete_key.png]",
    "4", "5", "6", "0",
    "7", "8", "9", "#"
};

static NCS_PROP_ENTRY dialpad_props[] = {
	{NCSP_DIALPAD_KEYPAD_NUMBER_ARRAY, (DWORD)dialpad_key_numbers},
	{NCSP_DIALPAD_KEYPAD_LETTERS_FONTNAME, (DWORD)"*-simfang-rrT*nn-*-16-UTF-8"},
	{0, 0}
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
static BOOL _home_button_onCreate(mButton* self, DWORD add_data )
{
    DWORD key = (DWORD)Str2Key("images/unlocking/home_button.png");

    ncsSetElement(self, NCS_IMAGE_BUTTON, key);

    return TRUE;
}

static void _home_button_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    ACTIVITYSTACK.back();
}

static void _dialpad_notify(mWidget *self, int id, int nc, DWORD add_data)
{
}

static NCS_EVENT_HANDLER _home_button_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(_home_button_onCreate)},
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, _home_button_notify),
	{0, NULL}	
};

static NCS_EVENT_HANDLER dialpad_handlers[] = {
    NCS_MAP_NOTIFY(NCSN_DIALPAD_KEYPAD_CLICKED, _dialpad_notify),
    {0, NULL}
};

// ++++++++++++++++++++++++
// |  controls            |
// ++++++++++++++++++++++++
NCS_WND_TEMPLATE DialpadStatusActivity::control_templates[] = {
    {
        NCSCTRL_BUTTON,
        ID_BUTTON_MAIN,
        684, 369, 106, 106,
        WS_VISIBLE | NCSS_BUTTON_IMAGE,
        WS_EX_TRANSPARENT,
        NULL,
        _home_button_props,
        _home_button_render,
        _home_button_handlers,
        CTRL_TEMPL_ZERO_AFTER_HANDLERS
    },
    {
        NCSCTRL_DIALPAD, 
        ID_DIALPAD,
        210, 135, 380, 280,
        WS_VISIBLE,
        WS_EX_TRANSPARENT,
        NULL,
        dialpad_props, //props,
        NULL, //rdr_info
        dialpad_handlers, //handlers,
        NULL, 0, 0, 0,
        "*-simfang-rrT*nn-*-42-UTF-8",
        CTRL_TEMPL_ZERO_AFTER_FONTNAME
    }
};


// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
DialpadStatusActivity::DialpadStatusActivity()
{
    addControl(control_templates, ARRAY_LEN(control_templates));
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
DialpadStatusActivity::~DialpadStatusActivity()
{
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   2. protected members                    |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   2.8. member functions |
// +++++++++++++++++++++++++++
BOOL DialpadStatusActivity::onCreate(mMainWnd* self, DWORD dwAddData )
{
    db_debug(" >> \n");
    StatusActivity::onCreate(self, dwAddData);
    
    return TRUE;
}

// +++++++++++++++++++++++++++
// |   2.9. member variables |
// +++++++++++++++++++++++++++


