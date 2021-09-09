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
	std::vector<int> tab120{
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1,  0,  1,  2,  3,  4,  5,  6,  7, -1,
		-1,  8,  9, 10, 11, 12, 13, 14, 15, -1,
		-1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
		-1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
		-1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
		-1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
		-1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
		-1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	};
	
	std::vector<int> tab64{
		 0,  1,  2,  3,  4,  5,  6,  7,
		 8,  9, 10, 11, 12, 13, 14, 15,
		16, 17, 18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29, 30, 31,
		32, 33, 34, 35, 36, 37, 38, 39,
		40, 41, 42, 43, 44, 45, 46, 47,
		48, 49, 50, 51, 52, 53, 54, 55,
		56, 57, 58, 59, 60, 61, 62, 63
	};
	
	std::vector<int> deplacementsTour{-10, 10, -1, 1};
	std::vector<int> deplacementsFou{-11, -9, 11, 9};
	std::vector<int> deplacementsRoi{-11, -10, -9, -1, 1, 9, 10, 11};
	std::vector<int> deplacementsCavalier{-12, -21, -19, -8, 12, 21, 19, 8};

public :
	Rules();

	void movesForKing(ListOfMoves&, unsigned int, const Board&, Color) const;
	void movesForKnight(ListOfMoves&, unsigned int, const Board&, Color) const;
	void movesForRook(ListOfMoves&, unsigned int, const Board&, Color) const;
	void movesForBishop(ListOfMoves&, unsigned int, const Board&, Color) const;
	void movesForPawn(ListOfMoves&, unsigned int, const Board&, Color) const;
};

#endif //RULES_HPP