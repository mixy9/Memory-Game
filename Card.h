#pragma once

#include "ResourceHolder.h"
#include "SceneNode.h"


class Card : public SceneNode
{
protected:
	ResourceHolder<sf::Texture> Texture;
	std::string frontCardTexture;
	sPtr<sf::Sprite> mSprite;
	bool mShowCard{ false };
	size_t mNumber;

public:
	Card();	
	Card(sPtr<sf::Sprite>& cardSprite, size_t cardNumber);
	
	sf::Sprite& getSprite();
	void setPosition(float posX, float posY);

	bool show();
	bool hide();
	int getNumber();
	
	virtual void update() {};
	virtual void initialize() {};
	virtual void draw(sf::RenderWindow& window);

	~Card();
};

