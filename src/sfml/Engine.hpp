#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <random>
#include <chrono>

#include "BoardDisp.hpp"

class Engine
{
public :
	
	Engine();
	void run();

private :
	
	void processEvents();
	void update();
	void render();
	
private :

	sf::RenderWindow m_window;
	static const sf::Time m_timePerFrame;
	
	Board m_board;
	BoardDisp m_boardDisp;

	int index;
	unsigned seed;
	std::default_random_engine generator;
};

#endif //ENGINE_HPP
