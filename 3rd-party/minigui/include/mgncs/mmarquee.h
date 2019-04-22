/**
 * \file manimate.h
 * \brief This file includes declaration of mMarquee.
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

#ifndef _MGUI_NCSCTRL_MARQUEE_H
#define _MGUI_NCSCTRL_MARQUEE_H


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define NCSCTRL_MARQUEE        NCSCLASSNAME("marquee")

typedef struct _mMarquee mMarquee;
typedef struct _mMarqueeClass mMarqueeClass;
typedef struct _mMarqueeRenderer mMarqueeRenderer;

// direction 表示滚动的方向，值可以是left，right，up，down，默认为left 
// behavior 表示滚动的方式，值可以是scroll(连续滚动)slide(滑动一次)alternate(来回滚动) 
// loop 表示循环的次数，值是正整数，默认为无限循环 
// hspace、vspace 表示元素到区域边界的水平距离和垂直距离，值是正整数，单位是像素。
#define mMarqueeHeader(clsName) \
    mStaticHeader(clsName)    \
    unsigned int state:4;  \
    unsigned int scrolldelay:28; \
    unsigned int loop; \
    unsigned int hspace:16; \
    unsigned int vspace:16; \
    unsigned int paint_flag; \
    HDC  mem_dc;

struct _mMarquee
{
    mMarqueeHeader(mMarquee)
};

#define mMarqueeClassHeader(clsName, parentClass) \
    mStaticClassHeader(clsName, parentClass) \
    BOOL (*play)(clsName*); \
    BOOL (*pauseResume)(clsName*); \
    BOOL (*stop)(clsName*);

struct _mMarqueeClass
{
    mMarqueeClassHeader(mMarquee, mStatic)
};

#define mMarqueeRendererHeader(clsName, parentClass) \
    mStaticRendererHeader(clsName, parentClass)

struct _mMarqueeRenderer {
    mMarqueeRendererHeader(mMarquee, mStatic)
};

MGNCS_EXPORT extern mMarqueeClass g_stmMarqueeCls;

enum mMarqueeProp {
    NCSP_MARQUEE_SCROLL_DELAY = NCSP_STATIC_MAX + 1,
    NCSP_MARQUEE_SCROLL_AMOUNT,
    NCSP_MARQUEE_HSPACE,
    NCSP_MARQUEE_VSPACE,
    NCSP_MARQUEE_MAX,
};

#define NCSS_MARQUEE_SHIFT  (NCSS_STATIC_SHIFT + 1)

#define NCSS_MARQUEE_DIRECTION_LEFT (0x1<<NCSS_MARQUEE_SHIFT)

#define NCSS_MARQUEE_DIRECTION_RIGHT    (0x2<<NCSS_MARQUEE_SHIFT)

#define NCSS_MARQUEE_DIRECTION_UP    (0x4<<NCSS_MARQUEE_SHIFT)

#define NCSS_MARQUEE_DIRECTION_DOWN    (0x8<<NCSS_MARQUEE_SHIFT)

//来回滚动
#define NCSS_MARQUEE_BEHAVIOR_ALTERNATE    (0x10<<NCSS_MARQUEE_SHIFT)

//单方向循环滚动
#define NCSS_MARQUEE_BEHAVIOR_SCROLL    (0x20<<NCSS_MARQUEE_SHIFT)

//滚动一次(TODO: 后续实现)
#define NCSS_MARQUEE_BEHAVIOR_SLIDE    (0x40<<NCSS_MARQUEE_SHIFT)

#define NCSS_MARQUEE_AUTOPLAY   (0x80<<NCSS_MARQUEE_SHIFT) //0x400

enum enumMarqueeNotify{
    NCSN_MARQUEE_MAX = NCSN_STATIC_MAX + 1
};

#define MARQUEE_PLAY 0x01
#define MARQUEE_PAUSE 0x02
#define MARQUEE_STOP 0x04
#define MARQUEE_STARTPLAY 0xF112
#define MARQUEE_PAUSE_RESUME 0xF113
#define MARQUEE_STOPPLAY 0xF114

#define ncsMarqueeStart(self)  ((self)?_c(self)->play(self):FALSE)

#define ncsMarqueePauseResume(self)  ((self)?_c(self)->pauseResume(self):FALSE)

#define ncsMarqueeStop(self) ((self)?_c(self)->stop(self):FALSE)

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif
#endif        //_MGNCSCTRL_ANIMATE
