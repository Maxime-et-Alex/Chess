#ifndef ABSTRACT_AI_HPP
#define ABSTRACT_AI_HPP

#include <tuple>

#include "../game/Rules.hpp"

class Board;

using Move = std::tuple<unsigned int, unsigned int, Type>;

class AbstractAI
{
public :
	AbstractAI(Board&);	

	virtual Move getMove() = 0;

private :
	Board& m_board;
};

#endif //ABSTRACT_AI_HPP