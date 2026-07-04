#include "board.h"
#include <iostream>
#include <vector>

int main()
{
    Board board(5, 5);

    board.make_move(1, 1, 1);
    board.make_move(2, 1, 2);
    board.make_move(1, 2, 1);

    board.print();
}
