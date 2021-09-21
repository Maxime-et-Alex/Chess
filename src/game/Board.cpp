#include "Board.hpp"

Board::Board(std::string fen)
{
	setPosition(fen);
}

void Board::setPosition(std::string fen)
{
	m_cases.clear();

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

	m_gameStates.emplace_back(new GameState{whiteToPlay? Color::WHITE : Color::BLACK, roqueK, roqueQ, roquek, roqueq, caseEnPassant});

	updateAllowedMoves();
}

void Board::updateAllowedMoves()
{
	m_allowedMoves.clear();
	updateAllMoves();

	for(std::size_t i = 0; i < m_allMoves.size(); ++i)
	{
		moveAPiece(*m_allMoves[i], true, false, false);
		if(!isKingUnderAttack())
		{
			m_allowedMoves.emplace_back(m_allMoves[i]);
		}
		undo(false);
	}
}

void Board::updateAllMoves()
{
	m_allMoves.clear();
	m_allMovesOppositeColor.clear();

	for (std::size_t i = 0; i < m_cases.size(); ++i)
	{
		Rules::movesForPiece(m_allMoves, i, *this, getColor());
		Rules::movesForPiece(m_allMovesOppositeColor, i, *this, getOppositeColor());
	}

	//ROQUE

	if (getColor() == Color::WHITE)
	{
		if (m_gameStates.back()->roqueK &&
			m_cases[63]->m_type == Type::ROOK &&
			m_cases[63]->m_color == Color::WHITE &&
			m_cases[62]->m_type == Type::None &&
			m_cases[61]->m_type == Type::None &&
			!isPieceUnderAttack(62) &&
			!isPieceUnderAttack(61) &&
			!isPieceUnderAttack(60))
		{
			m_allMoves.emplace_back(new Move{60, 62});
		}
		if (m_gameStates.back()->roqueQ &&
			m_cases[56]->m_type == Type::ROOK &&
			m_cases[56]->m_color == Color::WHITE &&
			m_cases[57]->m_type == Type::None &&
			m_cases[58]->m_type == Type::None &&
			m_cases[59]->m_type == Type::None &&
			!isPieceUnderAttack(58) &&
			!isPieceUnderAttack(59) &&
			!isPieceUnderAttack(60))
		{
			m_allMoves.emplace_back(new Move{60, 58});
		}
	}
	else if(getColor() == Color::BLACK)
	{
		if (m_gameStates.back()->roquek &&
			m_cases[7]->m_type == Type::ROOK &&
			m_cases[7]->m_color == Color::BLACK &&
			m_cases[5]->m_type == Type::None &&
			m_cases[6]->m_type == Type::None &&
			!isPieceUnderAttack(5) &&
			!isPieceUnderAttack(6) &&
			!isPieceUnderAttack(4))
		{
			m_allMoves.emplace_back(new Move{4, 6});
		}
		if (m_gameStates.back()->roqueq &&
			m_cases[0]->m_type == Type::ROOK &&
			m_cases[0]->m_color == Color::BLACK &&
			m_cases[1]->m_type == Type::None &&
			m_cases[2]->m_type == Type::None &&
			m_cases[3]->m_type == Type::None &&
			!isPieceUnderAttack(2) &&
			!isPieceUnderAttack(3) &&
			!isPieceUnderAttack(4))
		{
			m_allMoves.emplace_back(new Move{4, 2});
		}
	}
}

void Board::moveAPiece(Move& move, bool amongAllMoves, bool needVerification, bool updateMoves)
{
	if (!needVerification || isMovePossible(move, amongAllMoves))
	{
		m_pgn.emplace_back(&move);
		m_takenPieces.emplace_back(new Piece(m_cases[move.p64End]->m_color, m_cases[move.p64End]->m_type));
		m_positionsOfTakenPieces.emplace_back(move.p64End);
		int caseEnPassant = m_gameStates.back()->caseEnPassant;
		Color currentPlayer = getColor();
		m_gameStates.emplace_back(new GameState);
		m_gameStates.back()->colorToPlay = currentPlayer;

		m_cases[move.p64End]->m_color = m_cases[move.p64Start]->m_color;
		if(move.type != Type::None)
		{
			m_cases[move.p64End]->m_type = move.type;
		}
		else
		{
			m_cases[move.p64End]->m_type = m_cases[move.p64Start]->m_type;
		}
		m_cases[move.p64Start]->m_color = Color::None;
		m_cases[move.p64Start]->m_type = Type::None;

		if (move.p64Start == 4 &&
			move.p64End == 6 &&
			m_cases[6]->m_type == Type::KING)
		{
			m_cases[5]->m_type = m_cases[7]->m_type;
			m_cases[5]->m_color = m_cases[7]->m_color;
			m_cases[7]->m_color = Color::None;
			m_cases[7]->m_type = Type::None;
		}
		if (move.p64Start == 4 &&
			move.p64End == 2 &&
			m_cases[2]->m_type == Type::KING)
		{
			m_cases[3]->m_type = m_cases[0]->m_type;
			m_cases[3]->m_color = m_cases[0]->m_color;
			m_cases[0]->m_color = Color::None;
			m_cases[0]->m_type = Type::None;
		}
		if (move.p64Start == 60 &&
			move.p64End == 62 &&
			m_cases[62]->m_type == Type::KING)
		{
			m_cases[61]->m_type = m_cases[63]->m_type;
			m_cases[61]->m_color = m_cases[63]->m_color;
			m_cases[63]->m_color = Color::None;
			m_cases[63]->m_type = Type::None;
		}
		if (move.p64Start == 60 &&
			move.p64End == 58 &&
			m_cases[58]->m_type == Type::KING)
		{
			m_cases[59]->m_type = m_cases[56]->m_type;
			m_cases[59]->m_color = m_cases[56]->m_color;
			m_cases[56]->m_color = Color::None;
			m_cases[56]->m_type = Type::None;
		}

		if (m_cases[move.p64End]->m_type == Type::KING)
		{
			if (m_cases[move.p64End]->m_color == Color::WHITE) 
			{
				m_gameStates.back()->roqueK = false;
				m_gameStates.back()->roqueQ = false;
			}
			else
			{
				m_gameStates.back()->roquek = false;
				m_gameStates.back()->roqueq = false;
			}
		}
		if (move.p64Start == 0) {m_gameStates.back()->roqueq = false;}
		if (move.p64Start == 7) {m_gameStates.back()->roquek = false;}
		if (move.p64Start == 56) {m_gameStates.back()->roqueQ = false;}
		if (move.p64Start == 63) {m_gameStates.back()->roqueK = false;}

		if (m_cases[move.p64End]->m_type == Type::PAWN &&
			move.p64End == unsigned(caseEnPassant))
		{
			if (move.p64End/8 == 2)
			{
				m_takenPieces.back()->m_color = Color::BLACK;
				m_takenPieces.back()->m_type = Type::PAWN;
				m_positionsOfTakenPieces.back() = move.p64End + 8;
			}
			else if (move.p64End/8 == 5)
			{
				m_takenPieces.back()->m_color = Color::WHITE;
				m_takenPieces.back()->m_type = Type::PAWN;
				m_positionsOfTakenPieces.back() = move.p64End - 8;
			}
		}

		if (m_cases[move.p64End]->m_type == Type::PAWN)
		{
			if (move.p64End/8-move.p64Start/8 == 2)
				{caseEnPassant = move.p64End - 8;}
			else if (move.p64Start/8-move.p64End/8 == 2)
				{caseEnPassant = move.p64End + 8;}
			else {caseEnPassant = -1;}
		}
		else {caseEnPassant = -1;}

		m_gameStates.back()->caseEnPassant = caseEnPassant;

		toggleTurn();
	}

	if (updateMoves)
	{
		updateAllowedMoves();
	}
}

void Board::undo(bool updateMoves)
{
	if (m_pgn.size() != 0)
	{
		if (m_pgn.back()->type == Type::None)
		{
			m_cases[m_pgn.back()->p64Start]->m_color = m_cases[m_pgn.back()->p64End]->m_color;
			m_cases[m_pgn.back()->p64Start]->m_type = m_cases[m_pgn.back()->p64End]->m_type;
			m_cases[m_pgn.back()->p64End]->m_color = Color::None;
			m_cases[m_pgn.back()->p64End]->m_type = Type::None;

			m_cases[m_positionsOfTakenPieces.back()]->m_color = m_takenPieces.back()->m_color;
			m_cases[m_positionsOfTakenPieces.back()]->m_type = m_takenPieces.back()->m_type;



			if (m_cases[m_pgn.back()->p64Start]->m_type == Type::KING)
			{
				if (m_pgn.back()->p64Start == 4 && m_pgn.back()->p64End == 6)
				{
					m_cases[7]->m_color = m_cases[5]->m_color;
					m_cases[7]->m_type = m_cases[5]->m_type;
					m_cases[5]->m_color = Color::None;
					m_cases[5]->m_type = Type::None;
				}
				if (m_pgn.back()->p64Start == 4 && m_pgn.back()->p64End == 2)
				{
					m_cases[0]->m_color = m_cases[3]->m_color;
					m_cases[0]->m_type = m_cases[3]->m_type;
					m_cases[3]->m_color = Color::None;
					m_cases[3]->m_type = Type::None;
				}
				if (m_pgn.back()->p64Start == 60 && m_pgn.back()->p64End == 62)
				{
					m_cases[63]->m_color = m_cases[61]->m_color;
					m_cases[63]->m_type = m_cases[61]->m_type;
					m_cases[61]->m_color = Color::None;
					m_cases[61]->m_type = Type::None;
				}
				if (m_pgn.back()->p64Start == 60 && m_pgn.back()->p64End == 58)
				{
					m_cases[56]->m_color = m_cases[59]->m_color;
					m_cases[56]->m_type = m_cases[59]->m_type;
					m_cases[59]->m_color = Color::None;
					m_cases[59]->m_type = Type::None;
				}
			}
		}
		else 
		{
			m_cases[m_pgn.back()->p64Start]->m_color = m_cases[m_pgn.back()->p64End]->m_color;
			m_cases[m_pgn.back()->p64Start]->m_type = Type::PAWN;
			m_cases[m_positionsOfTakenPieces.back()]->m_color = m_takenPieces.back()->m_color;
			m_cases[m_positionsOfTakenPieces.back()]->m_type = m_takenPieces.back()->m_type;
		}

		m_pgn.pop_back();
		m_takenPieces.pop_back();
		m_positionsOfTakenPieces.pop_back();
		m_gameStates.pop_back();
	}

	if (updateMoves)
	{
		updateAllowedMoves();
	}
}

void Board::toggleTurn()
{
	m_gameStates.back()->colorToPlay = getOppositeColor();
}

bool Board::isMovePossible(Move&, bool amongAllMoves)
{
	return true;
}

bool Board::isPieceUnderAttack(unsigned int p64) const
{
	bool flag = false;

	for(std::size_t i = 0; i <  m_allMovesOppositeColor.size(); ++i)
	{
		if(m_allMovesOppositeColor[i]->p64End == p64)
		{
			flag = true;
			break;
		}
	}
	return flag;
}

bool Board::isKingUnderAttack() const
{
	unsigned int p64 = 0;

	for(int i = 0; i < 64; ++i)
	{
		if(m_cases[i]->m_type == Type::KING && m_cases[i]->m_color == getOppositeColor())
		{
			p64 = i;
			break;
		}
	}

	return isPieceUnderAttack(p64);
}

Color Board::getColor() const
{
	return m_gameStates.back()->colorToPlay;
}

Color Board::getOppositeColor() const
{
	return (m_gameStates.back()->colorToPlay == Color::WHITE) ? Color::BLACK : Color::WHITE;
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
		std::cout << m_cases[i]->getCode() << " | ";
	}	
	std::cout << std::endl;
	std::cout << "\t+---+---+---+---+---+---+---+---+" << std::endl;
	std::cout << std::endl;
	
	if (getColor() == Color::WHITE)
		std::cout << " White to play" << std::endl;
	else std::cout << " Black to play" << std::endl;
}