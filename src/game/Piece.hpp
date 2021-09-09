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

public :
	Color m_color = Color::None;
	Type m_type = Type::None;
	char m_code = '-';
};

struct PieceWithPos : public Piece
{
public :
	PieceWithPos(unsigned int, char);
	PieceWithPos(unsigned int, Color, Type);

public :
	unsigned int m_p64 = 64;
	Color m_color = Color::None;
	Type m_type = Type::None;
	char m_code = '-';
};

#endif //PIECE_HPP