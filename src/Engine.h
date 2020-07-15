#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

using namespace sf;

class Engine
{
private:
	//The Texture Holder
	TextureHolder textureHolder;

	//Game window
	RenderWindow m_Window;

	//Game board texture
	Texture m_GameBoardTexture;

	//How long has the game been running total?
	Time m_GameTimeTotal;

	void input();
	void update(float dtAsSeconds);
	void draw();

public:
	//The Engine constructor
	Engine();

	void run();
};