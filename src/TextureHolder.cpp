#include "TextureHolder.h"
#include <assert.h>

/*
Essentially, this class will maintain a map of texture so we don't have to keep referencing their files
every time we want to use them. If the texture we ask for doesn't already exist in the map, it will be added to
the map and loaded. The next time we ask for it, it will simply access the map and obtain the Texture object directly
as opposed to loading it from a file. This is because as we have more and more objects, loading textures from files
becomes unwieldly.

Credit for this technique and code to John Horton - LinkedIn C++ Game Programming series
*/

//Sets the value of the pointer m_s_Instance to nullptr.
TextureHolder* TextureHolder::m_s_Instance = nullptr;
TextureHolder::TextureHolder()
{
	//Checks that the instance is correctly null before proceeding.
	assert(m_s_Instance == nullptr);
	//Points the pointer to this instance, the only instance.
	m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{
	//Get a reference to m_Textures using m_s_Instance
	auto& m = m_s_Instance->m_Textures;
	//auto is the equivalent of typing map<string, Texture> here

	//Create an iterator to hold a key-value pair and search for the required kvp using the passed in file name
	auto keyValuePair = m.find(filename);
	//auto is the equivalent of typing map<string, Texture>::iterator here.

	//Did we find a match?
	if (keyValuePair != m.end())
	{
		//Yes, return the texture, the value of the kvp.
		return keyValuePair->second;
	}
	else
	{
		//No, file name not found. Create a new key value pair using the filename.
		auto& texture = m[filename];
		texture.loadFromFile(filename);

		//Return the texture to the calling code
		return texture;
	}
}
