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
	cStr font1("Fonts/love.ttf");
	cStr font2("Fonts/Madpakke.ttf");

	// Textures:
	cStr menu("Graphics/menu.png");
	cStr paper("Graphics/paper.png");
	cStr sound("Graphics/sound.png");
	cStr noSound("Graphics/noSound.png");
	cStr backCard("Graphics/backCard.png");
	cStr background("Graphics/background.jpg");

	// Audio:
	cStr cardFlip("Audio/cardFlip.wav");
	cStr clickSound("Audio/mouseClick.wav");
	cStr matchedSound("Audio/matchedSound.wav");
	cStr musicFilename("Audio/music_acoustic.ogg");
	cStr unmatchedSound("Audio/unmatchedSound.wav");
}

