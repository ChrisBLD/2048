#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "Tile.h"
#include "TextureHolder.h"

Tile::Tile()
{
	restart();
}

void Tile::update(float elapsedTime)
{
	float maximumX = BOARD_LOC.x + 40.0f + (m_moveTo * 160.0f);
	float maximumY = BOARD_LOC.y + 40.0f + (m_moveTo * 160.0f);
	switch (m_Dir)
	{
	case 1:
		//Right
		if (m_inAnim)
		{
			if (m_Position.x == maximumX) //If we've moved as far as we need to
			{
				m_inAnim = false;
				m_Position.x = m_StartingPos.x;
				m_isEmpty = true;
			}
			else
			{
				m_Position.x += m_Speed * elapsedTime;
				if (m_Position.x > maximumX)
				{
					m_Position.x = maximumX;
				}
			}
		}
		break;
	case 2:
		//Left
		if (m_inAnim)
		{
			if (m_Position.x == maximumX) //If we've moved as far as we need to
			{
				m_inAnim = false;
				m_Position.x = m_StartingPos.x;
				m_isEmpty = true;
			}
			else
			{
				m_Position.x -= m_Speed * elapsedTime;
				if (m_Position.x < maximumX)
				{
					m_Position.x = maximumX;
				}
			}
		}
		break;
	case 3:
		//Up
		if (m_inAnim)
		{
			if (m_Position.y == maximumY) //If we've moved as far as we need to
			{
				m_inAnim = false;
				m_Position.y = m_StartingPos.y;
				m_isEmpty = true;
			}
			else
			{
				m_Position.y -= m_Speed * elapsedTime;
				if (m_Position.y < maximumY)
				{
					m_Position.y = maximumY;
				}
			}
		}
		break;
	case 4:
		//Down
		if (m_inAnim)
		{
			if (m_Position.y == maximumY) //If we've moved as far as we need to
			{
				m_inAnim = false;
				m_Position.y = m_StartingPos.y;
				m_isEmpty = true;
			}
			else
			{
				m_Position.y += m_Speed * elapsedTime;
				if (m_Position.y > maximumY)
				{
					m_Position.y = maximumY;
				}
			}
		}
		break;
	}

	m_Sprite.setPosition(m_Position);
}

void Tile::pulse(float elapsedTime)
{
	elapsedTime *= 10.0f;
	Vector2f currentScale = m_Sprite.getScale();
	if (m_ScaleDir)
	{
		//True = scale up
		if (currentScale.x < MAX_SCALE)
		{
			currentScale.x += (MAX_SCALE - 1) * elapsedTime;
			currentScale.y += (MAX_SCALE - 1) * elapsedTime;
			//We need to see how much "bigger" the tile has gotten
			m_Position.x = m_StartingPos.x - ((m_TileSize.x * currentScale.x) - m_TileSize.x) / 2.0f;
			m_Position.y = m_StartingPos.y - ((m_TileSize.y * currentScale.y) - m_TileSize.y) / 2.0f;
		}
		else
		{
			currentScale.x = MAX_SCALE;
			currentScale.y = MAX_SCALE;
			m_Position.x = m_StartingPos.x - ((m_TileSize.x * currentScale.x) - m_TileSize.x) / 2.0f;
			m_Position.y = m_StartingPos.y - ((m_TileSize.y * currentScale.y) - m_TileSize.y) / 2.0f;
			m_ScaleDir = false;
		}
	}
	else
	{
		//False - scale down
		if (currentScale.x > 1.0f)
		{
			currentScale.x -= (MAX_SCALE - 1) * elapsedTime;
			currentScale.y -= (MAX_SCALE - 1) * elapsedTime;
			m_Position.x = m_StartingPos.x - ((m_TileSize.x * currentScale.x) - m_TileSize.x) / 2.0f;
			m_Position.y = m_StartingPos.y - ((m_TileSize.y * currentScale.y) - m_TileSize.y) / 2.0f;
		}
		else
		{
			currentScale.x = 1.0f;
			currentScale.y = 1.0f;
			m_Position.x = m_StartingPos.x;
			m_Position.y = m_StartingPos.y;
			m_ScaleDir = true;
			m_beenCombined = false;
		}
	}

	m_Sprite.setPosition(m_Position);
	m_Sprite.setScale(currentScale);

}

void Tile::setStartingPos(Vector2f startingPos)
{
	m_StartingPos = startingPos;
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
		m_Sprite.setTexture(TextureHolder::GetTexture("assets/default.png"));
		m_TileSize = Vector2f(m_Sprite.getLocalBounds().width, m_Sprite.getLocalBounds().height);
		m_isEmpty = true;
		break;
	default:
		int number = pow(2, val);;
		string numStr = to_string(number);
		stringstream ss;
		ss << "assets/tile" << numStr << ".png";
		m_Sprite.setTexture(TextureHolder::GetTexture(ss.str()));
		m_TileSize = Vector2f(m_Sprite.getLocalBounds().width, m_Sprite.getLocalBounds().height);
		m_isEmpty = false;
		break;
	}
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

void Tile::setMoveTo(int mt)
{
	m_moveTo = mt;
}

void Tile::setAnimate(bool anim, int dir)
{
	m_Dir = dir;
	m_inAnim = anim;
}

void Tile::setSpeed(int currentPos)
{
	m_Speed = BASE_SPEED * abs(m_moveTo - currentPos);
}

void Tile::resetParams()
{
	m_Sprite.setScale(Vector2f(1.0f, 1.0f));
	m_Position.x = m_StartingPos.x;
	m_Position.y = m_StartingPos.y;
	m_Sprite.setPosition(m_Position);
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

int Tile::getMoveTo()
{
	return m_moveTo;
}

bool Tile::needsAnimating()
{
	return m_inAnim;
}

Sprite Tile::getSprite()
{
	return m_Sprite;
}

void Tile::restart()
{
	m_ValueMultiplier = 0;
	m_moveTo = -1;
	m_inAnim = false;
	m_beenCombined = false;
	m_isEmpty = true;
	m_Dir = 0;
	m_ScaleDir = true;
	//m_Sprite.setOrigin(m_Sprite.getLocalBounds().width / 2.0f, m_Sprite.getLocalBounds().height / 2.0f);
}