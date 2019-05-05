
#ifndef _NCSCTRL_PASSWORDBOX_H
#define _NCSCTRL_PASSWORDBOX_H

#include <mgncs4touch/mgncs4touch.h>

#define NCSCTRL_PASSWORDBOX   NCSCLASSNAME("passwordbox")

enum mPasswordBoxProp {
    NCSP_PASSWORDBOX_RADIUS = NCSP_WIDGET_MAX + 1,
    NCSP_PASSWORDBOX_CORNERFLAG,
    NCSP_PASSWORDBOX_BKCOLOR, // use GetWindowBkColor(self->hwnd); ???
    NCSP_PASSWORDBOX_COLOR,
    NCSP_PASSWORDBOX_PASSWORD_CHAR,
    NCSP_PASSWORDBOX_MAX_LENGTH,
    NCSP_PASSWORDBOX_CELL_RADIUS,
    NCSP_PASSWORDBOX_CELL_WIDTH,
    NCSP_PASSWORDBOX_CELL_HEIGHT,
    NCSP_PASSWORDBOX_CELL_BKCOLOR,
    NCSP_PASSWORDBOX_MAX
};

/**
 * \enum mPasswordBoxNotify
 * \brief the notification code of \ref mPasswordBox
 *
 */
enum mPasswordBoxNotify {
    NCSN_PASSWORDBOX_CHANGED = NCSN_WIDGET_MAX + 1,
    NCSN_PASSWORDBOX_ENTERED,
    NCSN_PASSWORDBOX_MAX,
};

#define NCSS_PASSWORDBOX_BKGRADIENT (1<<NCSS_WIDGET_SHIFT)

DECLARE_OBJECT(mPasswordBox)

#define mPasswordBoxHeader(clsName) \
        mWidgetHeader(clsName) \
        int max_password_length; \
        char *password; \
        char *password2; \
        char *password_char; \
        mShapeTransRoundPiece* cell_backpiece; \
        mTextPiece **password_pieces;        

#define mPasswordBoxClassHeader(clsName, parentClass) \
        mWidgetClassHeader(clsName, parentClass) \
        void (*clear)(clsName*);

typedef mWidgetRenderer mPasswordBoxRenderer;
DEFINE_OBJECT(mPasswordBox, mWidget)


#endif /*_NCSCTRL_PASSWORDBOX_H*/
