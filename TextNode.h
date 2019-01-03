#pragma once

#include "stdafx.h"
#include "ResourceHolder.h"


class TextNode : public sf::Text
{
private:
	ResourceHolder<sf::Font> m_fonts;

public:

	TextNode() {};

	~TextNode() {};
	
	TextNode(std::string string, size_t size, float positionX, float positionY, sf::Color(color), std::string font)
	{
		m_fonts.load(Resource::Font, font);
		this->setString(string);
		this->setCharacterSize(Main::screenWidth / size);
		this->setFont(*m_fonts.get(font));
		this->setFillColor(sf::Color(color));
		this->setPosition(sf::Vector2f(Main::screenWidth / positionX, Main::screenHeight / positionY));
	}
};