#include "Piece.hpp"

Piece::Piece(char c)
{
	char c_min;
	m_code = c;
	
	if (c == '-')
	{
		m_color = Color::None;
		c_min = c;
	}
	else if (int(c) < 90)
	{
		m_color = Color::WHITE;
		c_min = c + 32;
	}
	else
	{
		m_color = Color::BLACK;
		c_min = c;
	}
	
	switch (c_min)
	{
		case 'p':
			m_type = Type::PAWN;
			break;
		case 'n':
			m_type = Type::KNIGHT;
			break;
		case 'b':
			m_type = Type::BISHOP;
			break;
		case 'r':
			m_type = Type::ROOK;
			break;
		case 'q':
			m_type = Type::QUEEN;			
			break;
		case 'k':
			m_type = Type::KING;
			break;
		default:
			m_type = Type::None;
			break;
	}
}

Piece::Piece(Color color, Type type)
: m_color(color)
, m_type(type)
{
	char c_min;

	switch (type)
	{
		case Type::PAWN:
			c_min = 'p';
			break;
		case Type::KNIGHT:
			c_min = 'n';
			break;
		case Type::BISHOP:
			c_min = 'b';
			break;
		case Type::ROOK:
			c_min = 'r';
			break;
		case Type::QUEEN:
			c_min = 'q';
			break;
		case Type::KING:
			c_min = 'k';
			break;
		default:
			c_min = '-';
			break;
	}

	if (m_type != Type::None)
	{
		if (m_color == Color::WHITE) {m_code = c_min - 32;}
		else {m_code = c_min;}
	}
}

PieceWithPos::PieceWithPos(unsigned int p64, char c)
: Piece(c)
, m_p64(p64)
{
}

PieceWithPos::PieceWithPos(unsigned int p64, Color color, Type type)
: Piece(color, type)
, m_p64(p64)
{
}