#include <iostream>

#include "game/Board.hpp"

int main()
{
	Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	board.printBoard();
	
    return 0;
}
