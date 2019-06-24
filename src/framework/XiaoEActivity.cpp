//1. The .cc .cpp .cxx related header files
#include "XiaoEActivity.h"
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

#undef LOG_TAG
#define LOG_TAG "XiaoEActivity"

XiaoEActivity::XiaoEActivity(NCS_MNWND_TEMPLATE* _template) : NCSActivity(_template)
{
    //if(!_template->handlers)
      //  _template->handlers = _message_handlers;
}

XiaoEActivity::~XiaoEActivity()
{
    db_debug("%s %d >>\n", __func__, __LINE__);
}

void XiaoEActivity::addControl(NCS_WND_TEMPLATE* ctrl, int count)
{
    assert(ctrl && count);
    int i;

    for(i = 0; i < count; i++)
        _mControls.push_back(&ctrl[i]);
}

BOOL XiaoEActivity::createControls(mMainWnd* self)
{
    int i;
    printf("%s:%d >> control count:%d\n", __func__, __LINE__, _mControls.size());
    
    for(i = 0; i < _mControls.size(); i++) {
        _c(self)->addChildren(self, _mControls[i], 1);        
        printf("%s %d : >>\n", __func__, __LINE__);
    }
    
    printf("%s %d : >>\n", __func__, __LINE__);
    return true;
}

static inline XiaoEActivity* _this_activity(mMainWnd* self)
{
    return dynamic_cast<XiaoEActivity*>(Activity::getActivityFromHWND(self->hwnd));
}

BOOL XiaoEActivity::_onCreate(mMainWnd* self, DWORD dwAddData )
{
    XiaoEActivity* _this = _this_activity(self);
    printf("%s %d : >>\n", __func__, __LINE__);
    _this->createControls(self);

    printf("%s %d : >>\n", __func__, __LINE__);
    return _this->onCreate(self, dwAddData);
}

void XiaoEActivity::_onPaint(mMainWnd *self, HDC hdc, const CLIPRGN* inv)
{
    XiaoEActivity* _this = _this_activity(self);
    _this->onPaint(self, hdc, inv);
}

BOOL XiaoEActivity::_onEraseBackground(mMainWnd *self, HDC hdc, const PRECT clip)
{
    XiaoEActivity* _this = _this_activity(self);
    return _this->onEraseBackground(self, hdc, clip);
}

BOOL XiaoEActivity::_onScreensave(mMainWnd* self, int message, WPARAM wParam, LPARAM lParam)
{
    XiaoEActivity* _this = _this_activity(self);
    return _this->onScreensave(self, message, wParam, lParam);
}

BOOL XiaoEActivity::_onCallback(mMainWnd* self, int message, WPARAM wParam, LPARAM lParam)
{
    Handler func = (Handler)wParam;
    func(self, (DWORD)lParam);
    return TRUE;
}

BOOL XiaoEActivity::_onIntent(mMainWnd* self, int message, WPARAM wParam, LPARAM lParam)
{
    XiaoEActivity* _this = _this_activity(self);
    Intent* intent = (Intent*)wParam;
    int ret = _this->onIntent(self, message, wParam, lParam);
    if(intent)
        Intent::deleteIntent(intent);

    return ret;
}

NCS_EVENT_HANDLER XiaoEActivity::_message_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(XiaoEActivity::_onCreate)},
    {MSG_PAINT, NCS_EVENT_HANDLER_CAST(XiaoEActivity::_onPaint)},
    {MSG_ERASEBKGND, NCS_EVENT_HANDLER_CAST(XiaoEActivity::_onEraseBackground)},
    {Activity::MSG_SCREENSAVE, NCS_EVENT_HANDLER_CAST(XiaoEActivity::_onScreensave)},
    {XiaoEActivity::MSG_CALLBACK, NCS_EVENT_HANDLER_CAST(XiaoEActivity::_onCallback)},
    {XiaoEActivity::MSG_INTENT, NCS_EVENT_HANDLER_CAST(XiaoEActivity::_onIntent)},
    {0, NULL}
};

bool XiaoEActivity::runOnUiThread(HWND hWnd,
                                 Handler handler,
                                 DWORD param)
{
    // TODO: check the if clause
    //if(hWnd && ACTIVITYSTACK.top()->hwnd() == hWnd)
        return PostMessage(hWnd, MSG_CALLBACK, 
                           (WPARAM)handler, (LPARAM)param) == 0;
    //return false;
}
