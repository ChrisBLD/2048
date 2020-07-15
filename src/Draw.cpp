#include "Engine.h"

void Engine::draw()
{
	//Clear the screen from the last frame
	m_Window.clear(Color::White);

	m_Window.draw(m_GB.getSprite());

	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++)
		{
			if (!m_GB.getTileArray()[i][j].isEmpty())
			{
				m_Window.draw(m_GB.getTileArray()[i][j].getSprite());
			}
		}
	}

	m_Window.display();
}