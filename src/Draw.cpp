#include "Engine.h"

void Engine::draw()
{
	//Clear the screen from the last frame
	m_Window.clear(Color::White);

	m_Window.draw(m_GB.getSprite());

	m_Window.display();
}