/*
 * \file mpopupdialog.h
 * \author suyc
 * \date 2019/02/12
 *
 * This file include the dialog defines
 *
 \verbatim

    This file is part of mGNCS, a component for MiniGUI.

    Copyright (C) 2008~2018, Beijing FMSoft Technologies Co., Ltd.

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

#ifdef _MGNCSCTRL_DIALOGBOX

#ifndef _MGUI_CTRL_POPUPDLG_H
#define _MGUI_CTRL_POPUPDLG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup PopupDialog mPopupDialog
 * @{
 */

/**
 * \def NCSCTRL_POPUPDIALOG
 * \brief the name of \ref mPopupDialog control
 */
#define NCSCTRL_POPUPDIALOG NCSCLASSNAME("popupdialog")

typedef struct _mPopupDialog mPopupDialog;
typedef struct _mPopupDialogClass mPopupDialogClass;
typedef struct _mPopupDialogRenderer mPopupDialogRenderer;

/* define mPopupDialogRenderer */
#define mPopupDialogRendererHeader(clsName, parentClass) \
	mDialogBoxRendererHeader(clsName, parentClass)

/**
 * \struct mPopupDialogRenderer
 * \brief the renerer interface of \ref mPopupDialog, inherit from \ref mDialogBoxRenderer
 *
 * \sa mPopupDialog, mPopupDialogClass
 */

struct _mPopupDialogRenderer {
	mPopupDialogRendererHeader(mPopupDialog, mDialogBox)
};

/* define mPopupDialog */
#define mPopupDialogHeader(className) \
	mDialogBoxHeader(className) \
	int first_idle;

/**
 * \struct mPopupDialog
 * \brief the members of mPopupDialog, inherit from mDialogBox
 *
 *  - DWORD \b modeRetValue;\n
 *    The return value after a dialog leave Mode state, return by \b doModal
 *
 * \sa mPopupDialogClass
 */
struct _mPopupDialog{
	mPopupDialogHeader(mPopupDialog)
};

/* define mPopupDialogClass */
#define mPopupDialogClassHeader(clsName, parentClass)    \
	mDialogBoxClassHeader(clsName, parentClass)

/**
 * \struct mPopupDialogClass
 * \brief the VTable of \ref mPopupDialog, inherit from mPopupDialogClass
 *
 * \sa mPopupDialog
 *
 */

struct _mPopupDialogClass
{
	mPopupDialogClassHeader(mPopupDialog, mDialogBox)
};

/**
 * \var g_stmPopupDialogCls
 * \brief the singleton of mPopupDialogClass
 */
MGNCS_EXPORT extern mPopupDialogClass g_stmPopupDialogCls; //Class(mPopupDialog);


#define NCSS_POPUPDLG_SHIFT  NCSS_DLGBOX_SHIFT

enum enumPopupDialogNotify {
	NCSN_POPUPDLG_MAX = NCSN_DLGBOX_MAX + 1
};

/** @} end of PopupDialog */

#ifdef __cplusplus
}
#endif

#endif
#endif
