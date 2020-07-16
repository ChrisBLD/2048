#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "GameBoard.h"

using namespace sf;

class Engine
{
private:
	//The Texture Holder
	TextureHolder textureHolder;

	//Game window
	RenderWindow m_Window;

	//Game board
	GameBoard m_GB;

	//How long has the game been running total?
	Time m_GameTimeTotal;

	//Is the player currently playing?
	bool m_Playing = false;

	void input();
	void update(float dtAsSeconds);
	void draw();

public:
	//Manages whether the tile animation has started or not
	bool m_TileAnim = false;

	//The Engine constructor
	Engine();

	void run();
};