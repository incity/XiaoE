#include <cassert>
#include "NCSActivity.h"

#define HOOK_ONDESTROY 1
void global_onDestroy(mWidget* self, int message)
{
    printf("%s %d >>\n", __func__, __LINE__);
    Activity* activity = Activity::getActivityFromHWND(self->hwnd);
    if (NULL != activity) {
        NCSActivity* ncsActivity = dynamic_cast<NCSActivity*>(activity);
        assert(NULL != ncsActivity);
        if (NULL != ncsActivity) {
            ncsActivity->onDestroyOrigin(self, message);
        }
        delete ncsActivity;
    }
}

NCSActivity::NCSActivity(NCS_MNWND_TEMPLATE* _template) : 
    m_tmpl(_template), m_hPack(NULL), m_hIcon(NULL), m_hMenu(NULL)
{
#if HOOK_ONDESTROY
    if (NULL != _template) {
        int i = 0;
        const NCS_EVENT_HANDLER* store = _template->handlers;
        if (NULL != store) {
            NCS_MNWND_TEMPLATE* tmpl
                = (NCS_MNWND_TEMPLATE*)malloc(sizeof(*tmpl));
            memcpy(tmpl, _template, sizeof(*tmpl));
            while (true) {
                if (MSG_DESTROY == _template->handlers[i].message) {
                    int found = i;
                    // calculate how many message handlers in message map table.
                    while (++i) {
                        if (0 == _template->handlers[i].message && 
                                NULL == _template->handlers[i].handler) {
                            break;
                        }
                    }
                    m_onDestroyOrigin = reinterpret_cast<void (*)(mWidget*, int)>(_template->handlers[found].handler);
                    assert(m_onDestroyOrigin != global_onDestroy);

                    tmpl->handlers = (NCS_EVENT_HANDLER*)calloc(1, sizeof(NCS_EVENT_HANDLER) * (i + 1));
                    memcpy(tmpl->handlers, store, sizeof(NCS_EVENT_HANDLER) * (i + 1));
                    /* Overwrite the termination item of original NCS_EVENT_HANDLER table. */
                    tmpl->handlers[found].message = MSG_DESTROY;
                    tmpl->handlers[found].handler = reinterpret_cast<void*>(global_onDestroy);
                    m_tmpl = tmpl;

                    break;
                } else if (0 == _template->handlers[i].message && 
                    NULL == _template->handlers[i].handler) {
                    m_onDestroyOrigin = NULL;
                    tmpl->handlers = (NCS_EVENT_HANDLER*)calloc(1, sizeof(NCS_EVENT_HANDLER) * (i + 2));
                    memcpy(tmpl->handlers, store, sizeof(NCS_EVENT_HANDLER) * i + 1);
                    /* Overwrite the termination item of original NCS_EVENT_HANDLER table. */
                    tmpl->handlers[i].message = MSG_DESTROY;
                    tmpl->handlers[i].handler = reinterpret_cast<void*>(global_onDestroy);
                    m_tmpl = tmpl;
                    break;
                } else {
                }
                ++i;
            }
        }
    }
    else {
        // TODO: throw a exception.
    }
#endif
}

NCSActivity::~NCSActivity()
{
    printf("%s %d >>\n", __func__, __LINE__);
#if HOOK_ONDESTROY
    if (NULL != m_tmpl->handlers) { // If realloc the NCS_MNWND_TEMPLATE struct.
        NCS_MNWND_TEMPLATE* tmpl = const_cast<NCS_MNWND_TEMPLATE*>(m_tmpl);
        free(tmpl->handlers);
        free(tmpl);
    }
#endif
}


int NCSActivity::onResume()
{
    db_debug("%s:%s:%d >>\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}

int NCSActivity::onPause()
{
    db_debug("%s:%s:%d >>\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}

HWND NCSActivity::createHWND()
{
    mWidget* window = NULL;
    if (m_tmpl) {
        // Pre-set the additional data,
        // so we can call getActivityFromHWND() to get our Activity's pointer 
        // in MSG_CREATE message handler.
        m_tmpl->user_data = (DWORD)this;

        window = (mWidget*)ncsCreateMainWindowIndirect 
            (m_tmpl, HWND_DESKTOP);
    }
    else {
        /* TODO: Create main window from ID is not implemented. */
#if 0
        window = (mWidget*)ncsCreateMainWindowIndirectFromID (m_hPack, Uint32 wndId,
                    HWND owner, m_hIcon, m_hMenu,
                    NCS_EVENT_HANDLER_INFO* handlers,
					NCS_EVENT_CONNECT_INFO *connects,
					DWORD user_data);
#endif
    }
    return NULL != window ? window->hwnd : HWND_NULL;
}
