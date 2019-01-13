#pragma once

#include "TextNode.h"
#include "GameObject.h"
#include "SpriteNode.h"
#include "SoundManager.h"



class Menu : public GameObject
{
private:
	std::vector<sPtr<TextNode>> m_menuButtons;
	sPtr<TextNode> okay, quit, play, game, title, repeat, end;
	sPtr<SpriteNode> menuSprite, backgroundSprite, introBG, soundSprite, noSoundSprite;

	sf::Vector2f m_mouseWorldPosition;
	sf::Vector2i m_mouseScreenPosition;

	bool m_isMusicOn;
	bool m_isMouseOver;

public:	
	Menu();	

	bool quitRect();
	bool textClick();
	bool isMusicOn(bool button);
	bool mouseHover(sPtr<TextNode> text);

	void header();
	void drawEnd();
	void drawInput();
	void drawIntro();
	void musicSwitch();

	virtual void draw();
	virtual void initialize();
	virtual void update(sf::Time& elapsedTime);

	~Menu();
};

