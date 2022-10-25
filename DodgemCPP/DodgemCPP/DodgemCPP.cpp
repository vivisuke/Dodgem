#include <iostream>
#include <random>
#include "Board.h"

using namespace std;

random_device g_rand;     	// 非決定的な乱数生成器
mt19937 g_mt(g_rand());     // メルセンヌ・ツイスタの32ビット版

int g_count = 0;

void search_game_tree(Board& bd, bool red_turn, int depth) {
	if( depth == 0 ) {
		cout << ++g_count << ":\n";
		bd.print();
	} else {
		Moves lst;
		if( red_turn ) {
			bd.get_red_moves(lst);
			if( lst.empty() ) {
				cout << ++g_count << ":\n";
				bd.print();
				return;
			}
			for(int i = 0; i != lst.size(); ++i) {
				bd.do_move_red(lst[i]);
				search_game_tree(bd, !red_turn, depth-1);
				bd.undo_move_red(lst[i]);
			}
		} else {
			bd.get_blue_moves(lst);
			if( lst.empty() ) {
				cout << ++g_count << ":\n";
				bd.print();
				return;
			}
			for(int i = 0; i != lst.size(); ++i) {
				bd.do_move_blue(lst[i]);
				search_game_tree(bd, !red_turn, depth-1);
				bd.undo_move_blue(lst[i]);
			}
		}
	}
}

int main()
{
	Board bd;
	bd.print();
	Moves lst;
	int ix;
	if( true ) {
		g_count = 0;
		search_game_tree(bd, true, 3);
	}
	if( false ) {
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
