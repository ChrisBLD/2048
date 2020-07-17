#include "Engine.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	bool tilesUpdated = true;
	int numFull = 0;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (m_GB.getTileArray()[x][y].needsAnimating())
			{
				m_GB.getTileArray()[x][y].update(dtAsSeconds);
				tilesUpdated = false;
				numFull++;
			}
			else if (!m_GB.getTileArray()[x][y].isEmpty())
			{
				numFull++;
			}
		}
	}

	//Spawn the first tiles and set score to 0
	if (numFull <= 1)
	{
		m_GB.spawnNextTile();
		m_HUD.setScore(0);
	}


	if (tilesUpdated && m_GB.moveBeenMade())
	{
		m_GB.finaliseMovement();
		m_GB.spawnNextTile();
		m_HUD.setScore(m_GB.score());
		if (m_GB.isGameOver())
		{
			m_Playing = false;
			std::cout << "Game Over!" << endl;
		}
	}


}