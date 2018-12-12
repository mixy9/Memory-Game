#pragma once

#include "stdafx.h"
#include "ResourceHolder.h"
#include "TextNode.h"
#include "SceneNode.h"
#include "SpriteNode.h"




class Player :  public SceneNode
{
protected:
	sf::String mInputtedText;
	sf::RectangleShape mTextUnderline;
	unsigned int minutes, movesCounter, matchingCards;
	sPtr<TextNode> name, playerName, hud, result, star;
	
public:
	Player();

	friend class Deck;

	virtual void initialize();

	void playerInput(sf::Event& Event);
	void clearPlayerInput();
	void rating();
	void drawHud();	
	void drawResult();
	void resetScore();

	int allMatching();

	virtual void draw();
	virtual void update(sf::Time& elapsedTime, unsigned int seconds);
	
	~Player();
};

