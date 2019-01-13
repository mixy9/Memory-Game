#pragma once
#include "stdafx.h"
#include "Card.h"
#include "Deck.h"
#include "Menu.h"
#include "Player.h"



class Application
{
private:
	Menu menu;
	Deck deck;
	Card* pCard;
	Player player;

	sf::Time delta;
	sf::Clock clock;

	sf::Event Event;

	sf::Vector2f mouseWorldPosition;
	sf::Vector2i mouseScreenPosition;

	enum class GameState
	{
		INTRO,
		PLAYER_INPUT,
		PLAYING,
		END
	};
	GameState gameState = GameState::INTRO;

public:
	Application();

	int execute();

	bool initialize();

	void update();
	void display();
	void updateEnd();
	void updatePlaying();
	void processEvents();

	~Application();
};

