#pragma once

#include "ResourceHolder.h"
#include "SpriteNode.h"
#include "SceneNode.h"



class Card : public SceneNode
{
protected:
	size_t m_number;
	sf::Clock m_clock;
	bool m_active, m_showCard;
	std::string m_frontCardTexture;
	ResourceHolder<sf::Texture> m_texture;
	sPtr<SpriteNode> m_frontSprite, m_backSprite;
public: 
	Card();	
	Card(sPtr<SpriteNode>& cardSprite, size_t cardNumber);

	sf::Sprite& setBackSprite();
	sf::Sprite& setFrontSprite();
	
	void setPosition(float posX, float posY);
	void animateCardFlip(sf::Time& elapsedTime, bool show);

	int getNumber();

	bool isActive();
	bool isShown(bool show);

	virtual void draw();
	virtual void initialize() {};
	virtual void update(sf::Time& elapsedTime) {};

	~Card();
};

