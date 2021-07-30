#ifndef RANDOM_H
#define RANDOM_H

#include "AbstractAI.hpp"

class Random : public AbstractAI
{
	public :
		Random(Board&);

        virtual Move getMove();

	private :
		Board& m_board;
};

#endif //RANDOM_H