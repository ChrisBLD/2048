#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class GameBoard
{
private:
	//Texture for game board
	Texture m_Texture;

	//Position of game board
	FloatRect m_Position;
	Vector2f m_VecPosition;

	//Sprite for game board
	Sprite m_Sprite;

public:
	//GameBoard constructor
	GameBoard();

	//Return sprite to engine
	Sprite getSprite();
};