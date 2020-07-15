#include "GameBoard.h"
#include "TextureHolder.h"


GameBoard::GameBoard()
{
	m_Texture = TextureHolder::GetTexture("assets/gameboard.png");

	m_Sprite.setTexture(m_Texture);

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	//We want the square to be in the middle of the screen
	//x = res - 700 / 2
	m_Position = FloatRect((resolution.x - 700.0f) / 2.0f, (resolution.y - 700.0f) / 2.0f, 700.0f, 700.0f);
	m_VecPosition = Vector2f(m_Position.left, m_Position.top);
	m_Sprite.setPosition(m_VecPosition);

	//Add Tile arrays to the existing tile array for a 2D Tile Array
	//and set their positions relative to the game board
	for (int i = 0; i < 4; i++)
	{
		tileArray[i] = new Tile[4];
		for (int j = 0; j < 4; j++)
		{
			tileArray[i][j].setValue(0);
			tileArray[i][j].setPosition(
				Vector2f(STARTING_LOC.x + (i * SIZE_OF_TILE) + m_Position.left,
					     STARTING_LOC.y + (j * SIZE_OF_TILE) + m_Position.top));
		}
	}

	//Test assignments
	tileArray[1][0].setValue(2);
	tileArray[2][0].setValue(2);
	tileArray[3][0].setValue(4);
	tileArray[1][1].setValue(3);
	tileArray[2][1].setValue(3);
	tileArray[3][1].setValue(4);
	tileArray[1][2].setValue(5);
	tileArray[2][2].setValue(5);
	tileArray[3][2].setValue(4);
	

}

void GameBoard::moveRight()
{
	//First we want to reset the value of the beenCombined bool for each tile
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tileArray[i][j].setCombined(false);
		}
	}

	int xLong = 0;
	int maxEmpty = 0;
	//When we move right, we don't need to move the tiles in the rightmost column
	//We work back to front, moving the rightmost tiles first.
	for (int y = 0; y < 4; y++)
	{
		//First we make an array of booleans to track the isEmpty() status of the current row
		bool empty[4];
		empty[0] = tileArray[0][y].isEmpty();
		empty[1] = tileArray[1][y].isEmpty();
		empty[2] = tileArray[2][y].isEmpty();
		empty[3] = tileArray[3][y].isEmpty();

		for (int x = 2; x >= 0; x--)
		{
			//If the current tile is not empty, we need to see how far right we can move
			if (!empty[x]) 
			{
				//This while loop will check all tiles to the right of the current one to find
				//the furthest right that is empty, which will be stored in the value maxEmpty.
				//If we find any value that isn't empty along the way, we must immediately break
				//from this as we can't jump over tiles with values.
				xLong = x+1;
				while (xLong < 4)
				{
					if (empty[xLong])
					{
						maxEmpty = xLong;
					}
					else
					{
						xLong = 3;
					}
					xLong++;
				}
				if (maxEmpty != 0)
				{
					//Now we've found the rightmost empty value, we can move our current tile to that location
					tileArray[maxEmpty][y].setValue(tileArray[x][y].getValue());
					tileArray[x][y].setValue(0);
					//And of course update the empty array that we're using to track our row
					empty[x] = true;
					empty[maxEmpty] = false;
				}

			}
		}

	}
	
	xLong = 0;
	//When combining values after a move right, we don't need to check the rightmost column
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			//If the tile to the right matches this, then combine
			if (tileArray[x][y].getValue() == tileArray[x + 1][y].getValue())
			{
				//--only if the tile hasn't already been combined this move
				if (!tileArray[x][y].getCombined() && tileArray[x][y].getValue() != 0)
				{
					tileArray[x + 1][y].setValue(tileArray[x][y].getValue() + 1);
					//tileArray[x][y].setCombined(true);
					tileArray[x + 1][y].setCombined(true);

					tileArray[x][y].setValue(0);

					//After we perform a combination, we need to move all previous tiles along one
					xLong = x;
					while (xLong > 0)
					{
						tileArray[xLong][y].setValue(tileArray[xLong - 1][y].getValue());
						xLong--;
					}

					//if = 11 then we've reached the 2048 tile and the game should end
				}

			}
		}
	}
	
	

}

void GameBoard::moveLeft()
{
	//First we want to reset the value of the beenCombined bool for each tile
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tileArray[i][j].setCombined(false);
		}
	}

	int xLong = 3;
	int maxEmpty = 3;
	//When we move left, we don't need to move the tiles in the leftmost column
	//We work back to front, moving the leftmost tiles first.
	for (int y = 0; y < 4; y++)
	{
		//First we make an array of booleans to track the isEmpty() status of the current row
		bool empty[4];
		empty[0] = tileArray[0][y].isEmpty();
		empty[1] = tileArray[1][y].isEmpty();
		empty[2] = tileArray[2][y].isEmpty();
		empty[3] = tileArray[3][y].isEmpty();

		for (int x = 1; x < 4; x++)
		{
			//If the current tile is not empty, we need to see how far right we can move
			if (!empty[x])
			{
				//This while loop will check all tiles to the right of the current one to find
				//the furthest right that is empty, which will be stored in the value maxEmpty.
				//If we find any value that isn't empty along the way, we must immediately break
				//from this as we can't jump over tiles with values.
				xLong = x - 1;
				while (xLong >= 0)
				{
					if (empty[xLong])
					{
						maxEmpty = xLong;
					}
					else
					{
						xLong = 0;
					}
					xLong--;
				}
				if (maxEmpty != 3)
				{
					//Now we've found the rightmost empty value, we can move our current tile to that location
					tileArray[maxEmpty][y].setValue(tileArray[x][y].getValue());
					tileArray[x][y].setValue(0);
					//And of course update the empty array that we're using to track our row
					empty[x] = true;
					empty[maxEmpty] = false;
				}
			}
		}
	}

	xLong = 0;
	//When combining values after a move left, we don't need to check for the leftmost column
	for (int x = 3; x >= 1; x--)
	{
		for (int y = 0; y < 4; y++)
		{
			//If the tile to the left matches this, then combine
			if (tileArray[x][y].getValue() == tileArray[x - 1][y].getValue())
			{
				//--only if the tile hasn't already been combined this move
				if (!tileArray[x][y].getCombined() && tileArray[x][y].getValue() != 0)
				{
					tileArray[x - 1][y].setValue(tileArray[x][y].getValue() + 1);
					tileArray[x][y].setCombined(true);
					tileArray[x - 1][y].setCombined(true);

					tileArray[x][y].setValue(0);

					//After we perform a combination, we need to move all previous tiles along one
					xLong = x;
					while (xLong < 3)
					{
						tileArray[xLong][y].setValue(tileArray[xLong + 1][y].getValue());
						xLong++;
					}
					//if = 11 then we've reached the 2048 tile and the game should end
				}

			}
		}
	}

}

Tile** GameBoard::getTileArray()
{
	return tileArray;
}

Sprite GameBoard::getSprite()
{
	return m_Sprite;
}