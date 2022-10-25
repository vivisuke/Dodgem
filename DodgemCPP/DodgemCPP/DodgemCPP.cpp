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
	for(;;) {
		bd.get_red_moves(lst);
		if( lst.empty() ) break;
		ix = g_mt() % lst.size();
		bd.do_move_red(lst[ix]);
		bd.print();
		if( bd.m_n_red == 0 ) break;
		bd.get_blue_moves(lst);
		if( lst.empty() ) break;
		ix = g_mt() % lst.size();
		bd.do_move_blue(lst[ix]);
		bd.print();
		if( bd.m_n_blue == 0 ) break;
	}

    std::cout << "OK.\n";
}
