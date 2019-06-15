#include "XiaoEActivity.h"

#undef LOG_TAG
#define LOG_TAG "XiaoEActivity"

BOOL XiaoEActivity::_onCreate(mMainWnd* self, DWORD dwAddData )
{
    XiaoEActivity* _this = (XiaoEActivity*)Activity::getActivityFromHWND(self->hwnd);
    return _this->onCreate(self, dwAddData);
}

void XiaoEActivity::_onPaint(mMainWnd *self, HDC hdc, const CLIPRGN* inv)
{
    XiaoEActivity* _this = (XiaoEActivity*)Activity::getActivityFromHWND(self->hwnd);
    _this->onPaint(self, hdc, inv);
}

BOOL XiaoEActivity::_onEraseBackground(mMainWnd *self, HDC hdc, const PRECT clip)
{
    XiaoEActivity* _this = (XiaoEActivity*)Activity::getActivityFromHWND(self->hwnd);
    return _this->onEraseBackground(self, hdc, clip);
}

BOOL XiaoEActivity::_onScreensave(mMainWnd* self, int message, WPARAM wParam, LPARAM lParam)
{
    XiaoEActivity* _this = (XiaoEActivity*)Activity::getActivityFromHWND(self->hwnd);
    return _this->onScreensave(self, message, wParam, lParam);
}

BOOL XiaoEActivity::_onCallback(mMainWnd* self, int message, WPARAM wParam, LPARAM lParam)
{
    Handler func = (Handler)wParam;
    func(self, (DWORD)lParam);
    return TRUE;
}

NCS_EVENT_HANDLER XiaoEActivity::_message_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(XiaoEActivity::_onCreate)},
    {MSG_PAINT, NCS_EVENT_HANDLER_CAST(XiaoEActivity::_onPaint)},
    {MSG_ERASEBKGND, NCS_EVENT_HANDLER_CAST(XiaoEActivity::_onEraseBackground)},
    {Activity::MSG_SCREENSAVE, NCS_EVENT_HANDLER_CAST(XiaoEActivity::_onScreensave)},
    {XiaoEActivity::MSG_CALLBACK, NCS_EVENT_HANDLER_CAST(XiaoEActivity::_onCallback)},
    {0, NULL}
};

XiaoEActivity::XiaoEActivity(NCS_MNWND_TEMPLATE* _template) : NCSActivity(_template)
{
    //if(!_template->handlers)
      //  _template->handlers = _message_handlers;
}

XiaoEActivity::~XiaoEActivity()
{
}

