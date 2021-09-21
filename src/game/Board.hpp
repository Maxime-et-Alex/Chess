#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <string>

#include "Rules.hpp"

struct GameState
{
	Color colorToPlay;
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

	void updateAllowedMoves();
	void moveAPiece(Move&, bool amongAllMoves=false, bool needVerification=true, bool updateMoves=true);
	void undo(bool updateMoves=true);

	void printBoard() const;

private :
	void setPosition(std::string fen);
	void updateAllMoves();
	bool isMovePossible(Move&, bool amongAllMoves);
	void toggleTurn();
	bool isPieceUnderAttack(unsigned int) const;
	bool isKingUnderAttack() const;
	Color getColor() const;
	Color getOppositeColor() const;

public :
	std::vector<Piece*> m_cases;
	ListOfMoves m_allowedMoves;
	std::vector<GameState*> m_gameStates;

private :
	ListOfMoves m_allMoves;
	ListOfMoves m_allMovesOppositeColor;
	ListOfMoves m_pgn;
	std::vector<Piece*> m_takenPieces;
	std::vector<int> m_positionsOfTakenPieces;
};

#endif //BOARD_HPP