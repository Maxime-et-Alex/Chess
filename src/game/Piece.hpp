#ifndef PIECE_HPP
#define PIECE_HPP

enum class Color
{
	None,
	WHITE,
	BLACK
};

enum class Type
{
	None,
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING
};

class Piece
{
public :
	Piece(char);
	Piece(Color, Type);

	char getCode() const;

public :
	Color m_color = Color::None;
	Type m_type = Type::None;
};

#endif //PIECE_HPP