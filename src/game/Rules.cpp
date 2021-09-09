#include "Rules.hpp"
#include "Board.hpp"

Rules::Rules()
{
}

void Rules::movesForKing(ListOfMoves& moves, unsigned int p64, const Board& board, Color c) const
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