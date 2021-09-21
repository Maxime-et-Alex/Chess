#include <iostream>

#include "sfml/Engine.hpp"

int main()
{
	try
	{
		Engine engine;
		engine.run();
	}
	catch (std::runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
		return 1;
	}
	
    return 0;
}
