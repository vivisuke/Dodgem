#include <iostream>
#include "Board.h"

using namespace std;

int main()
{
	Board bd;
	bd.print();
	Moves lst;
	bd.get_red_moves(lst);
	bd.get_blue_moves(lst);

    std::cout << "OK.\n";
}
