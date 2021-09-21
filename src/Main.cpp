<<<<<<< HEAD
#include <iostream>
#include <random>
#include <chrono>

#include "game/Board.hpp"
#include "sfml/Engine.hpp"

int main()
{
	try
	{
		Engine engine;
		engine.run();
	}
	catch (std::runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
		return 1;
	}
	
	Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	int index = 0;
	board.printBoard();
	std::cout << std::endl;

	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distU(0, board.m_allowedMoves.size()-1);

	for (int i = 0; i < 1000; ++i)
	{
		std::cin.get();
	
		index = distU(generator);

		std::cout << Rules::coord[board.m_allowedMoves[index]->p64Start] << "->" << Rules::coord[board.m_allowedMoves[index]->p64End] << std::endl;
		board.moveAPiece(*board.m_allowedMoves[index]);

		board.printBoard();
	}

    return 0;
}
