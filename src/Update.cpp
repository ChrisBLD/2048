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

	if (tilesUpdated && m_GB.comboAnim())
	{
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				if (m_GB.getTileArray()[x][y].getCombined())
				{

					m_GB.getTileArray()[x][y].pulse(dtAsSeconds);
				}
				else
				{
					m_GB.getTileArray()[x][y].resetParams();
				}
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
		int gameOver = m_GB.isGameOver();
		if (gameOver == 1)
		{
			m_Playing = false;
			m_HUD.setGameOver(false);
			//std::cout << "Game Over!" << endl;
		}
		else if (gameOver == 2)
		{
			m_Playing = false;
			m_HUD.setGameOver(true);
		}
	}

	//std::cout << "ISPLAYING? " << m_Playing << endl;


}