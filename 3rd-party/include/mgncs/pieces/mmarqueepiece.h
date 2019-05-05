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
#ifndef _MGNCS_MARQUEEPIECE_H
#define _MGNCS_MARQUEEPIECE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _mMarqueePiece mMarqueePiece;
typedef struct _mMarqueePieceClass mMarqueePieceClass;

#define mMarqueePieceHeader(clss) \
        mLabelPieceHeader(clss) \
        unsigned short flags; \
        unsigned short scrollamount; \
        HDC  mem_dc; \
        unsigned int mem_w; \
        unsigned int mem_h; \
        int view_x; \
        int view_y; \

    
struct _mMarqueePiece
{
	mMarqueePieceHeader(mMarqueePiece)
};

#define mMarqueePieceClassHeader(clss, superCls) \
	mLabelPieceClassHeader(clss, superCls) \
	void (*reset)(mMarqueePiece *self);

struct _mMarqueePieceClass
{
	mMarqueePieceClassHeader(mMarqueePiece, mLabelPiece)
};

MGNCS_EXPORT extern mMarqueePieceClass g_stmMarqueePieceCls;

enum mMarqueePieceProps {
    NCSP_MARQUEEPIECE_SCROLL_AMOUNT = MARQUEEPIECE_PROP_BEGIN,
    NCSS_MARQUEEPIECE_DIRECTION_LEFT,
    NCSS_MARQUEEPIECE_DIRECTION_RIGHT,
    NCSS_MARQUEEPIECE_DIRECTION_UP,
    NCSS_MARQUEEPIECE_DIRECTION_DOWN,
    NCSS_MARQUEEPIECE_BEHAVIOR_ALTERNATE,
    NCSS_MARQUEEPIECE_BEHAVIOR_SCROLL,
    NCSS_MARQUEEPIECE_BEHAVIOR_SLIDE,
    NCSP_MARQUEEPIECE_AUTOPLAY,
};

// Marquee Flag
#define NCSS_MF_PLAY 0x010
#define NCSS_MF_AUTOPLAY 0x020
#define NCSS_MF_DIRECTION_LEFT 0x040
#define NCSS_MF_DIRECTION_RIGHT 0x080
#define NCSS_MF_DIRECTION_UP 0x100
#define NCSS_MF_DIRECTION_DOWN 0x200
#define NCSS_MF_BEHAVIOR_ALTERNATE 0x400
#define NCSS_MF_BEHAVIOR_SCROLL 0x800
#define NCSS_MF_BEHAVIOR_SLIDE 0x1000


#define mMarqueePiece_setDirectionLeft(self, bleft) \
	((bleft)?SET_BIT((self)->flags, NCSS_MF_DIRECTION_LEFT):CLEAR_BIT((self)->flags, NCSS_MF_DIRECTION_LEFT))
#define mMarqueePiece_isDirectionLeft(self)	\
	IS_BIT_SET((self)->flags, NCSS_MF_DIRECTION_LEFT)
    
#define mMarqueePiece_setDirectionRight(self, bright) \
	((bright)?SET_BIT((self)->flags, NCSS_MF_DIRECTION_RIGHT):CLEAR_BIT((self)->flags, NCSS_MF_DIRECTION_RIGHT))
#define mMarqueePiece_isDirectionRight(self)	\
	IS_BIT_SET((self)->flags, NCSS_MF_DIRECTION_RIGHT)
    
#define mMarqueePiece_setDirectionUp(self, bup) \
((bup)?SET_BIT((self)->flags, NCSS_MF_DIRECTION_UP):CLEAR_BIT((self)->flags, NCSS_MF_DIRECTION_UP))
#define mMarqueePiece_isDirectionUp(self)	\
	IS_BIT_SET((self)->flags, NCSS_MF_DIRECTION_UP)
    
#define mMarqueePiece_setDirectionDown(self, bdown) \
	((bdown)?SET_BIT((self)->flags, NCSS_MF_DIRECTION_DOWN):CLEAR_BIT((self)->flags, NCSS_MF_DIRECTION_DOWN))
#define mMarqueePiece_isDirectionDown(self)	\
	IS_BIT_SET((self)->flags, NCSS_MF_DIRECTION_DOWN)

#define mMarqueePiece_setBehaviorAlternate(self, balternate) \
	((balternate)?SET_BIT((self)->flags, NCSS_MF_BEHAVIOR_ALTERNATE):CLEAR_BIT((self)->flags, NCSS_MF_BEHAVIOR_ALTERNATE))
#define mMarqueePiece_isBehaviorAlternate(self)	\
	IS_BIT_SET((self)->flags, NCSS_MF_BEHAVIOR_ALTERNATE)

#define mMarqueePiece_setBehaviorScroll(self, bscroll) \
	((bscroll)?SET_BIT((self)->flags, NCSS_MF_BEHAVIOR_SCROLL):CLEAR_BIT((self)->flags, NCSS_MF_BEHAVIOR_SCROLL))
#define mMarqueePiece_isBehaviorScroll(self)	\
	IS_BIT_SET((self)->flags, NCSS_MF_BEHAVIOR_SCROLL)

#define mMarqueePiece_setBehaviorSlide(self, bslide) \
	((bslide)?SET_BIT((self)->flags, NCSS_MF_BEHAVIOR_SLIDE):CLEAR_BIT((self)->flags, NCSS_MF_BEHAVIOR_SLIDE))
#define mMarqueePiece_isBehaviorSlide(self)	\
	IS_BIT_SET((self)->flags, NCSS_MF_BEHAVIOR_SLIDE)
    
#define mMarqueePiece_setPlay(self, bplay) \
	((bplay)?SET_BIT((self)->flags, NCSS_MF_PLAY):CLEAR_BIT((self)->flags, NCSS_MF_PLAY))
#define mMarqueePiece_isPlay(self)	\
	IS_BIT_SET((self)->flags, NCSS_MF_PLAY)

#define mMarqueePiece_setAutoplay(self, bautoplay) \
	((bautoplay)?SET_BIT((self)->flags, NCSS_MF_AUTOPLAY):CLEAR_BIT((self)->flags, NCSS_MF_AUTOPLAY))
#define mMarqueePiece_isAutoplay(self)	\
	IS_BIT_SET((self)->flags, NCSS_MF_AUTOPLAY)

    
#ifdef __cplusplus
}
#endif

#endif
#endif		//_MGNCSCTRL_ANIMATE

