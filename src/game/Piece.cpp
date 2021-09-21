#include "Piece.hpp"

Piece::Piece(char c)
{
	char c_min;
	
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
}

char Piece::getCode() const
{
	char code;

	switch (m_type)
	{
		case Type::PAWN:
			code = 'p';
			break;
		case Type::KNIGHT:
			code = 'n';
			break;
		case Type::BISHOP:
			code = 'b';
			break;
		case Type::ROOK:
			code = 'r';
			break;
		case Type::QUEEN:
			code = 'q';
			break;
		case Type::KING:
			code = 'k';
			break;
		default:
			code = '-';
			break;
	}

	if (m_type != Type::None)
	{
		if (m_color == Color::WHITE) {code = code - 32;}
		else {code = code;}
	}

	return code;
}