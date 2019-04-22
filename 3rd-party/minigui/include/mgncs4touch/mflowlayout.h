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

#ifndef _MGNCS_MFLOWLAYOUT_H
#define _MGNCS_MFLOWLAYOUT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _mFlowLayout mFlowLayout;
typedef struct _mFlowLayoutClass mFlowLayoutClass;
enum FlowLayoutHAlign{
    FLOW_LAYOUT_HALIGN_LEFT,
    FLOW_LAYOUT_HALIGN_CENTER,
    FLOW_LAYOUT_HALIGN_RIGHT,
};
    
enum FlowLayoutVAlign{
    FLOW_LAYOUT_VALIGN_TOP,
    FLOW_LAYOUT_VALIGN_CENTER,
    FLOW_LAYOUT_VALIGN_BOTTOM,
};
    

#define mFlowLayoutHeader(clss) \
    mLayoutManagerHeader(clss) \
    int hgap:14; \
    int vgap:14; \
    unsigned int halign:2; \
    unsigned int valign:2;

struct _mFlowLayout
{
    mFlowLayoutHeader(mFlowLayout)
};

#define mFlowLayoutClassHeader(clss, superCls) \
    mLayoutManagerClassHeader(clss, superCls) \
    void (*setHgap)(clss*, int); \
    void (*setVgap)(clss*, int); \
    void (*setHAlignment)(clss*, enum FlowLayoutHAlign); \
    void (*setVAlignment)(clss*, enum FlowLayoutVAlign); \
    int (*getHgap)(clss*); \
    int (*getVgap)(clss*); \
    enum FlowLayoutHAlign (*getHAlignment)(clss*); \
    enum FlowLayoutVAlign (*getVAlignment)(clss*);




struct _mFlowLayoutClass
{
    mFlowLayoutClassHeader(mFlowLayout, mLayoutManager)
};

MGNCS_EXPORT extern mFlowLayoutClass g_stmFlowLayoutCls;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MGNCS_MFLOWLAYOUT_H */
