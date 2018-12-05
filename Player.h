#pragma once

#include "stdafx.h"
#include "ResourceHolder.h"
#include "TextNode.h"
#include "SceneNode.h"



class Player :  public SceneNode
{
protected:	
	sf::String mInputtedText;
	sf::RectangleShape mTextUnderline;
	unsigned int minutes, movesCounter, matchingCards;
	std::shared_ptr<TextNode> name, playerName, hud, result, star;
	
public:
	Player();

	friend class Deck;
	virtual void initialize();

	int allMatching();

	void rating();   
	void resetScore();
	void clearPlayerInput();
	void playerInput(sf::Event& Event);
	void drawHud(sf::RenderWindow& window);	
	void drawResult(sf::RenderWindow& window);

	virtual void draw(sf::RenderWindow& window);
	virtual void update(sf::Time& elapsedTime, unsigned int seconds);
	
	~Player();
};

