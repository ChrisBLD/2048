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

	
}

Tile** GameBoard::getTileArray()
{
	return tileArray;
}

Sprite GameBoard::getSprite()
{
	return m_Sprite;
}