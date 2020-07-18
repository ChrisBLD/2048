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
	const float BASE_SPEED = 1000;

	//Actual speed of tile
	float m_Speed = 1000;

	//Constant value for the location of the board
	const Vector2f BOARD_LOC = Vector2f((VideoMode::getDesktopMode().width - 700.0f) / 2.0f, (VideoMode::getDesktopMode().height - 700.0f) / 2.0f);

	//Maximum scale that pieces can "pop" to
	const float MAX_SCALE = 1.2f;

	//Bool to track whether scale needs to increase or decrease
	bool m_ScaleDir;

	//Find tile size
	Vector2f m_TileSize;

	//Value of current tile = 2 * valueMultiplier
	int m_ValueMultiplier = 0;

	//Is the current tile empty?
	bool m_isEmpty;

	//Combined already this move?
	bool m_beenCombined;

	//New x/y value that the tile needs to move to
	int m_moveTo;

	//Bool to track whether tile is currently in an animation
	bool m_inAnim;

	//Direction value indicating which direction to move in
	int m_Dir;

public:
	Tile();

	void update(float elapsedTime);
	
	void pulse(float elapsedTime);

	void setStartingPos(Vector2f startingPos);
	void setValue(int val);
	void setPosition(Vector2f pos);
	void setCombined(bool dir);
	void setMoveTo(int mt);
	void setAnimate(bool anim, int dir);
	void setSpeed(int currentPos);
	void resetParams();

	bool isEmpty();

	int getValue();
	bool getCombined();
	int getMoveTo();

	bool needsAnimating();

	//Get a copy of the sprite
	Sprite getSprite();

	void restart();
};