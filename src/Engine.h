#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

using namespace sf;

class Engine
{
private:
	//The Texture Holder
	TextureHolder textureHolder;

public:
	//The Engine constructor
	Engine();

	void run();
};