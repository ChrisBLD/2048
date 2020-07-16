#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Tile
{
private:

	//Original position of the tile
	Vector2f m_StartingPos;

	//Current position of tile
	Vector2f m_Position;

	//Tile will use a sprite
	Sprite m_Sprite;

	//And have a texture
	Texture m_Texture;

	//How fast do tiles move?
	float m_Speed = 300;


	//Constant value for the location of the board
	const float BOARD_LOC = (VideoMode::getDesktopMode().width - 700.0f) / 2.0f;

	//Value of current tile = 2 * valueMultiplier
	int m_ValueMultiplier = 0;

	//Is the current tile empty?
	bool m_isEmpty = true;

	//Combined already this move?
	bool m_beenCombined = false;

	//New x/y value that the tile needs to move to
	int m_moveTo;

	//Bool to track whether tile needs animating
	bool m_inAnim = false;

	//Direction value indicating which direction to move in
	int m_Dir = 0;

public:
	Tile();

	void update(float elapsedTime);
	
	void setStartingPos(Vector2f startingPos);
	void setValue(int val);
	void setPosition(Vector2f pos);
	void setCombined(bool dir);
	void setMoveTo(int mt);
	void setAnimate(bool anim, int dir);
	void setSpeed(int currentPos);

	bool isEmpty();

	int getValue();
	bool getCombined();
	int getMoveTo();

	bool needsAnimating();

	//Get a copy of the sprite
	Sprite getSprite();
};