/**
 * \file mSwiper.h
 * \brief This file includes declaration of mSwiper.
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
#ifdef _MGNCSCTRL_ANIMATE

#ifndef _MGUI_NCSCTRL_SWIPER_H
#define _MGUI_NCSCTRL_SWIPER_H


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define NCSCTRL_SWIPER        NCSCLASSNAME("swiper")

typedef struct _mSwiper mSwiper;
typedef struct _mSwiperClass mSwiperClass;
typedef struct _mSwiperRenderer mSwiperRenderer;


#define mSwiperHeader(clsName) \
	mAnimateHeader(clsName) \
	unsigned int pagination_bullet_width:16; \
	unsigned int pagination_bullet_margin:8; \
	unsigned int pagination_bullet_padding:8;



struct _mSwiper
{
	mSwiperHeader(mSwiper)
};

#define mSwiperClassHeader(clsName, parentClass) \
	mAnimateClassHeader(clsName, parentClass)

struct _mSwiperClass
{
	mSwiperClassHeader(mSwiper, mAnimate)
};

#define mSwiperRendererHeader(clsName, parentClass) \
	mAnimateRendererHeader(clsName, parentClass)

struct _mSwiperRenderer {
	mSwiperRendererHeader(mSwiper, mAnimate)
};

MGNCS_EXPORT extern mSwiperClass g_stmSwiperCls;

enum mSwiperProp {
	NCSP_SWIPER_PAGINATION_BGCOLOR = NCSP_ANMT_MAX + 1,//id="18"
	NCSP_SWIPER_PAGINATION_BULLET_COLOR,
	NCSP_SWIPER_PAGINATION_BULLET_HILIGHT_COLOR,
	NCSP_SWIPER_PAGINATION_BULLET_WIDTH,
	NCSP_SWIPER_PAGINATION_BULLET_MARGIN,
	NCSP_SWIPER_PAGINATION_BULLET_PADDING,
	NCSP_SWIPER_MAX,
};

enum enumSwiperNotify{
	NCSN_SWIPER_MAX = NCSN_ANMT_MAX + 1
};


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif
#endif		//_MGNCSCTRL_ANIMATE
