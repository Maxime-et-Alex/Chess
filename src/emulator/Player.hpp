#ifndef PLAYER_HPP
#define PLAYER_HPP

class Board;

class Player
{
public :
	Player(Board&);

private :
	Board& m_board;
};

#endif //PLAYER_HPP