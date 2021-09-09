#include "Board.hpp"

Board::Board(std::string fen)
{
	setPosition(fen);
}

void Board::setPosition(std::string fen)
{
	m_cases.clear();
	m_pieces.clear();

	std::size_t s = fen.size();
	std::vector<std::string*> vectFen;
	std::string num = "12345678";
	char cell;

	vectFen.push_back(new std::string(""));

	for(std::size_t i = 0; i < s; ++i)
	{
		cell = fen[i];
		if(cell == ' ')
		{
			vectFen.push_back(new std::string(""));
		}
		else
		{
			(*vectFen[vectFen.size()-1]) += cell;
		}
	}

	for(std::size_t i = 0; i < vectFen[0]->size(); ++i)
	{
		cell = (*vectFen[0])[i];

		if(num.find_first_of(cell) < num.size())
		{
			for (std::size_t j = 0; j < unsigned(cell - '0'); ++j)
			{	
				m_cases.emplace_back(new Piece('-'));
			}
		}
		else if(cell != '/')
		{
			m_cases.emplace_back(new Piece(cell));
		}
	}
}

void Board::printBoard() const
{
	for(std::size_t i = 0; i < m_cases.size(); ++i)
	{
		if(i%8 == 0)
		{
			std::cout << std::endl;
			std::cout << "\t+---+---+---+---+---+---+---+---+" << std::endl;
			std::cout << "\t| ";
		}
		std::cout << m_cases[i]->m_code << " | ";
	}	
	std::cout << std::endl;
	std::cout << "\t+---+---+---+---+---+---+---+---+" << std::endl;
	std::cout << std::endl;
	
	if (m_whiteToPlay)
		std::cout << " White to play" << std::endl;
	else std::cout << " Black to play" << std::endl;
}