#include "Engine.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	bool tilesUpdated = true;
	bool allEmpty = true;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (m_GB.getTileArray()[x][y].needsAnimating())
			{
				m_GB.getTileArray()[x][y].update(dtAsSeconds);
				tilesUpdated = false;
				allEmpty = false;
			}
			else if (!m_GB.getTileArray()[x][y].isEmpty())
			{
				allEmpty = false;
			}
		}
	}

	//Spawn the first tile
	if (allEmpty)
	{
		m_GB.spawnNextTile();
	}


	if (tilesUpdated && m_GB.moveBeenMade())
	{
		m_GB.finaliseMovement();
		m_GB.spawnNextTile();
		if (m_GB.isGameOver())
		{
			//Game over handling
			std::cout << "Game Over!" << endl;
		}
	}


}