#pragma once

#include "ResourceHolder.h"
#include "SpriteNode.h"
#include "SceneNode.h"



class Card : public SceneNode
{
protected:
	bool m_showCard;
	size_t m_number;
	sf::Clock m_clock;
	std::string m_frontCardTexture;
	ResourceHolder<sf::Texture> m_texture;
	sPtr<SpriteNode> m_frontSprite, m_backSprite; 

public: 
	Card();	
	Card(sPtr<SpriteNode>& cardSprite, size_t cardNumber);

	sf::Sprite& setBackSprite();
	sf::Sprite& setFrontSprite();
	
	void setPosition(float posX, float posY);

	int getNumber();
	bool inactive();
	bool isShown(bool show);

	virtual void draw();
	virtual void initialize() {};
	virtual void update(sf::Time& elapsedTime) {};

	~Card();
};

