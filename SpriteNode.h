#pragma once

#include "stdafx.h"
#include "ResourceHolder.h"



class SpriteNode : public sf::Sprite
{
private:
	ResourceHolder<sf::Texture> m_texture;

public:

	SpriteNode() {};

	~SpriteNode() {};

	SpriteNode(std::string texture, float positionX, float positionY, float scaleX, float scaleY)
	{
		m_texture.load(Resource::Texture, texture);
		this->setTexture(*m_texture.get(texture));
		this->setPosition(sf::Vector2f(Main::screenWidth / positionX, Main::screenHeight / positionY));
		this->setScale(sf::Vector2f(Main::screenWidth / scaleX, Main::screenHeight / scaleY));
	}
};

