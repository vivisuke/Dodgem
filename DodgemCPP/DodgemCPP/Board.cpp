//----------------------------------------------------------------------
//
//			File:			"Board.cpp"
//			Created:		22-10-2022
//			Author:			津田伸秀
//			Description:
//
//----------------------------------------------------------------------

#include <iostream>
#include "Board.h"

using namespace std;

void Board::init() {
	for(int i = 0; i != ARY_SIZE; ++i)
		m_ary[i] = WALL;
	for(int y = 0; y != N_VERT; ++y) {
		for (int x = 0; x != N_HORZ; ++x) {
			m_ary[xyToIX(x, y)] = EMPTY;
		}
	}
	for(int k = 1; k != N_HORZ; ++k) {
		m_ary[xyToIX(k, 0)] = RED;
		m_ary[xyToIX(0, k)] = BLUE;
	}
}
void Board::print() const {
	for(int y = N_VERT; --y >= 0; ) {
		for (int x = 0; x != N_HORZ; ++x) {
			switch( m_ary[xyToIX(x, y)] ) {
			case EMPTY:	cout << "・";	break;
			case RED:	cout << "Ａ";	break;
			case BLUE:	cout << "＞";	break;
			}
		}
		cout << "\n";
	}
	cout << "\n";
}
void Board::get_red_moves(Moves& lst) const {
	lst.clear();
	for(int y = 0; y != N_VERT; ++y) {
		for (int x = 0; x != N_HORZ; ++x) {
			int ix = xyToIX(x, y);
			if( m_ary[ix] == RED ) {
				if( m_ary[ix+ARY_WIDTH] == EMPTY || y == N_VERT - 1 )
					lst.push_back(Move(ix, ix+ARY_WIDTH));
				if( m_ary[ix-1] == EMPTY )
					lst.push_back(Move(ix, ix-1));
				if( m_ary[ix+1] == EMPTY )
					lst.push_back(Move(ix, ix+1));
			}
		}
	}
}
void Board::get_blue_moves(Moves& lst) const {
	lst.clear();
	for (int x = 0; x != N_HORZ; ++x) {
		for(int y = 0; y != N_VERT; ++y) {
			int ix = xyToIX(x, y);
			if( m_ary[ix] == BLUE ) {
				if( m_ary[ix+1] == EMPTY || x == N_HORZ - 1 )
					lst.push_back(Move(ix, ix+1));
				if( m_ary[ix-ARY_WIDTH] == EMPTY )
					lst.push_back(Move(ix, ix-ARY_WIDTH));
				if( m_ary[ix+ARY_WIDTH] == EMPTY )
					lst.push_back(Move(ix, ix+ARY_WIDTH));
			}
		}
	}
}
