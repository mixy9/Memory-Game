#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <random>
#include <chrono>
#include <vector>
#include <memory>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <exception>
#include <functional>
#include <unordered_map>


template <typename T>
using sPtr = std::shared_ptr<T>;


static unsigned int screenWidth = sf::VideoMode::getDesktopMode().width;
static unsigned int screenHeight = sf::VideoMode::getDesktopMode().height;


namespace Filename
{
	// Fonts:
	const std::string font1("Fonts/love.ttf");
	const std::string font2("Fonts/Madpakke.ttf");

	// Audio:
	const std::string clickSound("Audio/click.wav");
	const std::string cardFlip("Audio/cardFlip.wav");
	const std::string musicFilename("Audio/music_ranch.ogg");

	// Textures:
	const std::string menu("Graphics/menu.png");
	const std::string sound("Graphics/sound.png");
	const std::string noSound("Graphics/nsnd.png");
	const std::string backCard("Graphics/backCard.png");
	const std::string background("Graphics/background.jpg");
}


