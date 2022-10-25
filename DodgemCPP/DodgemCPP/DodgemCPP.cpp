#include <iostream>
#include <random>
#include "Board.h"

using namespace std;

random_device g_rand;     	// 非決定的な乱数生成器
mt19937 g_mt(g_rand());     // メルセンヌ・ツイスタの32ビット版



int main()
{
	Board bd;
	bd.print();
	Moves lst;
	int ix;
	if( true ) {
		bd.get_red_moves(lst);
		ix = g_mt() % lst.size();
		bd.do_move_red(lst[ix]);
		bd.print();
		bd.undo_move_red(lst[ix]);
		bd.print();
		//
		bd.get_blue_moves(lst);
		ix = g_mt() % lst.size();
		bd.do_move_blue(lst[ix]);
		bd.print();
		bd.undo_move_blue(lst[ix]);
		bd.print();
	}
	if( false ) {
		for(;;) {
			bd.get_red_moves(lst);
			if( lst.empty() ) {
				cout << "red won.\n";
				break;
			}
			ix = g_mt() % lst.size();
			bd.do_move_red(lst[ix]);
			bd.print();
			if( bd.m_n_red == 0 ) {
				cout << "red won.\n";
				break;
			}
			bd.get_blue_moves(lst);
			if( lst.empty() ) {
				cout << "blue won.\n";
				break;
			}
			ix = g_mt() % lst.size();
			bd.do_move_blue(lst[ix]);
			bd.print();
			if( bd.m_n_blue == 0 ) {
				cout << "blue won.\n";
				break;
			}
		}
	}

    std::cout << "\nOK.\n";
}
