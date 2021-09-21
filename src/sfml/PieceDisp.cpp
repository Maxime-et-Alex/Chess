#include "PieceDisp.hpp"
#include "../game/Piece.hpp"

PieceDisp::PieceDisp()
{
	if (!m_whitePawn.loadFromFile("assets/white/p.png"))
		throw std::runtime_error ("PieceDisp::PieceDisp() - Failed to load 'assets/white/p.png'");
	if (!m_whiteKnight.loadFromFile("assets/white/n.png"))
		throw std::runtime_error ("PieceDisp::PieceDisp() - Failed to load 'assets/white/n.png'");
	if (!m_whiteBishop.loadFromFile("assets/white/b.png"))
		throw std::runtime_error ("PieceDisp::PieceDisp() - Failed to load 'assets/white/b.png'");
	if (!m_whiteRook.loadFromFile("assets/white/r.png"))
		throw std::runtime_error ("PieceDisp::PieceDisp() - Failed to load 'assets/white/r.png'");
	if (!m_whiteQueen.loadFromFile("assets/white/q.png"))
		throw std::runtime_error ("PieceDisp::PieceDisp() - Failed to load 'assets/white/q.png'");
	if (!m_whiteKing.loadFromFile("assets/white/k.png"))
		throw std::runtime_error ("PieceDisp::PieceDisp() - Failed to load 'assets/white/k.png'");

	if (!m_blackPawn.loadFromFile("assets/black/p.png"))
		throw std::runtime_error ("PieceDisp::PieceDisp() - Failed to load 'assets/black/p.png'");
	if (!m_blackKnight.loadFromFile("assets/black/n.png"))
		throw std::runtime_error ("PieceDisp::PieceDisp() - Failed to load 'assets/black/n.png'");
	if (!m_blackBishop.loadFromFile("assets/black/b.png"))
		throw std::runtime_error ("PieceDisp::PieceDisp() - Failed to load 'assets/black/b.png'");
	if (!m_blackRook.loadFromFile("assets/black/r.png"))
		throw std::runtime_error ("PieceDisp::PieceDisp() - Failed to load 'assets/black/r.png'");
	if (!m_blackQueen.loadFromFile("assets/black/q.png"))
		throw std::runtime_error ("PieceDisp::PieceDisp() - Failed to load 'assets/black/q.png'");
	if (!m_blackKing.loadFromFile("assets/black/k.png"))
		throw std::runtime_error ("PieceDisp::PieceDisp() - Failed to load 'assets/black/k.png'");

	m_whitePawn.setSmooth(true);
	m_whiteKnight.setSmooth(true);
	m_whiteBishop.setSmooth(true);
	m_whiteRook.setSmooth(true);
	m_whiteQueen.setSmooth(true);
	m_whiteKing.setSmooth(true);

	m_blackPawn.setSmooth(true);
	m_blackKnight.setSmooth(true);
	m_blackBishop.setSmooth(true);
	m_blackRook.setSmooth(true);
	m_blackQueen.setSmooth(true);
	m_blackKing.setSmooth(true);
}

sf::Sprite PieceDisp::getSprite(Piece& piece) const
{
	sf::Sprite sprite;

	if(piece.m_color == Color::WHITE)
	{
		switch (piece.m_type)
		{
		case Type::PAWN:
			sprite.setTexture(m_whitePawn);
			break;

		case Type::KNIGHT:
			sprite.setTexture(m_whiteKnight);
			break;

		case Type::BISHOP:
			sprite.setTexture(m_whiteBishop);
			break;

		case Type::ROOK:
			sprite.setTexture(m_whiteRook);
			break;

		case Type::QUEEN:
			sprite.setTexture(m_whiteQueen);
			break;

		case Type::KING:
			sprite.setTexture(m_whiteKing);
			break;
		
		default:
			break;
		}
	}
	else if(piece.m_color == Color::BLACK)
	{
		switch (piece.m_type)
		{
		case Type::PAWN:
			sprite.setTexture(m_blackPawn);
			break;

		case Type::KNIGHT:
			sprite.setTexture(m_blackKnight);
			break;

		case Type::BISHOP:
			sprite.setTexture(m_blackBishop);
			break;

		case Type::ROOK:
			sprite.setTexture(m_blackRook);
			break;

		case Type::QUEEN:
			sprite.setTexture(m_blackQueen);
			break;

		case Type::KING:
			sprite.setTexture(m_blackKing);
			break;
		
		default:
			break;
		}
	}

	return sprite;
}