#ifndef BOARDDISP_HPP
#define BOARDDISP_HPP

#include "PieceDisp.hpp"
#include "../game/Board.hpp"

class BoardDisp : public sf::Drawable
{
public :
	BoardDisp(Board&);

private :
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

private :
	PieceDisp m_pieceDisp;
	Board m_board;
};

#endif //BOARDDISP_HPP