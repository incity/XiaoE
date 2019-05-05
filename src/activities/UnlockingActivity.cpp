#include "UnlockingActivity.h"

AUTO_REGISTER_ACTIVITY(UnlockingActivity);

#define LOG_TAG "UnlockingActivity"

enum {
    ID_BUTTON_MAIN = 100,
    ID_DIALPAD,
    ID_PASSWORDBOX,
};

void UnlockingActivity::onPaint(mMainWnd *self, HDC hdc, const CLIPRGN* inv)
{
}

BOOL UnlockingActivity::onScreensave(mWidget* self, int message, WPARAM wParam, LPARAM lParam)
{
    return TRUE; // enable screensave
}

BOOL UnlockingActivity::onEraseBackground(mWidget *self, HDC hdc, const PRECT clip)
{
    RECT rc;
    GetClientRect(self->hwnd, &rc);

    if(background_image) {
        FillBoxWithBitmap(hdc, 0, 0, RECTW(rc), RECTH(rc), background_image);
    }
    
    return TRUE;
}

BOOL UnlockingActivity::onCreate(mMainWnd* self, DWORD dwAddData )
{
    db_debug(" >> \n");
    mPasswordBox *pb = (mPasswordBox*)_c(self)->getChild (self, ID_PASSWORDBOX);
    mDialPad *dp = (mDialPad*)_c(self)->getChild (self, ID_DIALPAD);

    _c(dp)->setProperty(dp, NCSP_DIALPAD_TARGET_HWND, (DWORD)pb->hwnd);
    return TRUE;
}

static BOOL home_button_onCreate(mButton* self, DWORD dwAddData )
{
    DWORD key = (DWORD)Str2Key("images/unlocking/home_button.png");

    ncsSetElement(self, NCS_IMAGE_BUTTON, key);

    return TRUE;
}

static NCS_RDR_INFO home_button_render[] = {
    {"skin", "skin", NULL}
};

static NCS_PROP_ENTRY home_button_props[] = {
    {0, 0},
};

static void home_button_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    ACTIVITYSTACK->back();
}

static NCS_EVENT_HANDLER home_button_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(home_button_onCreate)},
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, home_button_notify),
	{0, NULL}	
};

NCS_EVENT_HANDLER UnlockingActivity::message_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(UnlockingActivity::onCreate)},
    {MSG_PAINT, NCS_EVENT_HANDLER_CAST(UnlockingActivity::onPaint)},
    {MSG_ERASEBKGND, NCS_EVENT_HANDLER_CAST(UnlockingActivity::onEraseBackground)},
    {Activity::MSG_SCREENSAVE, NCS_EVENT_HANDLER_CAST(UnlockingActivity::onScreensave)},
    {0, NULL}
};
    
static const char *dialpad_key_numbers[] = {
    "1", "2", "3", "[./res/images/unlocking/delete_key.png]",
    "4", "5", "6", "0",
    "7", "8", "9", "#"
};

static void dialpad_notify(mWidget *self, int id, int nc, DWORD add_data)
{
}

static void passwordbox_notify(mPasswordBox *self, int id, int nc, DWORD add_data)
{
    _c(self)->clear(self);
}

static NCS_EVENT_HANDLER dialpad_handlers [] = {
    NCS_MAP_NOTIFY(NCSN_DIALPAD_KEYPAD_CLICKED, dialpad_notify),
    {0, NULL}
};


static NCS_EVENT_HANDLER passwordbox_handlers [] = {
    NCS_MAP_NOTIFY(NCSN_PASSWORDBOX_ENTERED, passwordbox_notify),
    {0, NULL}
};
    
static NCS_PROP_ENTRY dialpad_props [] = {
	{NCSP_DIALPAD_KEYPAD_NUMBER_ARRAY, (DWORD)dialpad_key_numbers},
	{0, 0}
};

NCS_WND_TEMPLATE UnlockingActivity::control_template[] = {
    {
        NCSCTRL_BUTTON,
        ID_BUTTON_MAIN,
        684, 369, 106, 106,
        WS_VISIBLE | NCSS_BUTTON_IMAGE,
        WS_EX_TRANSPARENT,
        NULL,
        home_button_props,
        home_button_render,
        home_button_handlers, NULL, 0, 0
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
        NULL, //controls
        0,
        0 //add data
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
        NULL, //controls
        0,
        0 //add data
    }
};

NCS_MNWND_TEMPLATE UnlockingActivity::window_template = {
        NCSCTRL_DIALOGBOX, 
        1,
        0, 0, 800, 480,
        WS_NONE,
        WS_EX_AUTOSECONDARYDC,
        NULL, /* caption */
        NULL,
        NULL,
        UnlockingActivity::message_handlers,
        UnlockingActivity::control_template,
        ARRAY_LEN(UnlockingActivity::control_template),
        0,
        0, 0,
};

BITMAP* UnlockingActivity::background_image = NULL;

UnlockingActivity::UnlockingActivity() : NCSActivity(&UnlockingActivity::window_template){
    m_style = STYLE_ZOOM;
    background_image = (BITMAP*)calloc(1, sizeof(BITMAP));
    assert(background_image);
    
    LoadBitmap(HDC_SCREEN, background_image, 
        "./res/images/unlocking/background.png");
}

UnlockingActivity::~UnlockingActivity() {
    UnloadBitmap(background_image);
    free(background_image);
}

