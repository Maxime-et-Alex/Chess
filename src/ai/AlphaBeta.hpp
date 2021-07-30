#ifndef ALPHA_BETA_H
#define ALPHA_BETA_H

#include "AbstractAI.hpp"

enum Color;

class AlphaBeta : public AbstractAI
{
	public :
		AlphaBeta(Board&, Color);

        int eval();
        virtual Move getMove();

    private :
        int search(int depth, int alpha=-1000, int beta=1000);

    private :
        Board& m_board;
        Color m_color;
        double m_tempsTotal;
};

#endif //ALPHA_BETA_H
