#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

using namespace sf;

struct TileCopy {
	int value;
	bool combined;
	int moveTo;
};



class GameBoard
{
private:
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

	//Boolean to check if we need to start combo animation
	bool m_ComboTime = false;

	//Integer to track score to add to UI
	int m_Score;

	//2D 4x4 array of tiles, a copy for rotation and an array of structures for processing moves
	Tile** tileArray = new Tile * [4];
	TileCopy tileArrayCopy[4][4];
	Tile** tileArrayRotate = new Tile * [4];
	TileCopy tileArrayCopyRotate[4][4];
	
	//Create an array of coordinates for empty tiles
	std::vector<Vector2i> emptyTiles = { {} };


public:
	//GameBoard constructor
	GameBoard();

	//Functions for moving tiles
	bool move(Tile** tileArrayToUse);
	void animate(int dir);

	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();
	void setMoveMade(bool dir);

	//Function for overwriting current tile array with temp tile array
	void finaliseMovement();

	//Function for spawning new tile after a move has been made
	void spawnNextTile();

	//Function for checking if a game has finished
	int isGameOver();

	//Return tile array to engine
	Tile** getTileArray();

	//Check if a move has been made
	bool moveBeenMade();

	//Check if it's time to start combo animation
	bool comboAnim();

	//See what score we need to add
	int score();

	//Return sprite to engine
	Sprite getSprite();

	//Restart the board
	void restart();
};