#ifndef EMULATOR_HPP
#define EMULATOR_HPP

class Board;

class Emulator
{
public :
	Emulator(Board&);

private :
	bool m_whiteToPlay;
	Board& m_board;
};

#endif //EMULATOR_HPP