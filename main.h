#pragma once
#include "stdafx.h"
#include "Menu.h"
#include "Deck.h"
#include "Player.h"
#include "SoundManager.h"



namespace Main
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Memory Game", sf::Style::Fullscreen);

	unsigned int screenWidth = sf::VideoMode::getDesktopMode().width;
	unsigned int screenHeight = sf::VideoMode::getDesktopMode().height;

	float cardWidht = screenWidth / 2101.53f;
	float cardHeight = screenHeight / 1129.41f;
}


namespace Filename
{
	// Fonts:
	const std::string font1("Fonts/love.ttf");
	const std::string font2("Fonts/Madpakke.ttf");

	// Textures:
	const std::string menu("Graphics/menu.png");
	const std::string sound("Graphics/sound.png");
	const std::string noSound("Graphics/nsnd.png");
	const std::string introBG("Graphics/introBG.jpg");
	const std::string backCard("Graphics/backCard.png");
	const std::string background("Graphics/background.jpg");

	// Audio:
	const std::string cardFlip("Audio/cardFlip.wav");
	const std::string matchCards("Audio/matchSound.wav");
	const std::string clickSound("Audio/mouseClick.wav");
	const std::string musicFilename("Audio/musicRanch.ogg");
}

