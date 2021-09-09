#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <string>

#include "Rules.hpp"

using GameState = std::tuple<bool, bool, bool, bool, unsigned int>;

class Board
{
public :
	Board(std::string fen);

	ListOfMoves allowedMoves(Color);
	void setPosition(std::string fen);
	void moveAPiece(Move);
	void undo();

	void printBoard() const;

private :
	ListOfMoves allMoves(Color);
	bool isMovePossible(Move);
	void toggleTurn();
	bool isKingUnderAttack(Color);

public :
	std::vector<Piece*> m_cases;

private :
	bool m_whiteToPlay;
	std::vector<Piece*> m_pieces;
	std::vector<GameState*> m_gameStates;
	ListOfMoves m_allMoves;
	ListOfMoves m_allowedMoves;
	ListOfMoves m_pgn;
	std::vector<Piece*> m_piecesTooked;
};

#endif //BOARD_HPP