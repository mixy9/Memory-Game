#pragma once
#include "stdafx.h"



class TextNode : public sf::Text
{

protected:
	sf::Font fonts;

public:
	TextNode();
	
	TextNode(std::string string, size_t size, float x, float y, sf::Color(color), std::string font);

	~TextNode();
};