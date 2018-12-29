#include "Application.h"



Application::Application()
{
}

int Application::execute()
{
	while (Main::window.isOpen())
	{
		Main::window.clear();
		display();
		Main::window.display();
		processEvents();
		update();
	}
	return EXIT_SUCCESS;
}

bool Application::initialize()
{
	Main::window.setKeyRepeatEnabled(false);
	Main::window.setFramerateLimit(60);

	seconds = 0;

	pCard = nullptr;

	menu.initialize();

	deck.display();
	deck.shuffleCards();
	deck.initialize();

	player.initialize();
	//SoundManager::getInstance()->playMusic(Filename::musicFilename);

	return true;
}

void Application::update()
{
	menu.update();
	seconds = static_cast<unsigned>(delta.asSeconds());
	if (gameState == GameState::PLAYER_INPUT)
	{
		delta = clock.restart();
	}
	else if (gameState == GameState::PLAYING)
	{
		updatePlaying();
	}
	else if (gameState == GameState::END)
	{
		endGame();
	}
}

void Application::display()
{
	switch (gameState)
	{
	case GameState::INTRO:
		menu.draw();
		menu.drawIntro();
		break;
	case GameState::PLAYER_INPUT:
		menu.draw();
		player.draw();
		menu.drawInput();
		break;
	case GameState::PLAYING:
		menu.draw(); 
		deck.drawDeck();
		player.drawHud();
		break;
	case GameState::END:
		menu.draw();
		menu.drawEnd();
		player.drawResult();
		break;
	}
}

void Application::endGame()
{
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
}

void Application::updatePlaying()
{
	delta = clock.getElapsedTime();
	deck.update(mouseWorldPosition, pCard, delta, player);
	player.update(delta, seconds);
	if (pCard != nullptr)
	{
		pCard->update(delta);
	}
}

void Application::processEvents()
{
	while (Main::window.pollEvent(Event))
	{
		if ((Event.type == sf::Event::Closed) || (Event.type == sf::Event::KeyPressed)
			&& (Event.key.code == sf::Keyboard::Escape))
		{
			Main::window.close();
		}
		if ((Event.type == sf::Event::MouseButtonReleased))
		{
			pCard && gameState != GameState::END ? SoundManager::getInstance()->playSound(Resource::Sound, Filename::cardFlip)
				: SoundManager::getInstance()->playSound(Resource::Sound, Filename::clickSound);
		}
		if ((Event.type == sf::Event::MouseButtonPressed) && (Event.mouseButton.button == sf::Mouse::Left))
		{
			mouseScreenPosition = sf::Mouse::getPosition();
			mouseWorldPosition = Main::window.mapPixelToCoords(sf::Mouse::getPosition());
			menu.musicSwitch(); 
			if (gameState == GameState::INTRO)
			{
				if (menu.textClick())
				{
					if (menu.quitRect())
					{
						Main::window.close();
					}
					else 
					{
						gameState = GameState::PLAYER_INPUT;
					}
				}
			} 
			else if (gameState == GameState::PLAYER_INPUT)
			{
				if (menu.textClick())
				{
					gameState = GameState::PLAYING;
				}
			}
			else if (gameState == GameState::PLAYING)
			{
				pCard = deck.clickCard(mouseWorldPosition);
				if (pCard)
				{
					if (deck.pickCards(pCard, player, delta))
					{
						if (player.allMatching()) 
						{
							gameState = GameState::END;
						}
						deck.matched(player);
					}
					else if (deck.unmatched(delta)) 
					{
						deck.clearChoices();
						deck.pickCards(pCard, player, delta);
					}
				}
			}
			else if (gameState == GameState::END)
			{ 
				if (menu.textClick())
				{
					if (menu.quitRect())
					{
						Main::window.close();
					}
					else
					{
						gameState = GameState::PLAYER_INPUT;
						player.clearPlayerInput();
						player.resetScore();
						deck.clearChoices();
					}
				}
			}
		} // End of mouse type event
		if (Event.type == sf::Event::TextEntered)
		{
			if (gameState == GameState::PLAYER_INPUT)
			{
				player.playerInput(Event);
			}
		}
	} 
}

Application::~Application()
{
}
