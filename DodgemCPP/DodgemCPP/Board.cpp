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
