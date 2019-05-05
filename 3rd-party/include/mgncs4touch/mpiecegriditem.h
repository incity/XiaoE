/*
 * \file 
 * \author FMSoft
 * \date 
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

#ifndef  MPIECEGRIDITEM_INC
#define  MPIECEGRIDITEM_INC

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _mPieceGridItemClass mPieceGridItemClass;
typedef struct _mPieceGridItem mPieceGridItem;

enum LayoutGravity{
    LAYOUT_GRAVITY_Fill,
};


#define mPieceGridItemHeader(clss) \
    mPieceItemHeader(clss) \
    int row, colum; \
    int rowSpan, columSpan; \
    enum LayoutGravity gravity; \


#define mPieceGridItemClassHeader(clss, superCls) \
    mPieceItemClassHeader(clss, superCls)  \
    void (*setGravity)(clss*, enum LayoutGravity);    \
    void (*setRow)(clss*, int);    \
    void (*setColum)(clss*, int);    \
    void (*setRowSpan)(clss*, int);    \
    void (*setColumSpan)(clss*, int);    \
    int  (*getGravity)(clss*);    \
    int  (*getRow)(clss*);    \
    int  (*getColum)(clss*);    \
    int  (*getRowSpan)(clss*);    \
    int  (*getColumSpan)(clss*);    \



struct _mPieceGridItem
{   
    mPieceGridItemHeader(mPieceGridItem)
};

struct _mPieceGridItemClass
{   
    mPieceGridItemClassHeader(mPieceGridItem, mPieceItem)
};

MGNCS_EXPORT extern mPieceGridItemClass g_stmPieceGridItemCls;

#ifdef __cplusplus
}
#endif

#endif   /* ----- #ifndef MPIECEGRIDITEM_INC  ----- */

