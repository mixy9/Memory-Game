#include "Menu.h"


Menu::Menu() :
	mIsMusicOn(true),
	mIsMouseOver(false)	
{
}

void Menu::initialize()
{
	menuSprite = std::make_shared<SpriteNode>(Filename::menu, 2.9f, 1.9f, 3902.85f, 2194.28f);
	soundSprite = std::make_shared<SpriteNode>(Filename::sound, 1.09f, 19.f, 1366.f, 768.f);
	noSoundSprite = std::make_shared<SpriteNode>(Filename::noSound, 1.09f, 19.f, 1366.f, 768.f);
	backgroundSprite = std::make_shared<SpriteNode>(Filename::background, Main::screenWidth, Main::screenHeight, NULL, NULL);
	backgroundSprite->setScale(Main::screenWidth / backgroundSprite->getLocalBounds().width, Main::screenHeight / backgroundSprite->getLocalBounds().height); 

	okay = std::make_shared<TextNode>("OK", 12u, 2.4f, 1.5f, sf::Color::White, Filename::font2);
	quit = std::make_shared<TextNode>("Quit", 18u, 2.3f, 1.36f, sf::Color::White, Filename::font2);
	play = std::make_shared<TextNode>("Play", 18u, 2.3f, 1.77f, sf::Color::White, Filename::font2);
	game = std::make_shared<TextNode>("GAME", 9u, 2.7f, 3.f, sf::Color(96, 69, 35), Filename::font2);
	repeat = std::make_shared<TextNode>("Try again", 18u, 2.6f, 1.6f, sf::Color::White, Filename::font2);
	title = std::make_shared<TextNode>("Memory", 6u, 4.7f, 8.6f, sf::Color(219, 139, 41), Filename::font1);
	theEnd = std::make_shared<TextNode>("CONGRATULATIONS", 20u, 3.9f, 3.2f, sf::Color::White, Filename::font2);

	title->setOutlineThickness(7.5f);
	title->setOutlineColor(sf::Color::White);

	menuButtons.push_back(quit);
	menuButtons.push_back(play);
	menuButtons.push_back(okay);
	menuButtons.push_back(repeat);
}

bool Menu::quitRect()
{
	sf::FloatRect button = quit->getGlobalBounds();
	return mouseHover(quit);
}

bool Menu::textClick()
{
	// Check if text is clicked
	std::vector<sPtr<TextNode>>::iterator it = std::find_if(menuButtons.begin(), menuButtons.end(), [=](sPtr<TextNode>& text) -> bool
	{ return (text->getGlobalBounds().contains((float)mouseWorldPosition.x, (float)mouseWorldPosition.y) && mouseHover(text)); });
	
	return it != menuButtons.end() ? (*it).get() : nullptr;
}

bool Menu::mouseHover(sPtr<TextNode> text)
{
	if (text->getGlobalBounds().contains(mouseWorldPosition.x, mouseWorldPosition.y))
	{
		text->setFillColor(sf::Color(255, 186, 83));
		mIsMouseOver = true;
	}
	else {
		text->setFillColor(sf::Color::White);
		mIsMouseOver = false;
	}
	return mIsMouseOver;
}

void Menu::header()
{
	title->setCharacterSize(Main::screenWidth / 12u);
	title->setPosition(Main::screenWidth / 2.7f, Main::screenHeight / 28.f);
	game->setCharacterSize(Main::screenWidth / 15u);
	game->setPosition(Main::screenWidth / 2.3f, Main::screenHeight / 7.4f);
	Main::window.draw(*title);
	Main::window.draw(*game);
}

void Menu::drawEnd()
{
	header();
	Main::window.draw(*repeat);
	Main::window.draw(*theEnd);
	Main::window.draw(*quit);
}

void Menu::drawInput()
{
	header();
	mIsMusicOn = true;
	Main::window.draw(*okay);
}

void Menu::drawIntro()
{
	Main::window.draw(*menuSprite);
	Main::window.draw(*title);
	Main::window.draw(*game);
	Main::window.draw(*play);
	Main::window.draw(*quit);
}

void Menu::musicSwitch()
{
	sf::FloatRect on = soundSprite->getGlobalBounds();
	sf::FloatRect off = noSoundSprite->getGlobalBounds();

	if (mIsMusicOn && (on.contains(mouseWorldPosition.x, mouseWorldPosition.y)))
	{
		SoundManager::getInstance()->pauseMusic();
		mIsMusicOn = false;
	}
	else if (!mIsMusicOn && (off.contains(mouseWorldPosition.x, mouseWorldPosition.y))) {
		SoundManager::getInstance()->playMusic(Filename::musicFilename);
		mIsMusicOn = true;
	}
}

void Menu::draw()
{
	Main::window.draw(*backgroundSprite);
	mIsMusicOn ? Main::window.draw(*soundSprite) : Main::window.draw(*noSoundSprite);
	mouseWorldPosition = Main::window.mapPixelToCoords(mouseScreenPosition);
}

void Menu::update()
{
	mouseScreenPosition = sf::Mouse::getPosition();
	for (auto& text : menuButtons)
	{
		mouseHover(text);
	}
}

Menu::~Menu()
{
}