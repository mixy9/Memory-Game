#pragma once

#include "TextNode.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "SoundManager.h"



class Menu : public SceneNode
{
private:
	std::vector<sPtr<TextNode>> m_menuButtons;
	sPtr<TextNode> okay, quit, play, game, title, repeat, theEnd;
	sPtr<SpriteNode> menuSprite, backgroundSprite, introBG, soundSprite, noSoundSprite;

	sf::Vector2f m_mouseWorldPosition;
	sf::Vector2i m_mouseScreenPosition;

	bool m_isMusicOn;
	bool m_isMouseOver;

public:	
	Menu();	

	virtual void initialize();

	bool quitRect();
	bool textClick();
	bool mouseHover(sPtr<TextNode> text);

	void header();
	void drawEnd();
	void drawInput();
	void drawIntro();
	void musicSwitch();

	virtual void draw();
	virtual void update();

	~Menu();
};

