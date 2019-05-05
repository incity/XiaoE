/*
 *   This file is part of mGNCS, a component for MiniGUI.
 *
 *   Copyright (C) 2008~2018, Beijing FMSoft Technologies Co., Ltd.
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Or,
 *
 *   As this program is a library, any link to this program must follow
 *   GNU General Public License version 3 (GPLv3). If you cannot accept
 *   GPLv3, you need to be licensed from FMSoft.
 *
 *   If you have got a commercial license of this program, please use it
 *   under the terms and conditions of the commercial license.
 *
 *   For more information about the commercial license, please refer to
 *   <http://www.minigui.com/en/about/licensing-policy/>.
 */
#ifdef _MGNCSCTRL_ANIMATE
#ifndef _MGNCS_SWIPERPIECE_H
#define _MGNCS_SWIPERPIECE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _mSwiperPiece mSwiperPiece;
typedef struct _mSwiperPieceClass mSwiperPieceClass;

#define mSwiperPieceHeader(clss) \
	mAnimatePieceHeader(clss) \
	unsigned int pagination; \
	DWORD32 pagination_bgcolor; \
	DWORD32 pagination_bullet_color; \
	DWORD32 pagination_bullet_hilight_color; \
	unsigned int pagination_bullet_width:16; \
	unsigned int pagination_bullet_margin:8; \
	unsigned int pagination_bullet_padding:8;

struct _mSwiperPiece
{
	mSwiperPieceHeader(mSwiperPiece)
};

#define mSwiperPieceClassHeader(clss, superCls) \
	mAnimatePieceClassHeader(clss, superCls)

struct _mSwiperPieceClass
{
	mSwiperPieceClassHeader(mSwiperPiece, mAnimatePiece)
};

MGNCS_EXPORT extern mSwiperPieceClass g_stmSwiperPieceCls;

enum mSwiperPieceProps {
	NCSP_SWIPERPIECE_PAGINATION_BGCOLOR = SWIPERPIECE_PROP_BEGIN,
	NCSP_SWIPERPIECE_PAGINATION_BULLET_COLOR,
	NCSP_SWIPERPIECE_PAGINATION_BULLET_HILIGHT_COLOR,
	NCSP_SWIPERPIECE_PAGINATION_BULLET_WIDTH,
	NCSP_SWIPERPIECE_PAGINATION_BULLET_MARGIN,
	NCSP_SWIPERPIECE_PAGINATION_BULLET_PADDING,

};


#ifdef __cplusplus
}
#endif

#endif
#endif		//_MGNCSCTRL_ANIMATE

