#pragma once

#include "TextNode.h"
#include "SceneNode.h"
#include "SoundManager.h"



class Menu : public SceneNode
{
private:
	ResourceHolder<sf::Texture> Textures;	
	std::vector<sPtr<TextNode>> Buttons;
	sPtr<TextNode> okay, quit, play, game, title, tryAgain, theEnd;
	sPtr<sf::Sprite> backgroundSprite, menuSprite, soundSprite, noSoundSprite;

	sf::Vector2f mouseWorldPosition;
	sf::Vector2i mouseScreenPosition;

	bool m_isMusicOn;
	bool m_isMouseOver;

public:	
	Menu();	

	virtual void initialize();

	bool quitRect();
	bool textClick();
	bool mouseHover(sPtr<TextNode> text);

	void musicSwitch();
	void header(sf::RenderWindow& window);
	void drawEnd(sf::RenderWindow& window);
	void drawInput(sf::RenderWindow& window);
	void drawIntro(sf::RenderWindow& window);

	virtual void update(sf::Time &elapsedTime);
	virtual void draw(sf::RenderWindow& window);

	~Menu();
};

