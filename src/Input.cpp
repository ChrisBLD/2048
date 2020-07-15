#include "Engine.h"

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			//Handle the player quitting
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				m_Window.close();
			}

			//Handle the player starting the game
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				m_Playing = true;
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				m_GB.moveRight();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				m_GB.moveLeft();
			}
		}
	}
}