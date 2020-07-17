#include "GameBoard.h"
#include "TextureHolder.h"
#include <iostream>
#include <map>

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
		tileArrayRotate[i] = new Tile[4];
		for (int j = 0; j < 4; j++)
		{
			tileArray[i][j].setValue(0);
			tileArray[i][j].setPosition(
				Vector2f(STARTING_LOC.x + (i * SIZE_OF_TILE) + m_Position.left,
					     STARTING_LOC.y + (j * SIZE_OF_TILE) + m_Position.top));
			tileArray[i][j].setStartingPos(
				Vector2f(STARTING_LOC.x + (i * SIZE_OF_TILE) + m_Position.left,
						 STARTING_LOC.y + (j * SIZE_OF_TILE) + m_Position.top));
		}
	}

	//Seed the random number generator
	srand((int)time(0));



	//Test assignments
	//tileArray[0][0].setValue(4);
	//tileArray[0][1].setValue(3);
	//tileArray[0][2].setValue(2);
	//tileArray[0][3].setValue(2);

	//tileArray[0][2].setValue(3);
	//tileArray[0][3].setValue(3);


	//tileArray[3][0].setValue(5);

	//tileArray[0][0].setValue(2);
	//tileArray[1][0].setValue(2);
	//tileArray[2][0].setValue(3);
	//tileArray[3][0].setValue(4);

	tileArray[0][3].setValue(1);
	tileArray[1][3].setValue(0);
	tileArray[2][3].setValue(1);
	tileArray[3][3].setValue(2);

	//tileArray[2][3].setValue(2);
	//tileArray[3][3].setValue(2);


	//tileArray[0][0].setValue(0); tileArray[1][0].setValue(1); tileArray[2][0].setValue(0); tileArray[3][0].setValue(3);
	//tileArray[0][1].setValue(0); tileArray[1][1].setValue(2); tileArray[2][1].setValue(0); tileArray[3][1].setValue(4);
	//tileArray[0][2].setValue(0); tileArray[1][2].setValue(6); tileArray[2][2].setValue(2); tileArray[3][2].setValue(2);
	//tileArray[0][3].setValue(2); tileArray[1][3].setValue(5); tileArray[2][3].setValue(3); tileArray[3][3].setValue(1);

	

}

void GameBoard::move(Tile** tileArrayToUse)
{
	setMoveMade(true);


	//We want to create a temporary copy of the tile array to hold the state of the board after all changes have been made
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tileArrayCopy[i][j].value = tileArrayToUse[i][j].getValue();
			tileArrayCopy[i][j].combined = false;
			tileArrayCopy[i][j].moveTo = -1;
			//moveTo = -1 is a default value indicating that the tile doesn't need to be moved
			tileArrayToUse[i][j].setMoveTo(-1);
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
		empty[0] = (tileArrayCopy[0][y].value == 0);
		empty[1] = (tileArrayCopy[1][y].value == 0);
		empty[2] = (tileArrayCopy[2][y].value == 0);
		empty[3] = (tileArrayCopy[3][y].value == 0);
		
		for (int x = 2; x >= 0; x--)
		{
			//If the current tile is not empty, we need to see how far right we can move
			if (!empty[x])
			{
				//This while loop will check all tiles to the right of the current one to find
				//the furthest right that is empty, which will be stored in the value maxEmpty.
				//If we find any value that isn't empty along the way, we must immediately break
				//from this as we can't jump over tiles with values.
				xLong = x + 1;
				maxEmpty = 0;
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
					if (maxEmpty != 3)
					{
						int currentTileValue = tileArrayCopy[x][y].value;
						int nextTileValue = tileArrayCopy[maxEmpty + 1][y].value;
						if (tileArrayCopy[x][y].value == tileArrayCopy[maxEmpty + 1][y].value)
						{
							tileArrayToUse[x][y].setMoveTo(maxEmpty + 1);
						}
						else
						{
							tileArrayToUse[x][y].setMoveTo(maxEmpty);
						}
					}
					else
					{
						tileArrayToUse[x][y].setMoveTo(maxEmpty);
					}

					//Now we've found the rightmost empty value, we can move our current tile to that location
					tileArrayCopy[maxEmpty][y].value = (tileArrayCopy[x][y].value);
					tileArrayCopy[x][y].value = 0;

					//And of course update the empty array that we're using to track our row
					empty[x] = true;
					empty[maxEmpty] = false;
				}

			}
		}

	}

	std::cout << "This is the tileArrayCopy state after movement applied:" << endl
		<< tileArrayCopy[0][0].value << " " << tileArrayCopy[1][0].value << " " << tileArrayCopy[2][0].value << " " << tileArrayCopy[3][0].value << "\n"
		<< tileArrayCopy[0][1].value << " " << tileArrayCopy[1][1].value << " " << tileArrayCopy[2][1].value << " " << tileArrayCopy[3][1].value << "\n"
		<< tileArrayCopy[0][2].value << " " << tileArrayCopy[1][2].value << " " << tileArrayCopy[2][2].value << " " << tileArrayCopy[3][2].value << "\n"
		<< tileArrayCopy[0][3].value << " " << tileArrayCopy[1][3].value << " " << tileArrayCopy[2][3].value << " " << tileArrayCopy[3][3].value << "\n";


	std::cout << "This is where all values need to move to AFTER MOVEMENT:" << endl
		<< tileArray[0][0].getMoveTo() << " " << tileArray[1][0].getMoveTo() << " " << tileArray[2][0].getMoveTo() << " " << tileArray[3][0].getMoveTo() << "\n"
		<< tileArray[0][1].getMoveTo() << " " << tileArray[1][1].getMoveTo() << " " << tileArray[2][1].getMoveTo() << " " << tileArray[3][1].getMoveTo() << "\n"
		<< tileArray[0][2].getMoveTo() << " " << tileArray[1][2].getMoveTo() << " " << tileArray[2][2].getMoveTo() << " " << tileArray[3][2].getMoveTo() << "\n"
		<< tileArray[0][3].getMoveTo() << " " << tileArray[1][3].getMoveTo() << " " << tileArray[2][3].getMoveTo() << " " << tileArray[3][3].getMoveTo() << "\n";

	xLong = 0;
	//When combining values after a move right, we don't need to check the leftmost column
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x > 0; x--)
		{
			//If the tile to the left matches this, then combine
			if (tileArrayCopy[x][y].value == tileArrayCopy[x - 1][y].value)
			{
				//--only if the tile hasn't already been combined this move
				if (!tileArrayCopy[x][y].combined && tileArrayCopy[x][y].value != 0)
				{
					//tileArray[x-1]
					//tileArrayCopy[x][y].setMoveTo(x + 1);

					tileArrayCopy[x][y].value++;
					//tileArray[x][y].setCombined(true);
					tileArrayCopy[x][y].combined = true;

					tileArrayCopy[x - 1][y].value = 0;


					tileArrayToUse[x - 1][y].setMoveTo(x);

					//After we perform a combination, we need to move all previous tiles along one
					xLong = x-1;
					while (xLong >= 1)
					{
						tileArrayCopy[xLong][y].value = (tileArrayCopy[xLong - 1][y].value);
						tileArrayCopy[xLong - 1][y].value = 0;
						if (tileArrayToUse[xLong - 1][y].getMoveTo() == -1)
						{
							tileArrayToUse[xLong - 1][y].setMoveTo(xLong);
						}
						xLong--;
					}
					

					//if = 11 then we've reached the 2048 tile and the game should end
				}

			}
			std::cout << "This is the tileArrayCopy state after stage of the movement:" << endl
				<< tileArrayCopy[0][0].value << " " << tileArrayCopy[1][0].value << " " << tileArrayCopy[2][0].value << " " << tileArrayCopy[3][0].value << "\n"
				<< tileArrayCopy[0][1].value << " " << tileArrayCopy[1][1].value << " " << tileArrayCopy[2][1].value << " " << tileArrayCopy[3][1].value << "\n"
				<< tileArrayCopy[0][2].value << " " << tileArrayCopy[1][2].value << " " << tileArrayCopy[2][2].value << " " << tileArrayCopy[3][2].value << "\n"
				<< tileArrayCopy[0][3].value << " " << tileArrayCopy[1][3].value << " " << tileArrayCopy[2][3].value << " " << tileArrayCopy[3][3].value << "\n";


		}
	}


	std::cout << "This is the tileArrayCopy state after movement and combination applied:" << endl
		<< tileArrayCopy[0][0].value << " " << tileArrayCopy[1][0].value << " " << tileArrayCopy[2][0].value << " " << tileArrayCopy[3][0].value << "\n"
		<< tileArrayCopy[0][1].value << " " << tileArrayCopy[1][1].value << " " << tileArrayCopy[2][1].value << " " << tileArrayCopy[3][1].value << "\n"
		<< tileArrayCopy[0][2].value << " " << tileArrayCopy[1][2].value << " " << tileArrayCopy[2][2].value << " " << tileArrayCopy[3][2].value << "\n"
		<< tileArrayCopy[0][3].value << " " << tileArrayCopy[1][3].value << " " << tileArrayCopy[2][3].value << " " << tileArrayCopy[3][3].value << "\n";



}


void GameBoard::animate(int dir)
{
	//In here, we need to animate the movements that are going to happen
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			//Animate the tile to move to its new location
			int getMoveTo = tileArray[x][y].getMoveTo();
			if (dir == 1 || dir == 2)
			{
				//Left or Right
				if (tileArray[x][y].getMoveTo() != x && tileArray[x][y].getMoveTo() != -1)
				{
					tileArray[x][y].setSpeed(x);
					tileArray[x][y].setAnimate(true, dir);
				}
			}
			else
			{
				//Up or down
				if (tileArray[x][y].getMoveTo() != y && tileArray[x][y].getMoveTo() != -1)
				{
					tileArray[x][y].setSpeed(y);
					tileArray[x][y].setAnimate(true, dir);
				}
			}
		}
	}
}

void GameBoard::moveRight()
{
	move(tileArray);

	std::cout << "This is the board state according to tileArray:" << endl
		<< tileArray[0][0].getValue() << " " << tileArray[1][0].getValue() << " " << tileArray[2][0].getValue() << " " << tileArray[3][0].getValue() << "\n"
		<< tileArray[0][1].getValue() << " " << tileArray[1][1].getValue() << " " << tileArray[2][1].getValue() << " " << tileArray[3][1].getValue() << "\n"
		<< tileArray[0][2].getValue() << " " << tileArray[1][2].getValue() << " " << tileArray[2][2].getValue() << " " << tileArray[3][2].getValue() << "\n"
		<< tileArray[0][3].getValue() << " " << tileArray[1][3].getValue() << " " << tileArray[2][3].getValue() << " " << tileArray[3][3].getValue() << "\n";

	std::cout << "This is where all values need to move to:" << endl
		<< tileArray[0][0].getMoveTo() << " " << tileArray[1][0].getMoveTo() << " " << tileArray[2][0].getMoveTo() << " " << tileArray[3][0].getMoveTo() << "\n"
		<< tileArray[0][1].getMoveTo() << " " << tileArray[1][1].getMoveTo() << " " << tileArray[2][1].getMoveTo() << " " << tileArray[3][1].getMoveTo() << "\n"
		<< tileArray[0][2].getMoveTo() << " " << tileArray[1][2].getMoveTo() << " " << tileArray[2][2].getMoveTo() << " " << tileArray[3][2].getMoveTo() << "\n"
		<< tileArray[0][3].getMoveTo() << " " << tileArray[1][3].getMoveTo() << " " << tileArray[2][3].getMoveTo() << " " << tileArray[3][3].getMoveTo() << "\n";

	animate(1);
}

void GameBoard::moveLeft()
{
	int moveToX = 0;
	int moveToY = 0;

	std::map<int, int> valMap = { {0,3},{1,2},{2,1},{3,0},{-1,-1} };

	//When moving to the left, we will just rotate the board by 180 and run the moveRight function
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			tileArrayRotate[y][x].setValue(tileArray[valMap[y]][valMap[x]].getValue());
		}
	}

	move(tileArrayRotate);


	//And rotate back before animating

	TileCopy tileArrayCopyRotate[4][4];

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			tileArray[valMap[x]][valMap[y]].setValue(tileArrayRotate[x][y].getValue());
			tileArray[valMap[x]][valMap[y]].setMoveTo(valMap[tileArrayRotate[x][y].getMoveTo()]);
			tileArrayCopyRotate[x][y].value = tileArrayCopy[x][y].value;
		}
	}

	//And rotate the array of structures we made back
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			tileArrayCopy[valMap[x]][valMap[y]].value = tileArrayCopyRotate[x][y].value;
		}
	}

	std::cout << "This is the board state according to tileArray:" << endl
		<< tileArray[0][0].getValue() << " " << tileArray[1][0].getValue() << " " << tileArray[2][0].getValue() << " " << tileArray[3][0].getValue() << "\n"
		<< tileArray[0][1].getValue() << " " << tileArray[1][1].getValue() << " " << tileArray[2][1].getValue() << " " << tileArray[3][1].getValue() << "\n"
		<< tileArray[0][2].getValue() << " " << tileArray[1][2].getValue() << " " << tileArray[2][2].getValue() << " " << tileArray[3][2].getValue() << "\n"
		<< tileArray[0][3].getValue() << " " << tileArray[1][3].getValue() << " " << tileArray[2][3].getValue() << " " << tileArray[3][3].getValue() << "\n";

	std::cout << "This is where all values need to move to:" << endl
		<< tileArray[0][0].getMoveTo() << " " << tileArray[1][0].getMoveTo() << " " << tileArray[2][0].getMoveTo() << " " << tileArray[3][0].getMoveTo() << "\n"
		<< tileArray[0][1].getMoveTo() << " " << tileArray[1][1].getMoveTo() << " " << tileArray[2][1].getMoveTo() << " " << tileArray[3][1].getMoveTo() << "\n"
		<< tileArray[0][2].getMoveTo() << " " << tileArray[1][2].getMoveTo() << " " << tileArray[2][2].getMoveTo() << " " << tileArray[3][2].getMoveTo() << "\n"
		<< tileArray[0][3].getMoveTo() << " " << tileArray[1][3].getMoveTo() << " " << tileArray[2][3].getMoveTo() << " " << tileArray[3][3].getMoveTo() << "\n";

	animate(2);
}

void GameBoard::moveUp()
{
	int moveToX = 0;
	int moveToY = 0;

	std::map<int, int> valMap = { {0,3},{1,2},{2,1},{3,0},{-1,-1} };

	//When moving up, we will just rotate the board by 90 and run the moveRight function
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			tileArrayRotate[x][y].setValue(tileArray[y][valMap[x]].getValue());
		}
	}


	move(tileArrayRotate);


	//And rotate back before animating

	TileCopy tileArrayCopyRotate[4][4];

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			tileArray[y][valMap[x]].setValue(tileArrayRotate[x][y].getValue());

			tileArray[x][y].setMoveTo(valMap[tileArrayRotate[valMap[y]][x].getMoveTo()]);
			tileArrayCopyRotate[x][y].value = tileArrayCopy[x][y].value;
		}
	}

	//And rotate the array of structures we made back
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			tileArrayCopy[y][valMap[x]].value = tileArrayCopyRotate[x][y].value;
		}
	}

	std::cout << "This is the board state according to tileArray:" << endl
		<< tileArray[0][0].getValue() << " " << tileArray[1][0].getValue() << " " << tileArray[2][0].getValue() << " " << tileArray[3][0].getValue() << "\n"
		<< tileArray[0][1].getValue() << " " << tileArray[1][1].getValue() << " " << tileArray[2][1].getValue() << " " << tileArray[3][1].getValue() << "\n"
		<< tileArray[0][2].getValue() << " " << tileArray[1][2].getValue() << " " << tileArray[2][2].getValue() << " " << tileArray[3][2].getValue() << "\n"
		<< tileArray[0][3].getValue() << " " << tileArray[1][3].getValue() << " " << tileArray[2][3].getValue() << " " << tileArray[3][3].getValue() << "\n";

	std::cout << "This is where all values need to move to:" << endl
		<< tileArray[0][0].getMoveTo() << " " << tileArray[1][0].getMoveTo() << " " << tileArray[2][0].getMoveTo() << " " << tileArray[3][0].getMoveTo() << "\n"
		<< tileArray[0][1].getMoveTo() << " " << tileArray[1][1].getMoveTo() << " " << tileArray[2][1].getMoveTo() << " " << tileArray[3][1].getMoveTo() << "\n"
		<< tileArray[0][2].getMoveTo() << " " << tileArray[1][2].getMoveTo() << " " << tileArray[2][2].getMoveTo() << " " << tileArray[3][2].getMoveTo() << "\n"
		<< tileArray[0][3].getMoveTo() << " " << tileArray[1][3].getMoveTo() << " " << tileArray[2][3].getMoveTo() << " " << tileArray[3][3].getMoveTo() << "\n";

	animate(3);
}

void GameBoard::moveDown()
{
	int moveToX = 0;
	int moveToY = 0;

	std::map<int, int> valMap = { {0,3},{1,2},{2,1},{3,0},{-1,-1} };

	//When moving up, we will just rotate the board by 90 and run the moveRight function
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			tileArrayRotate[x][y].setValue(tileArray[valMap[y]][x].getValue());
		}
	}


	move(tileArrayRotate);


	//And rotate back before animating

	TileCopy tileArrayCopyRotate[4][4];

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			tileArray[valMap[y]][x].setValue(tileArrayRotate[x][y].getValue());

			tileArray[x][y].setMoveTo(tileArrayRotate[y][valMap[x]].getMoveTo());
			tileArrayCopyRotate[x][y].value = tileArrayCopy[x][y].value;
		}
	}

	//And rotate the array of structures we made back
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			tileArrayCopy[valMap[y]][x].value = tileArrayCopyRotate[x][y].value;
		}
	}

	std::cout << "This is the board state according to tileArray:" << endl
		<< tileArray[0][0].getValue() << " " << tileArray[1][0].getValue() << " " << tileArray[2][0].getValue() << " " << tileArray[3][0].getValue() << "\n"
		<< tileArray[0][1].getValue() << " " << tileArray[1][1].getValue() << " " << tileArray[2][1].getValue() << " " << tileArray[3][1].getValue() << "\n"
		<< tileArray[0][2].getValue() << " " << tileArray[1][2].getValue() << " " << tileArray[2][2].getValue() << " " << tileArray[3][2].getValue() << "\n"
		<< tileArray[0][3].getValue() << " " << tileArray[1][3].getValue() << " " << tileArray[2][3].getValue() << " " << tileArray[3][3].getValue() << "\n";

	std::cout << "This is where all values need to move to:" << endl
		<< tileArray[0][0].getMoveTo() << " " << tileArray[1][0].getMoveTo() << " " << tileArray[2][0].getMoveTo() << " " << tileArray[3][0].getMoveTo() << "\n"
		<< tileArray[0][1].getMoveTo() << " " << tileArray[1][1].getMoveTo() << " " << tileArray[2][1].getMoveTo() << " " << tileArray[3][1].getMoveTo() << "\n"
		<< tileArray[0][2].getMoveTo() << " " << tileArray[1][2].getMoveTo() << " " << tileArray[2][2].getMoveTo() << " " << tileArray[3][2].getMoveTo() << "\n"
		<< tileArray[0][3].getMoveTo() << " " << tileArray[1][3].getMoveTo() << " " << tileArray[2][3].getMoveTo() << " " << tileArray[3][3].getMoveTo() << "\n";

	animate(4);
}

void GameBoard::setMoveMade(bool dir)
{
	m_moveMade = dir;
}


void GameBoard::finaliseMovement()
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			int test = tileArrayCopy[x][y].value;
			tileArray[x][y].setValue(tileArrayCopy[x][y].value);
		}
	}

	setMoveMade(false);
}



void GameBoard::spawnNextTile()
{
	//Here we want to make a new tile appear in an spot that is currently empty.
	//First, we need to find out which tiles are empty and add them to the emptyTiles array.
	
	emptyTiles.clear();
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (tileArray[x][y].isEmpty())
			{
				emptyTiles.push_back({ x,y });
			}
		}
	}

	//Now we need to select one at random
	int indexOfNext = rand() % emptyTiles.size();
	Vector2i nextTileLoc = Vector2i(emptyTiles[indexOfNext].x, emptyTiles[indexOfNext].y);

	//And we drop a 2 tile in there (except for 10% of the time, we drop a 4 tile)
	if (rand() % 10 < 9)
	{
		tileArray[nextTileLoc.x][nextTileLoc.y].setValue(1);
	}
	else
	{
		tileArray[nextTileLoc.x][nextTileLoc.y].setValue(2);
	}

	std::cout << endl << "This is the board state AFTER all movement and new tile spawned" << endl
		<< tileArray[0][0].getValue() << " " << tileArray[1][0].getValue() << " " << tileArray[2][0].getValue() << " " << tileArray[3][0].getValue() << "\n"
		<< tileArray[0][1].getValue() << " " << tileArray[1][1].getValue() << " " << tileArray[2][1].getValue() << " " << tileArray[3][1].getValue() << "\n"
		<< tileArray[0][2].getValue() << " " << tileArray[1][2].getValue() << " " << tileArray[2][2].getValue() << " " << tileArray[3][2].getValue() << "\n"
		<< tileArray[0][3].getValue() << " " << tileArray[1][3].getValue() << " " << tileArray[2][3].getValue() << " " << tileArray[3][3].getValue() << "\n";



}

Tile** GameBoard::getTileArray()
{
	return tileArray;
}

bool GameBoard::moveBeenMade()
{
	return m_moveMade;
}

Sprite GameBoard::getSprite()
{
	return m_Sprite;
}