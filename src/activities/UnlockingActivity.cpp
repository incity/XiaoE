#include "UnlockingActivity.h"
#include "AccessController.h"

AUTO_REGISTER_ACTIVITY(UnlockingActivity);

#define ACTIVITY_NAME "UnlockingActivity"
#undef LOG_TAG
#define LOG_TAG ACTIVITY_NAME

enum {
    ID_BUTTON_MAIN = 100,
    ID_DIALPAD,
    ID_PASSWORDBOX,
};

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
UnlockingActivity::UnlockingActivity()
                 : XiaoEActivity(&UnlockingActivity::window_template)
{
    m_style = STYLE_ZOOM;
    background_image = (BITMAP*)calloc(1, sizeof(BITMAP));
    assert(background_image);
    
    LoadBitmap(HDC_SCREEN, background_image, 
                "./res/images/unlocking/background.png");
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
UnlockingActivity::~UnlockingActivity()
{
    UnloadBitmap(background_image);
    free(background_image);
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   3. private members                      |
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
static BOOL _home_button_onCreate(mButton* , DWORD);
static void _home_button_notify(mWidget *, int , int , DWORD);
static NCS_EVENT_HANDLER _home_button_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(_home_button_onCreate)},
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, _home_button_notify),
	{0, NULL}	
};

static void _dialpad_notify(mWidget *, int, int, DWORD);
static NCS_EVENT_HANDLER dialpad_handlers[] = {
    NCS_MAP_NOTIFY(NCSN_DIALPAD_KEYPAD_CLICKED, _dialpad_notify),
    {0, NULL}
};

static void _passwordbox_notify(mPasswordBox *, int, int, DWORD);
static NCS_EVENT_HANDLER passwordbox_handlers[] = {
    NCS_MAP_NOTIFY(NCSN_PASSWORDBOX_ENTERED, _passwordbox_notify),
    {0, NULL}
};

// +++++++++++++++++++++++++++
// |   3.8. member functions |
// +++++++++++++++++++++++++++
BOOL UnlockingActivity::onCreate(mMainWnd* self, DWORD dwAddData )
{
    db_debug(" >> \n");
    mPasswordBox *pb = (mPasswordBox*)_c(self)->getChild (self, ID_PASSWORDBOX);
    mDialPad *dp = (mDialPad*)_c(self)->getChild (self, ID_DIALPAD);

    _c(dp)->setProperty(dp, NCSP_DIALPAD_TARGET_HWND, (DWORD)pb->hwnd);
    return TRUE;
}

void UnlockingActivity::onPaint(mMainWnd *self, HDC hdc, const CLIPRGN* inv)
{
}

BOOL UnlockingActivity::onScreensave(mMainWnd* self, int message, WPARAM wParam, LPARAM lParam)
{
    return TRUE; // enable screensave
}

BOOL UnlockingActivity::onEraseBackground(mMainWnd *self, HDC hdc, const PRECT clip)
{
    RECT rc;
    GetClientRect(self->hwnd, &rc);

    if(background_image) {
        FillBoxWithBitmap(hdc, 0, 0, RECTW(rc), RECTH(rc), background_image);
    }
    
    return TRUE;
}

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

// the callback is call within the main UI thread.
static void _on_password_validated(mMainWnd *self, DWORD param)
{
    printf("%s %d : param=0x%lx \n", __func__, __LINE__, param);
    mPasswordBox *pb = (mPasswordBox *)ncsGetChildObj(self->hwnd, ID_PASSWORDBOX);
    _c(pb)->clear(pb);
   ACTIVITYSTACK.back(); 
}

static void _passwordbox_notify(mPasswordBox *self, int id, int nc, DWORD add_data)
{
    db_debug(" >> \n");
    size_t len = strlen(self->password);
    if(len) {
        ACCESSCONTROLLER.work("PasswordValidator",
                              self->password,
                              (Handler)_on_password_validated,
                              NULL,
                              GetMainWindowHandle(self->hwnd));
        //_c(self)->clear(self);
    }
}

// +++++++++++++++++++++++++++
// |   3.9. member variables |
// +++++++++++++++++++++++++++
BITMAP* UnlockingActivity::background_image = NULL;

NCS_WND_TEMPLATE UnlockingActivity::control_templates[] = {
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
        210, 145, 380, 280,
        WS_VISIBLE,
        WS_EX_TRANSPARENT,
        NULL,
        dialpad_props, //props,
        NULL, //rdr_info
        dialpad_handlers, //handlers,
        CTRL_TEMPL_ZERO_AFTER_HANDLERS
    },
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
        CTRL_TEMPL_ZERO_AFTER_HANDLERS
    }
};

NCS_MNWND_TEMPLATE UnlockingActivity::window_template = 
    XIAOE_WINDOW_TEMPLATE(ACTIVITY_NAME, UnlockingActivity::control_templates);

