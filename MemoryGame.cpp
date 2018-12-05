#include "stdafx.h"
#include "Menu.h"
#include "Deck.h"
#include "Player.h"
#include "SoundManager.h"




int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Memory Game", sf::Style::Fullscreen);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);	

	unsigned int seconds = 0;

	Menu menu;	
	menu.initialize();
	
	Card* card = nullptr;
	Deck deck;
	deck.display();
	deck.shuffleCards();
	deck.initialize();

	Player player;
	player.initialize();
	
	sf::Time delta;
	sf::Clock clock;	
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

	SoundManager::getInstance()->playMusic(Filename::musicFilename);

	while (window.isOpen())
	{
		window.clear();
		
		/********** DRAW **********/
		switch (gameState)
		{
		case GameState::INTRO:
			menu.draw(window);
			menu.drawIntro(window);
			break;
		case GameState::PLAYER_INPUT:
			menu.draw(window);
			player.draw(window);
			menu.drawInput(window);
			break;
		case GameState::PLAYING:
			menu.draw(window);
			deck.drawDeck(window);
			player.drawHud(window);
			break;
		case GameState::END:
			menu.draw(window);
			menu.drawEnd(window);
			player.drawResult(window);
			break;
		}

		window.display();

		sf::Event Event;
		while (window.pollEvent(Event))
		{
			if ((Event.type == sf::Event::Closed) || (Event.type == sf::Event::KeyPressed)
				&& (Event.key.code == sf::Keyboard::Escape))
			{
				window.close();
			}
			if ((Event.type == sf::Event::MouseButtonReleased))
			{
				card && gameState != GameState::END ? SoundManager::getInstance()->createSound(Resource::cardFlip, Filename::cardFlip)
					: SoundManager::getInstance()->createSound(Resource::Click, Filename::clickSound);
			}
			if ((Event.type == sf::Event::MouseButtonPressed) && (Event.mouseButton.button == sf::Mouse::Left))
			{
				mouseScreenPosition = sf::Mouse::getPosition();
				mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition());
				menu.musicSwitch();

				switch (gameState)
				{
				case GameState::INTRO:
					if (menu.textClick())
					{
						if (menu.quitRect())
						{
							window.close();
						}
						else {
							gameState = GameState::PLAYER_INPUT;
						}
					}
					break;
				case GameState::PLAYER_INPUT:			
					if (menu.textClick())
					{ 
						gameState = GameState::PLAYING;
					}
					break;
				case GameState::PLAYING:
					if (card = deck.clickCard(mouseWorldPosition))
					{
						if (deck.pickCards(card, player))
						{
							if (player.allMatching()) {
								sf::sleep(sf::milliseconds(200));
								gameState = GameState::END;
							}
						}
						else if (deck.chechMatching(player)) {
							deck.clearChoices();
							deck.pickCards(card, player);
						}
					}
					break;
				case GameState::END:
					if (menu.textClick()) 
					{
						if (menu.quitRect())
						{ 
							window.close(); 
						}
						else {
							gameState = GameState::PLAYER_INPUT;
							player.clearPlayerInput();
							player.resetScore(); 
						}
					}
					break;
				}
			} // End of mouse type event

			if (Event.type == sf::Event::TextEntered)
			{
				if (gameState == GameState::PLAYER_INPUT)
				{ 
					player.playerInput(Event);
				}
			}	
		} // End of Event

		/********** UPDATE **********/
		menu.update(delta);
		seconds = static_cast<unsigned>(delta.asSeconds());

		switch (gameState)
		{
		case GameState::PLAYER_INPUT:
			delta = clock.restart();
			break;
		case GameState::PLAYING:
			delta = clock.getElapsedTime();
			deck.update(mouseWorldPosition);
			player.update(delta, seconds);	
			break;
		case GameState::END:
			SoundManager::getInstance()->stopMusic();
			player.rating();
			player.update(delta, seconds); 
			deck.resetCards();
			clock.restart();
			if (menu.textClick()) 
			{
				// Play music when the game is repeated
				SoundManager::getInstance()->playMusic(Filename::musicFilename);
			}
			break;
		}
		if (gameState != GameState::PLAYING) 
			continue;

	} // End of while loop

	return 0;
}



