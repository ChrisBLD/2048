#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Tile
{
private:

	//Position of tile
	Vector2f m_Position;

	//Tile will use a sprite
	Sprite m_Sprite;

	//And have a texture
	Texture m_Texture;

	//Value of current tile = 2 * valueMultiplier
	int m_ValueMultiplier;

	//Is the current tile empty?
	bool m_isEmpty = true;

	//Combined already this move?
	bool m_beenCombined = false;

public:
	Tile();
	
	void setValue(int val);
	void setPosition(Vector2f pos);
	void setCombined(bool dir);

	bool isEmpty();

	int getValue();
	bool getCombined();

	//Get a copy of the sprite
	Sprite getSprite();
};