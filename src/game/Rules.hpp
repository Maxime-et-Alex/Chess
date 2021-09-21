#ifndef RULES_HPP
#define RULES_HPP

#include <vector>
#include <tuple>

#include "Piece.hpp"

class Board;

struct Move
{
	unsigned int p64Start;
	unsigned int p64End;
	Type type = Type::None;
};

using ListOfMoves = std::vector<Move*>;

class Rules
{
public :
	static void movesForPiece(ListOfMoves&, unsigned int, const Board&, Color);

private :
	static void movesForKing(ListOfMoves&, unsigned int, const Board&, Color);
	static void movesForKnight(ListOfMoves&, unsigned int, const Board&, Color);
	static void movesForRook(ListOfMoves&, unsigned int, const Board&, Color);
	static void movesForBishop(ListOfMoves&, unsigned int, const Board&, Color);
	static void movesForPawn(ListOfMoves&, unsigned int, const Board&, Color);

public :
	static const std::vector<std::string> coord;
	
private :
	static const std::vector<int> tab120;
	static const std::vector<int> tab64;
	static const std::vector<int> deplacementsTour;
	static const std::vector<int> deplacementsFou;
	static const std::vector<int> deplacementsRoi;
	static const std::vector<int> deplacementsCavalier;
};

#endif //RULES_HPP