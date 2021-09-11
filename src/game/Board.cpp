#include "Board.hpp"

Board::Board(std::string fen)
{
	setPosition(fen);
	updateAllowedMoves(m_gameStates.back()->whiteToPlay ? Color::WHITE : Color::BLACK);
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

	for (std::size_t i = 0; i < m_cases.size(); ++i)
	{
		if (m_cases[i]->m_type != Type::None)
		{
			m_pieces.emplace_back(new PieceWithPos(i, m_cases[i]->m_color, m_cases[i]->m_type));
		}
	}

	bool whiteToPlay = (*vectFen[1] == "w");
	
	bool roqueK = vectFen[2]->find_first_of('K') < vectFen[2]->size();
	bool roqueQ = vectFen[2]->find_first_of('Q') < vectFen[2]->size();
	bool roquek = vectFen[2]->find_first_of('k') < vectFen[2]->size();
	bool roqueq = vectFen[2]->find_first_of('q') < vectFen[2]->size();

	int caseEnPassant = -1;
	if (*vectFen[3] != "-")
	{
		for (std::size_t i = 0; i < Rules::coord.size(); ++i)
		{
			if (*vectFen[3] == Rules::coord[i])
				caseEnPassant = i;
		}
	}

	m_gameStates.emplace_back(new GameState{whiteToPlay, roqueK, roqueQ, roquek, roqueq, caseEnPassant});
}

void Board::updateAllowedMoves(Color c)
{
	m_allowedMoves.clear();
	updateAllMoves(c);
}

void Board::updateAllMoves(Color c)
{
	m_allMoves.clear();

	for (std::size_t i = 0; i < m_pieces.size(); ++i)
	{
		Rules::movesForPiece(m_allMoves, m_pieces[i]->m_p64, *this, c);
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
	
	if (m_gameStates.back()->whiteToPlay)
		std::cout << " White to play" << std::endl;
	else std::cout << " Black to play" << std::endl;
}