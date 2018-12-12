#pragma once

#include "TextNode.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "SoundManager.h"



class Menu : public SceneNode
{
private:
	ResourceHolder<sf::Texture> Textures;	
	std::vector<sPtr<TextNode>> menuButtons;
	sPtr<TextNode> okay, quit, play, game, title, repeat, theEnd;
	sPtr<SpriteNode> menuSprite, backgroundSprite, introBG, soundSprite, noSoundSprite;

	sf::Vector2f mouseWorldPosition;
	sf::Vector2i mouseScreenPosition;

	bool mIsMusicOn;
	bool mIsMouseOver;

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

