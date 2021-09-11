#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <string>

#include "Rules.hpp"

struct GameState
{
	bool whiteToPlay;
	bool roqueK;
	bool roqueQ;
	bool roquek;
	bool roqueq;
	int caseEnPassant;
};

class Board
{
public :
	Board(std::string fen);

	void updateAllowedMoves(Color);
	void updateAllMoves(Color);
	void moveAPiece(Move);
	void undo();

	void printBoard() const;

private :
	void setPosition(std::string fen);
	bool isMovePossible(Move);
	void toggleTurn();
	bool isPieceUnderAttack(Color);
	bool isKingUnderAttack(Color);

public :
	std::vector<Piece*> m_cases;
	ListOfMoves m_allMoves;
	ListOfMoves m_allowedMoves;
	std::vector<GameState*> m_gameStates;

private :
	std::vector<PieceWithPos*> m_pieces;
	ListOfMoves m_pgn;
	std::vector<Piece*> m_piecesTooked;
};

#endif //BOARD_HPP