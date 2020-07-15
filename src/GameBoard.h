#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

using namespace sf;

class GameBoard
{
private:
	//Texture for game board
	Texture m_Texture;

	//Constant size of tiles
	const float SIZE_OF_TILE = 160.0f;

	//Constant starting location of first tile (x,y)
	const Vector2f STARTING_LOC = Vector2f(40.0f, 40.0f);

	//Position of game board
	FloatRect m_Position;
	Vector2f m_VecPosition;

	//Sprite for game board
	Sprite m_Sprite;

	//2D 4x4 array of tiles
	Tile** tileArray = new Tile * [4];

public:
	//GameBoard constructor
	GameBoard();

	//Functions for moving tiles
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	//Return tile array to engine
	Tile** getTileArray();

	//Return sprite to engine
	Sprite getSprite();
};