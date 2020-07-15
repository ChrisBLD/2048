#pragma once
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder
{
private:
	//A map container from the STL that holds related pairs of string and texture
	std::map<std::string, Texture> m_Textures;

	//A pointer of the same type as the class itself, the one and only instance.
	static TextureHolder* m_s_Instance;

public:
	TextureHolder();
	//Returns a reference to a texture. Function can be used without an instance of the class.
	static Texture& GetTexture(std::string const& filename);
};