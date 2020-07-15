#include <string>
#include <sstream>
#include "Tile.h"
#include "TextureHolder.h"

Tile::Tile()
{

}

void Tile::setValue(int val)
{
	m_ValueMultiplier = val;

	int number = 2 ^ val;
	string numStr = to_string(number);

	//Get the appropriate texture for the value of the tile
	switch (val)
	{
	case 0:
		//This doesn't technically matter since the tile won't be drawn
		//if it doesn't have a value
		m_Texture = TextureHolder::GetTexture("assets/default.png");
		break;
	default:
		stringstream ss;
		ss << "assets/tile" << numStr << ".png";
		m_Texture = TextureHolder::GetTexture(ss.str());
	}
	m_Sprite.setTexture(m_Texture);
}

void Tile::setPosition(Vector2f pos)
{
	m_Position.x = pos.x;
	m_Position.y = pos.y;
	m_Sprite.setPosition(m_Position);
}

bool Tile::isEmpty()
{
	return m_isEmpty;
}

Sprite Tile::getSprite()
{
	return m_Sprite;
}