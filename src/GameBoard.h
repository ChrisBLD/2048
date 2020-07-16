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

	//Boolean to monitor if a move has been made or not
	bool m_moveMade = false;

	//2D 4x4 array of tiles, and a copy
	Tile** tileArray = new Tile * [4];
	Tile** tileArrayCopy = new Tile * [4];


public:
	//GameBoard constructor
	GameBoard();

	//Functions for moving tiles
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void setMoveMade(bool dir);

	//Functions for animating movement
	void animRight();

	//Function for overwriting current tile array with temp tile array
	void finaliseMovement();

	//Return tile array to engine
	Tile** getTileArray();

	bool moveBeenMade();

	//Return sprite to engine
	Sprite getSprite();
};