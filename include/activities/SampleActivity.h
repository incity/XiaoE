#ifndef SAMPLE_ACTIVITY_HH
#define SAMPLE_ACTIVITY_HH

#include "NCSActivity.h"

class SampleActivity : public NCSActivity {
public:
    SampleActivity();
    ~SampleActivity();

protected:
    /* must be static because of the 'this' pointer. */
    static void onPaint(mWidget *self, HDC hdc, const CLIPRGN* inv);
    static NCS_EVENT_HANDLER message_handlers[];
    static NCS_MNWND_TEMPLATE window_template;
};
#endif

