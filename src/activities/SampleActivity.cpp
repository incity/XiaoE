#include "SampleActivity.h"

AUTO_REGISTER_ACTIVITY(SampleActivity);

void SampleActivity::onPaint(mWidget *self, HDC hdc, const CLIPRGN* inv)
{
    RECT rt;
    GetClientRect(self->hwnd, &rt);
    DrawText(hdc, "Hello, XiaoE!", -1, &rt, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
}

NCS_EVENT_HANDLER SampleActivity::message_handlers [] = {
        {MSG_PAINT, NCS_EVENT_HANDLER_CAST(SampleActivity::onPaint)},
        {0, NULL}
};

NCS_MNWND_TEMPLATE SampleActivity::window_template = {
        NCSCTRL_DIALOGBOX, 
        1,
        0, 0, 800, 480,
        WS_NONE,
        WS_EX_NONE,
        "This is a sample.",
        NULL,
        NULL,
        SampleActivity::message_handlers,
        NULL,
        0,
        0,
        0, 0,
};

SampleActivity::SampleActivity() : NCSActivity(&SampleActivity::window_template){
    m_style = STYLE_PUSH;
}

SampleActivity::~SampleActivity() {
}

