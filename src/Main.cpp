#include "game/Board.hpp"

int main()
{
	Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1");

	board.printBoard();
	std::cout << std::endl;

	for (std::size_t i = 0; i < board.m_allMoves.size(); ++i)
	{
		std::cout << Rules::coord[board.m_allMoves[i]->p64Start] << "->" << Rules::coord[board.m_allMoves[i]->p64End] << std::endl;
	}

    return 0;
}
