#include "Engine.h"

Engine::Engine()
{
	//Get the screen resolution
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y), "2048", Style::Fullscreen);

}

void Engine::run()
{
	//Timing
	Clock clock;
	m_Playing = true;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		//Update the total game time
		m_GameTimeTotal += dt;
		//Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}