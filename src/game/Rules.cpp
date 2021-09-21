#include "Rules.hpp"
#include "Board.hpp"

const std::vector<int> Rules::tab120{
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

const std::vector<int> Rules::tab64{
	0,  1,  2,  3,  4,  5,  6,  7,
	8,  9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23,
	24, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 35, 36, 37, 38, 39,
	40, 41, 42, 43, 44, 45, 46, 47,
	48, 49, 50, 51, 52, 53, 54, 55,
	56, 57, 58, 59, 60, 61, 62, 63
};

const std::vector<std::string> Rules::coord{
	"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
	"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
	"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
	"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
	"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
	"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
	"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
	"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
};

const std::vector<int> Rules::deplacementsTour{-10, 10, -1, 1};
const std::vector<int> Rules::deplacementsFou{-11, -9, 11, 9};
const std::vector<int> Rules::deplacementsRoi{-11, -10, -9, -1, 1, 9, 10, 11};
const std::vector<int> Rules::deplacementsCavalier{-12, -21, -19, -8, 12, 21, 19, 8};

void Rules::movesForKing(ListOfMoves& moves, unsigned int p64, const Board& board, Color c)
{
	unsigned int p120 = p64 + 21 + 2*(p64/8);
	int n;

	for (auto it = deplacementsRoi.begin(); it != deplacementsRoi.end(); ++it)
	{
		n = tab120[p120 + *it];
		if (n>=0 && (board.m_cases[n]->m_type == Type::None || board.m_cases[n]->m_color != c))
		{
			moves.emplace_back(new Move{p64, unsigned(n)});
		}
	}
}

void Rules::movesForKnight(ListOfMoves& moves, unsigned int p64, const Board& board, Color c)
{
	unsigned int p120 = p64 + 21 + 2*(p64/8);
	int n;

	for (auto it = deplacementsCavalier.begin(); it != deplacementsCavalier.end(); ++it)
	{
		n = tab120[p120 + *it];
		if (n>=0 && (board.m_cases[n]->m_type == Type::None || board.m_cases[n]->m_color != c))
		{
			moves.emplace_back(new Move{p64, unsigned(n)});
		}
	}
}

void Rules::movesForRook(ListOfMoves& moves, unsigned int p64, const Board& board, Color c)
{
	unsigned int p120 = p64 + 21 + 2*(p64/8);
	int n, k;

	for (auto it = deplacementsTour.begin(); it != deplacementsTour.end(); ++it)
	{
		k = 1;
		while(true)
		{
			n = tab120[p120 + k*(*it)];
			if (n>=0)
			{
				if (board.m_cases[n]->m_type == Type::None || board.m_cases[n]->m_color != c)
				{
					moves.emplace_back(new Move{p64, unsigned(n)});
				}
			}
			else {break;}
			if (board.m_cases[n]->m_type != Type::None) {break;}
			++k;
		}
	}
}

void Rules::movesForBishop(ListOfMoves& moves, unsigned int p64, const Board& board, Color c)
{
	unsigned int p120 = p64 + 21 + 2*(p64/8);
	int n, k;

	for (auto it = deplacementsFou.begin(); it != deplacementsFou.end(); ++it)
	{
		k = 1;
		while(true)
		{
			n = tab120[p120 + k*(*it)];
			if (n>=0)
			{
				if (board.m_cases[n]->m_type == Type::None || board.m_cases[n]->m_color != c)
				{
					moves.emplace_back(new Move{p64, unsigned(n)});
				}
			}
			else {break;}
			if (board.m_cases[n]->m_type != Type::None) {break;}
			++k;
		}
	}
}

void Rules::movesForPawn(ListOfMoves& moves, unsigned int p64, const Board& board, Color c)
{
	unsigned int p120 = p64 + 21 + 2*(p64/8);
	int n;

	//-----------------------------------WHITE PAWN -----------------------------------
	if (c == Color::WHITE)
	{
		n = tab120[p120 - 10];
		if (n >= 0 && board.m_cases[n]->m_type == Type::None)
		{
			if(n < 8)
			{
				moves.emplace_back(new Move{p64, unsigned(n), Type::QUEEN});
				moves.emplace_back(new Move{p64, unsigned(n), Type::ROOK});
				moves.emplace_back(new Move{p64, unsigned(n), Type::KNIGHT});
				moves.emplace_back(new Move{p64, unsigned(n), Type::BISHOP});
			}
			else
			{
				moves.emplace_back(new Move{p64, unsigned(n), Type::None});
			}
		}

		//Starting Square
		if (p64/8 == 6 &&
			board.m_cases[p64-8]->m_type == Type::None &&
			board.m_cases[p64-16]->m_type == Type::None)
		{
			moves.emplace_back(new Move{p64, unsigned(p64-16), Type::None});
		}

		//Capture upper left
		n = tab120[p120 - 11];
		if (n >= 0 && (board.m_cases[n]->m_color == Color::BLACK || n == board.m_gameStates.back()->caseEnPassant))
		{
			if(n < 8)
			{
				moves.emplace_back(new Move{p64, unsigned(n), Type::QUEEN});
				moves.emplace_back(new Move{p64, unsigned(n), Type::ROOK});
				moves.emplace_back(new Move{p64, unsigned(n), Type::KNIGHT});
				moves.emplace_back(new Move{p64, unsigned(n), Type::BISHOP});
			}
			else
			{
				moves.emplace_back(new Move{p64, unsigned(n), Type::None});
			}
		}

		//Capture upper right
		n = tab120[p120 - 9];
		if (n >= 0 && (board.m_cases[n]->m_color == Color::BLACK || n == board.m_gameStates.back()->caseEnPassant))
		{
			if(n < 8)
			{
				moves.emplace_back(new Move{p64, unsigned(n), Type::QUEEN});
				moves.emplace_back(new Move{p64, unsigned(n), Type::ROOK});
				moves.emplace_back(new Move{p64, unsigned(n), Type::KNIGHT});
				moves.emplace_back(new Move{p64, unsigned(n), Type::BISHOP});
			}
			else
			{
				moves.emplace_back(new Move{p64, unsigned(n), Type::None});
			}
		}
	}
	//-----------------------------------BLACK PAWN -----------------------------------
	if (c == Color::BLACK)
	{
		n = tab120[p120 + 10];
		if (n >= 0 && board.m_cases[n]->m_type == Type::None)
		{
			if(n > 55)
			{
				moves.emplace_back(new Move{p64, unsigned(n), Type::QUEEN});
				moves.emplace_back(new Move{p64, unsigned(n), Type::ROOK});
				moves.emplace_back(new Move{p64, unsigned(n), Type::KNIGHT});
				moves.emplace_back(new Move{p64, unsigned(n), Type::BISHOP});
			}
			else
			{
				moves.emplace_back(new Move{p64, unsigned(n), Type::None});
			}
		}

		//Starting Square
		if (p64/8 == 1 &&
			board.m_cases[p64+8]->m_type == Type::None &&
			board.m_cases[p64+16]->m_type == Type::None)
		{
			moves.emplace_back(new Move{p64, unsigned(p64+16), Type::None});
		}

		//Capture bottom left
		n = tab120[p120 + 9];
		if (n >= 0 && (board.m_cases[n]->m_color == Color::WHITE || n == board.m_gameStates.back()->caseEnPassant))
		{
			if(n > 55)
			{
				moves.emplace_back(new Move{p64, unsigned(n), Type::QUEEN});
				moves.emplace_back(new Move{p64, unsigned(n), Type::ROOK});
				moves.emplace_back(new Move{p64, unsigned(n), Type::KNIGHT});
				moves.emplace_back(new Move{p64, unsigned(n), Type::BISHOP});
			}
			else
			{
				moves.emplace_back(new Move{p64, unsigned(n), Type::None});
			}
		}

		//Capture bottom right
		n = tab120[p120 + 11];
		if (n >= 0 && (board.m_cases[n]->m_color == Color::WHITE || n == board.m_gameStates.back()->caseEnPassant))
		{
			if(n > 55)
			{
				moves.emplace_back(new Move{p64, unsigned(n), Type::QUEEN});
				moves.emplace_back(new Move{p64, unsigned(n), Type::ROOK});
				moves.emplace_back(new Move{p64, unsigned(n), Type::KNIGHT});
				moves.emplace_back(new Move{p64, unsigned(n), Type::BISHOP});
			}
			else
			{
				moves.emplace_back(new Move{p64, unsigned(n), Type::None});
			}
		}
	}
	//---------------------------------------------------------------------------------
}

void Rules::movesForPiece(ListOfMoves& moves, unsigned int p64, const Board& board, Color c)
{
	Type type = board.m_cases[p64]->m_type;

	if (board.m_cases[p64]->m_color == c)
	{	
		switch (type)
		{
			case Type::KING:
				movesForKing(moves, p64, board, c);
				break;
			case Type::QUEEN:
				movesForRook(moves, p64, board, c);
				movesForBishop(moves, p64, board, c);
				break;
			case Type::ROOK:
				movesForRook(moves, p64, board, c);
				break;
			case Type::BISHOP:
				movesForBishop(moves, p64, board, c);
				break;
			case Type::KNIGHT:
				movesForKnight(moves, p64, board, c);
				break;
			case Type::PAWN: 
				movesForPawn(moves, p64, board, c);
				break;
			default:
				break;
		}
	}
}