#ifndef PIECEDISP_HPP
#define PIECEDISP_HPP

#include <SFML/Graphics.hpp>

class Piece;

class PieceDisp
{
public :
	PieceDisp();

	sf::Sprite getSprite(Piece&) const;

private :
	sf::Texture m_whitePawn;
	sf::Texture m_whiteKnight;
	sf::Texture m_whiteBishop;
	sf::Texture m_whiteRook;
	sf::Texture m_whiteQueen;
	sf::Texture m_whiteKing;

	sf::Texture m_blackPawn;
	sf::Texture m_blackKnight;
	sf::Texture m_blackBishop;
	sf::Texture m_blackRook;
	sf::Texture m_blackQueen;
	sf::Texture m_blackKing;
};

#endif //PIECEDISP_HPP