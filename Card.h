#pragma once

#include "ResourceHolder.h"
#include "SceneNode.h"



class Card : public SceneNode
{
protected:
	ResourceHolder<sf::Texture> m_texture;
	std::string m_frontCardTexture;
	sPtr<sf::Sprite> m_sprite;
	sf::Clock m_clock;
	size_t m_number;

	int m_currentId;
	bool m_showCard;
	static int m_ID;

public: 
	Card();	
	Card(sPtr<sf::Sprite>& cardSprite, size_t cardNumber);

	sf::Sprite& setSprite(); 
	
	void setPosition(float posX, float posY);
	void animateCardFlip(sf::Time &elapsedTime, bool show);

	int getNumber();

	bool getID();
	bool isShown(bool show);

	virtual void draw();
	virtual void initialize() {};
	virtual void update(sf::Time &elapsedTime);

	~Card();
};

