
#ifndef _NCSCTRL_TEXTVIEW_H
#define _NCSCTRL_TEXTVIEW_H

#include <mgncs4touch/mgncs4touch.h>

#define NCSCTRL_TEXTVIEW   NCSCLASSNAME("textview")

enum mTextViewProp {
    NCSP_TEXTVIEW_RADIUS = NCSP_WIDGET_MAX + 1,
    NCSP_TEXTVIEW_CORNERFLAG,
    NCSP_TEXTVIEW_BKCOLOR, // use GetWindowBkColor(self->hwnd); ???
    NCSP_TEXTVIEW_ALIGN,
    NCSP_TEXTVIEW_VALIGN,
    NCSP_TEXTVIEW_AUTOWRAP,
    NCSP_TEXTVIEW_MAX
};

/**
 * \def NCSS_TEXTVIEW_HORIZONTAL
 * \brief horizontal textview
 */
#define NCSS_TEXTVIEW_HORIZONTAL          0x0000L

/**
 * \def NCSS_TEXTVIEW_VERTICAL
 * \brief vertical textview
 */
#define NCSS_TEXTVIEW_VERTICAL            (0x0001L<<NCSS_WIDGET_SHIFT)


/**
 * \enum mTextViewNotify
 * \brief the notification code of \ref mTextView
 *
 */
enum mTextViewNotify {
    NCSN_TEXTVIEW_CHANGED = NCSN_WIDGET_MAX + 1,
    NCSN_TEXTVIEW_ENTERED,
    NCSN_TEXTVIEW_MAX,
};


DECLARE_OBJECT(mTextView)

#define mTextViewHeader(clsName) \
        mWidgetHeader(clsName) \
        mTextPiece *textpiece;        

#define mTextViewClassHeader(clsName, parentClass) \
        mWidgetClassHeader(clsName, parentClass) \
        void (*getMaxSize)(clsName*, SIZE*);

typedef mWidgetRenderer mTextViewRenderer;
DEFINE_OBJECT(mTextView, mWidget)


#endif /*_NCSCTRL_TEXTVIEW_H*/
