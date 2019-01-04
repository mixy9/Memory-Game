#pragma once

#include "stdafx.h"
#include "TextNode.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "ResourceHolder.h"



class Player :  public SceneNode
{
protected:
	sPtr<SpriteNode> m_paper;
	sf::String m_inputtedText;
	sf::RectangleShape m_textUnderline;

	sPtr<TextNode> name, hud, result, star, playerName;
	unsigned int seconds, minutes, movesCounter, matchingCards;
	
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

	bool allMatching();

	virtual void draw();
	virtual void update(sf::Time& elapsedTime);
	
	~Player();
};

