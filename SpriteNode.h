#pragma once
#include "stdafx.h"
#include "ResourceHolder.h"



class SpriteNode : public sf::Sprite
{
private:

	ResourceHolder<sf::Texture> Textures;

public:

	SpriteNode() {};

	~SpriteNode() {};

	SpriteNode(std::string texture, float positionX, float positionY, float scaleX, float scaleY)
	{
		Textures.load(Resource::Texture, texture);
		this->setTexture(*Textures.get(texture));
		this->setPosition(sf::Vector2f(Main::screenWidth / positionX, Main::screenHeight / positionY));
		this->setScale(sf::Vector2f(Main::screenWidth / scaleX, Main::screenHeight / scaleY));
	}

};

