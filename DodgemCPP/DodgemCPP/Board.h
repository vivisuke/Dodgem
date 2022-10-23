//----------------------------------------------------------------------
//
//			File:			"Board.h"
//			Created:		22-10-2022
//			Author:			津田伸秀
//			Description:
//
//----------------------------------------------------------------------

#pragma once

#include <vector>

typedef unsigned char uchar;

/*

	３＞・・
	２＞・・
	１・▲▲
	　ａｂｃ

*/

enum {
	EMPTY = 0,
	RED,			//	▲
	BLUE,			//	＞
	WALL,
	N_HORZ = 3,
	N_VERT = N_HORZ,
	ARY_WIDTH = N_HORZ + 1,
	ARY_HEIGHT = N_VERT + 2,
	ARY_SIZE = ARY_WIDTH * ARY_HEIGHT + 1,
};

inline int xyToIX(int x, int y) {		//	x: [0, N_HORZ-1],  y: [0, N_VERT-1]
	return (y+1)*ARY_WIDTH + (x+1);
}

struct Move {
public:
	Move(uchar src = 0, uchar dst = 0)
		: m_src(src)
		, m_dst(dst)
	{
	};
public:
	uchar	m_src;
	uchar	m_dst;
};
typedef std::vector<Move> Moves;

class Board {
public:
	Board() { init(); }
public:
	void	print() const;
	void	get_red_moves(Moves&) const;
public:
	void	init();
public:
	uchar	m_ary[ARY_SIZE];
};
