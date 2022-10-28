#include <iostream>
#include <random>
#include <unordered_set>
#include "Board.h"

using namespace std;

random_device g_rand;     	// 非決定的な乱数生成器
mt19937 g_mt(g_rand());     // メルセンヌ・ツイスタの32ビット版

bool g_verbose = true;
int g_count = 0;
unordered_set<string> g_set;

void print_board(const Board& bd) {
	++g_count;
	if( g_verbose ) {
		cout << g_count << ":\n";
		bd.print();
	}
}
void search_game_tree(Board& bd, bool red_turn, int depth) {
	if( depth == 0 ) {
		print_board(bd);
	} else {
		Moves lst;
		if( red_turn ) {
			bd.get_red_moves(lst);
			if( lst.empty() ) {
				print_board(bd);
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
				print_board(bd);
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
void print_if_uniq(const Board& bd) {
	const auto key = bd.hash();
	if( g_set.find(key) == g_set.end() ) {		//	重複していない場合
		g_set.insert(key);
		++g_count;
		if( g_verbose ) {
			cout << g_count << ":\n";
			bd.print();
		}
	}
}
void search_game_tree_uniq(Board& bd, bool red_turn, int depth) {
	if( depth == 0 ) {
		print_if_uniq(bd);
	} else {
		Moves lst;
		if( red_turn ) {
			bd.get_red_moves(lst);
			if( lst.empty() ) {
				print_if_uniq(bd);
				return;
			}
			for(int i = 0; i != lst.size(); ++i) {
				bd.do_move_red(lst[i]);
				search_game_tree_uniq(bd, !red_turn, depth-1);
				bd.undo_move_red(lst[i]);
			}
		} else {
			bd.get_blue_moves(lst);
			if( lst.empty() ) {
				print_if_uniq(bd);
				return;
			}
			for(int i = 0; i != lst.size(); ++i) {
				bd.do_move_blue(lst[i]);
				search_game_tree_uniq(bd, !red_turn, depth-1);
				bd.undo_move_blue(lst[i]);
			}
		}
	}
}
void count_nodes(Board& bd, bool red_turn) {
	Moves lst;
	if( red_turn ) {
		bd.get_red_moves(lst);
		//if( lst.empty() ) {
		//	return;
		//}
		for(int i = 0; i != lst.size(); ++i) {
			bd.do_move_red(lst[i]);
			auto key = bd.hash();
			if( g_set.find(key) == g_set.end() ) {		//	未探索の場合
				g_set.insert(key);
				++g_count;
				count_nodes(bd, !red_turn);
			}
			bd.undo_move_red(lst[i]);
		}
	} else {
		bd.get_blue_moves(lst);
		//if( lst.empty() ) {
		//	return;
		//}
		for(int i = 0; i != lst.size(); ++i) {
			bd.do_move_blue(lst[i]);
			auto key = bd.hash();
			if( g_set.find(key) == g_set.end() ) {		//	未探索の場合
				g_set.insert(key);
				++g_count;
				count_nodes(bd, !red_turn);
			}
			bd.undo_move_blue(lst[i]);
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
		auto key = bd.hash();
		g_set.insert(key);
		g_count = 1;
		count_nodes(bd, true);
		cout << "g_count = " << g_count << "\n";
	}
	if( false ) {
		const int DEPTH = 20;
		cout << "depth = " << DEPTH << ":\n";
		g_verbose = false;
#if 0
		g_count = 0;
		search_game_tree(bd, true, DEPTH);
		cout << "g_count = " << g_count << "\n";
#endif
		g_count = 0;
		search_game_tree_uniq(bd, true, DEPTH);
		cout << "g_count = " << g_count << "\n";
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
