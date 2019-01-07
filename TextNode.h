#pragma once

#include "stdafx.h"
#include "ResourceHolder.h"


class TextNode : public sf::Text
{
private:
	ResourceHolder<sf::Font> m_font;

public:

	TextNode() {};

	~TextNode() {};
	
	TextNode(std::string string, size_t size, float positionX, float positionY, sf::Color(color), std::string font)
	{
		m_font.load(Resource::Font, font);
		this->setString(string);
		this->setFont(*m_font.get(font));
		this->setFillColor(sf::Color(color));
		this->setCharacterSize(Main::screenWidth / size);
		this->setPosition(sf::Vector2f(Main::screenWidth / positionX, Main::screenHeight / positionY));
	}
};