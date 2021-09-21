#include "BoardDisp.hpp"

BoardDisp::BoardDisp(Board& board)
: m_board(board)
{
}

void BoardDisp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f((target.getSize().x)/8.f, (target.getSize().y)/8.f));

	for (std::size_t i = 0; i < 8; ++i)
	{
		for (std::size_t j = 0; j < 8; ++j)
		{
			rectangle.setPosition((i*target.getSize().x)/8, (j*target.getSize().y)/8);
			if((i+j)%2 == 0)
				rectangle.setFillColor(sf::Color(240, 217, 181));
			else
				rectangle.setFillColor(sf::Color(181, 136, 99));

			target.draw(rectangle, states);

			sf::Sprite sprite = m_pieceDisp.getSprite(*m_board.m_cases[i+8*j]);
			sf::FloatRect rectPiece = sprite.getLocalBounds();
			sprite.scale(target.getSize().x/(rectPiece.width*8.f), target.getSize().y/(rectPiece.height*8.f));
			sprite.setPosition((i*target.getSize().x)/8, (j*target.getSize().y)/8);
			target.draw(sprite, states);
		}
	}
}