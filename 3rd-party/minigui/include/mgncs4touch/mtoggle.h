/*
 * \file mToggle.h
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

#ifndef __MGNCS4TOUCH_TOGGLE_H__
#define __MGNCS4TOUCH_TOGGLE_H__

#undef BACKUP_BACKGROUND_DC
/**
 * \defgroup ControlToggle mToggle
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/**
 * \def NCSCTRL_TOGGLE
 * \brief the name of Toggle control
 */
#define NCSCTRL_TOGGLE              NCSCLASSNAME("Toggle")

typedef struct _mToggle         mToggle;
typedef struct _mToggleClass    mToggleClass;
typedef struct _mToggleRenderer mToggleRenderer;

/**
 * \enum eToggleCheckState
 * \brief define the check state of Toggle
 *
 * \var NCS_TOGGLE_OFF
 * \brief Toggle status, OFF
 *
 * \var NCS_TOGGLE_ON
 * \brief Toggle status, ON
 */
enum mToggleStatus {
    NCS_TOGGLE_OFF = 0,
    NCS_TOGGLE_ON
};

#define mToggleHeader(clsName) \
    mWidgetHeader(clsName)           \
    DWORD status;                    \
    DWORD checked_bgcolor;  \
    DWORD checked_bordercolor;  \
    DWORD unchecked_bgcolor;  \
    DWORD unchecked_bordercolor;  \
    int   mouseX;                       \
    DWORD bgcolor;                \
    DWORD bordercolor; 
/*
#if BACKUP_BACKGROUND_DC
    HDC backup_of_bg_dc;      \
#endif
*/
/**
 * \struct mToggle
 * \brief Toggle class, derived from \ref mWidget
 *
 * -int \b status - the toggle status, 0-OFF, 1-ON
 *
 * \sa \ref mWidget
 */
struct _mToggle {
    mToggleHeader(mToggle)
};

#define mToggleClassHeader(clsName, parentClass)  \
    mWidgetClassHeader(clsName, parentClass)            \
    void (*runAnimation)(clsName*, int start, int end, int duration);

/**
 * \struct mToggleClass
 * \brief  Toggle struct of Toggle control, derived from \ref mWidgetClass
 *
 * \sa \ref mWidgetClass
 */
struct _mToggleClass {
    mToggleClassHeader(mToggle, mWidget)
};

#define mToggleRendererHeader(clsName, parentClass) \
    mWidgetRendererHeader(clsName, parentClass)

/**
 * \struct mToggleRenderer
 * \brief Toggle class renderer interface, derived from \ref mWidgetRenderer
 *
 * \sa mToggle, mToggleClass, mWidgetRenderer
 */
struct _mToggleRenderer {
    mToggleRendererHeader(mToggle, mWidget)
};

/**
 * \var g_stmToggleCls
 * \brief global mToggleClass
 */
MTOUCH_EXPORT extern mToggleClass g_stmToggleCls;

/**
 * \define mToggleStyle
 * \brief the style id of \ref mToggle
 */
#define NCSS_TOGGLE_SHIFT      (NCSS_WIDGET_SHIFT)

/**
 * \enum mToggleProp
 * \brief the properties id of \ref mToggle
 *
 * \var NCSP_TOGGLE_STATUS
 * \brief Label control displays the toggle status.
 */
enum mToggleProp {
    NCSP_TOGGLE_STATUS = NCSP_WIDGET_MAX + 1,
    NCSP_TOGGLE_CHECKED_BGCOLOR,
    NCSP_TOGGLE_CHECKED_BORDERCOLOR,
    NCSP_TOGGLE_UNCHECKED_BGCOLOR,
    NCSP_TOGGLE_UNCHECKED_BORDERCOLOR,
    NCSP_TOGGLE_MAX
};

/**
 * \enum eToggleNotify
 * \brief the notification code of \ref mToggle
 *
 * \var NCSN_TOGGLE_STATUSCHANGED
 * \brief Identify toggle control choice status changes.
 */
enum mToggleNotify {
    NCSN_TOGGLE_STATUSCHANGED = NCSN_WIDGET_MAX + 1,
    NCSN_TOGGLE_MAX
};

/**
 * @} end of ControlToggle
 */
#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* __MGNCS4TOUCH_TOGGLE_H__ */

