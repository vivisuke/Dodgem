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
	for(int i = 0; i != ARY_SIZE; ++i) m_ary[i] = WALL;		//	周りは全部壁（含ゴール）
	for(int y = 0; y != N_VERT; ++y) {
		for (int x = 0; x != N_HORZ; ++x) {
			m_ary[xyToIX(x, y)] = EMPTY;
		}
	}
	for(int k = 1; k != N_HORZ; ++k) {
		m_ary[xyToIX(k, 0)] = RED;
		m_ary[xyToIX(0, k)] = BLUE;
	}
	m_n_red = m_n_blue = N_HORZ - 1;
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
void Board::do_move_red(const Move& mv) {
	if( m_ary[mv.m_dst] != WALL )
		m_ary[mv.m_dst] = RED;
	else {
		--m_n_red;
	}
	m_ary[mv.m_src] = EMPTY;
}
void Board::do_move_blue(const Move& mv) {
	if( m_ary[mv.m_dst] != WALL )
		m_ary[mv.m_dst] = BLUE;
	else {
		--m_n_blue;
	}
	m_ary[mv.m_src] = EMPTY;
}
void Board::undo_move_red(const Move& mv) {
	if( m_ary[mv.m_dst] != WALL )
		m_ary[mv.m_dst] = EMPTY;
	else {
		++m_n_red;
	}
	m_ary[mv.m_src] = RED;
}
void Board::undo_move_blue(const Move& mv) {
	if( m_ary[mv.m_dst] != WALL )
		m_ary[mv.m_dst] = EMPTY;
	else {
		++m_n_blue;
	}
	m_ary[mv.m_src] = BLUE;
}
string Board::hash() const {
	string h;
	for(int ix = xyToIX(0, 0); ix < xyToIX(N_HORZ-1, N_VERT-1); ++ix) {
		switch( m_ary[ix] ) {
		case EMPTY:	h += '.';	break;
		case RED:	h += 'A';	break;
		case BLUE:	h += '>';	break;
		}
	}
	return h;
}
