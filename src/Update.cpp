#include "Engine.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	bool tilesUpdated = true;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (m_GB.getTileArray()[x][y].needsAnimating())
			{
				m_GB.getTileArray()[x][y].update(dtAsSeconds);
				tilesUpdated = false;
			}
			else
			{

			}
		}
	}

	if (tilesUpdated && m_GB.moveBeenMade())
	{
		m_GB.finaliseMovement();
	}


}