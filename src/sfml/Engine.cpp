#include "Engine.hpp"

const sf::Time Engine::m_timePerFrame = sf::seconds(1.f/60.f);

Engine::Engine()
: m_window(sf::VideoMode(656, 656), "Chess")
, m_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")
, m_boardDisp(m_board)
, seed(std::chrono::steady_clock::now().time_since_epoch().count())
, generator(seed)
{
}

void Engine::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > m_timePerFrame)
		{
			timeSinceLastUpdate -= m_timePerFrame;
			update();
		}
		render();
	}
}

void Engine::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::Closed:
				m_window.close();
				break;
				
			default:
				break;
		}
	}
}

void Engine::update()
{
	std::uniform_int_distribution<int> distU(0, m_board.m_allowedMoves.size()-1);
	index = distU(generator);

	std::cout << "Size : " << m_board.m_allowedMoves.size() << std::endl;
	std::cout << "Choice : " << index << std::endl;

	if(m_board.m_allowedMoves.size() != 0)
		m_board.moveAPiece(*m_board.m_allowedMoves[index]);
}

void Engine::render()
{
	m_window.clear();
	m_window.draw(m_boardDisp);
	m_window.display();
}