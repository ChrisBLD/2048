#include <string>
#include <sstream>
#include "Tile.h"
#include "TextureHolder.h"

Tile::Tile()
{
	m_ValueMultiplier = 0;
}

void Tile::setValue(int val)
{
	m_ValueMultiplier = val;

	//Get the appropriate texture for the value of the tile
	switch (val)
	{
	case 0:
		//This doesn't technically matter since the tile won't be drawn
		//if it doesn't have a value
		m_Texture = TextureHolder::GetTexture("assets/default.png");
		m_isEmpty = true;
		break;
	default:
		int number = pow(2, val);;
		string numStr = to_string(number);
		stringstream ss;
		ss << "assets/tile" << numStr << ".png";
		m_Texture = TextureHolder::GetTexture(ss.str());
		m_isEmpty = false;
		break;
	}
	m_Sprite.setTexture(m_Texture);
}

void Tile::setPosition(Vector2f pos)
{
	m_Position.x = pos.x;
	m_Position.y = pos.y;
	m_Sprite.setPosition(m_Position);
}

void Tile::setCombined(bool dir)
{
	m_beenCombined = dir;
}

bool Tile::isEmpty()
{
	return m_isEmpty;
}

int Tile::getValue()
{
	return m_ValueMultiplier;
}

bool Tile::getCombined()
{
	return m_beenCombined;
}

Sprite Tile::getSprite()
{
	return m_Sprite;
}