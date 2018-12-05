#include "TextNode.h"


TextNode::TextNode()
{
}


TextNode::TextNode(std::string string, size_t size, float x, float y, sf::Color(color), std::string font)
{
	assert(fonts.loadFromFile(font));
	this->setFont(fonts);
	this->setString(string);
	this->setCharacterSize(size);	
	this->setFillColor(sf::Color(color));
	this->setPosition(sf::Vector2f(screenWidth / x, screenHeight / y));
}


TextNode::~TextNode()
{
}