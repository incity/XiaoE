/*
 * \file mDialPad.h
 * \author miniStudio team of FMSoft
 * \date 2010/10/09
 *
 \verbatim

    This file is part of mGNCS4Touch, one of MiniGUI components.

    Copyright (C) 2008-2018 FMSoft (http://www.fmsoft.cn).

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Or,

    As this program is a library, any link to this program must follow
    GNU General Public License version 3 (GPLv3). If you cannot accept
    GPLv3, you need to be licensed from FMSoft.

    If you have got a commercial license of this program, please use it
    under the terms and conditions of the commercial license.

    For more information about the commercial license, please refer to
    <http://www.minigui.com/en/about/licensing-policy/>.

 \endverbatim
*/

#ifndef __MGNCS4TOUCH_DIALPAD_H__
#define __MGNCS4TOUCH_DIALPAD_H__

/**
 * \defgroup ControlDialPad mDialPad
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/**
 * \def NCSCTRL_DIALPAD
 * \brief the name of DialPad control
 */
#define NCSCTRL_DIALPAD              NCSCLASSNAME("DialPad")

typedef struct _mDialPad         mDialPad;
typedef struct _mDialPadClass    mDialPadClass;
typedef struct _mDialPadRenderer mDialPadRenderer;

#define mDialPadHeader(clsName) \
    mWidgetHeader(clsName) \
    int keypad_count; \
    char* keypad_scancode_array; \
    char** keypad_number_array; \
    char** keypad_letters_array; \
    PLOGFONT keypad_number_font; \
    PLOGFONT keypad_letters_font; \
    ARGB keypad_number_color; \
    ARGB keypad_letters_color; \
    ARGB keypad_bgcolor; \
    ARGB keypad_hi_bgcolor; \
    int keypad_radius; \
    int last_scancode; \
    HWND hwnd_target;



/**
 * \struct mDialPad
 * \brief DialPad class, derived from \ref mWidget
 *
 * \sa \ref mWidget
 */
struct _mDialPad {
    mDialPadHeader(mDialPad)
};

#define mDialPadClassHeader(clsName, parentClass)  \
    mWidgetClassHeader(clsName, parentClass)

/**
 * \struct mDialPadClass
 * \brief  DialPad struct of DialPad control, derived from \ref mWidgetClass
 *
 * \sa \ref mWidgetClass
 */
struct _mDialPadClass {
    mDialPadClassHeader(mDialPad, mWidget)
};

#define mDialPadRendererHeader(clsName, parentClass) \
    mWidgetRendererHeader(clsName, parentClass)

/**
 * \struct mDialPadRenderer
 * \brief DialPad class renderer interface, derived from \ref mWidgetRenderer
 *
 * \sa mDialPad, mDialPadClass, mWidgetRenderer
 */
struct _mDialPadRenderer {
    mDialPadRendererHeader(mDialPad, mWidget)
};

/**
 * \var g_stmDialPadCls
 * \brief global mDialPadClass
 */
MTOUCH_EXPORT extern mDialPadClass g_stmDialPadCls;

/**
 * \define mDialPadStyle
 * \brief the style id of \ref mDialPad
 */
#define NCSS_DIALPAD_SHIFT      (NCSS_WIDGET_SHIFT)

/**
 * \enum mDialPadProp
 * \brief the properties id of \ref mDialPad
 *
 * \var NCSP_DIALPAD_STATUS
 * \brief Label control displays the toggle status.
 */
enum mDialPadProp {
    NCSP_DIALPAD_STATUS = NCSP_WIDGET_MAX + 1,
    NCSP_DIALPAD_KEYPAD_NUM,
    NCSP_DIALPAD_KEYPAD_BGCOLOR,
    NCSP_DIALPAD_KEYPAD_HI_BGCOLOR,
    NCSP_DIALPAD_KEYPAD_RADIUS,
    NCSP_DIALPAD_KEYPAD_HSPACING,
    NCSP_DIALPAD_KEYPAD_VSPACING,
    NCSP_DIALPAD_KEYPAD_NUMBER_ARRAY,
    NCSP_DIALPAD_KEYPAD_LETTERS_ARRAY,
    NCSP_DIALPAD_KEYPAD_NUMBER_FONT,
    NCSP_DIALPAD_KEYPAD_LETTERS_FONT,
    NCSP_DIALPAD_KEYPAD_NUMBER_COLOR,
    NCSP_DIALPAD_KEYPAD_LETTERS_COLOR,
    NCSP_DIALPAD_LAST_SCANCODE,
    NCSP_DIALPAD_TARGET_HWND,
    NCSP_DIALPAD_MAX
};

/**
 * \enum eDialPadNotify
 * \brief the notification code of \ref mDialPad
 *
 * \var NCSN_DIALPAD_KEYPAD_CLICKED
 * \brief Identify toggle control choice status changes.
 */
enum mDialPadNotify {
    NCSN_DIALPAD_KEYPAD_CLICKED = NCSN_WIDGET_MAX + 1,
    NCSN_DIALPAD_MAX
};

/**
 * @} end of ControlDialPad
 */
#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* __MGNCS4TOUCH_DIALPAD_H__ */

