#include "Menu.h"


Menu::Menu() :
	m_isMusicOn(true),
	m_isMouseOver(false)
{
}

void Menu::initialize()
{ 
	menuSprite = std::make_shared<SpriteNode>(Filename::menu, 2.9f, 1.9f, 3902.85f, 2194.28f);
	soundSprite = std::make_shared<SpriteNode>(Filename::sound, 1.09f, 19.f, 1366.f, 768.f);
	noSoundSprite = std::make_shared<SpriteNode>(Filename::noSound, 1.09f, 19.f, 1366.f, 768.f);
	backgroundSprite = std::make_shared<SpriteNode>(Filename::background, Screen::screenWidth, Screen::screenHeight, NULL, NULL);
	backgroundSprite->setScale(Screen::screenWidth / backgroundSprite->getLocalBounds().width, Screen::screenHeight / backgroundSprite->getLocalBounds().height);
	
	okay = std::make_shared<TextNode>(OK_BUTTON, 12u, 2.4f, 1.5f, sf::Color::White, Filename::font2);
	end = std::make_shared<TextNode>(END_TEXT, 20u, 3.9f, 3.2f, sf::Color::White, Filename::font2);
	quit = std::make_shared<TextNode>(QUIT_BUTTON, 18u, 2.3f, 1.36f, sf::Color::White, Filename::font2);
	play = std::make_shared<TextNode>(PLAY_BUTTON, 18u, 2.3f, 1.77f, sf::Color::White, Filename::font2);
	game = std::make_shared<TextNode>(GAME_TEXT, 9u, 2.7f, 3.f, sf::Color(96, 69, 35), Filename::font2);
	repeat = std::make_shared<TextNode>(REPEAT_BUTTON, 18u, 2.6f, 1.6f, sf::Color::White, Filename::font2);
	title = std::make_shared<TextNode>(TITLE_TEXT, 6u, 4.7f, 9.4f, sf::Color(219, 139, 41), Filename::font1);

	title->setOutlineThickness(7.5f);
	title->setOutlineColor(sf::Color::White);

	m_menuButtons.push_back(quit);
	m_menuButtons.push_back(play);
	m_menuButtons.push_back(okay);
	m_menuButtons.push_back(repeat);
}

bool Menu::quitRect()
{
	sf::FloatRect button = quit->getGlobalBounds();
	return mouseHover(quit);
}

bool Menu::textClick()
{
	// Check if a text button is clicked
	std::vector<sPtr<TextNode>>::iterator it = std::find_if(m_menuButtons.begin(), m_menuButtons.end(), [=](sPtr<TextNode>& text) -> bool
	{ return (text->getGlobalBounds().contains(m_mouseWorldPosition.x, m_mouseWorldPosition.y) && mouseHover(text)); });	
	return it != m_menuButtons.end() ? (*it).get() : nullptr;
}

bool Menu::isMusicOn(bool button)
{
	return m_isMusicOn = button;
}

bool Menu::mouseHover(sPtr<TextNode> text)
{
	if (text->getGlobalBounds().contains(m_mouseWorldPosition.x, m_mouseWorldPosition.y))
	{
		text->setFillColor(sf::Color(255, 186, 83));
		m_isMouseOver = true;
	}
	else {
		text->setFillColor(sf::Color::White);
		m_isMouseOver = false;
	}
	return m_isMouseOver;
}

void Menu::header()
{
	title->setCharacterSize(Screen::screenWidth / 12u);
	title->setPosition(Screen::screenWidth / 2.7f, Screen::screenHeight / 28.f);
	game->setCharacterSize(Screen::screenWidth / 15u);
	game->setPosition(Screen::screenWidth / 2.3f, Screen::screenHeight / 7.4f);
	Screen::window.draw(*title);
	Screen::window.draw(*game);
}

void Menu::drawEnd()
{
	header();
	Screen::window.draw(*repeat);
	Screen::window.draw(*quit);
	Screen::window.draw(*end);
}

void Menu::drawInput()
{
	header();
	Screen::window.draw(*okay);
}

void Menu::drawIntro()
{
	Screen::window.draw(*menuSprite);
	Screen::window.draw(*title);
	Screen::window.draw(*game);
	Screen::window.draw(*play);
	Screen::window.draw(*quit);
}

void Menu::musicSwitch()
{
	sf::FloatRect on = soundSprite->getGlobalBounds();
	sf::FloatRect off = noSoundSprite->getGlobalBounds();

	if (m_isMusicOn && (on.contains(m_mouseWorldPosition.x, m_mouseWorldPosition.y)))
	{
		SoundManager::getInstance()->pauseMusic();
		isMusicOn(false);
	}
	else if (!m_isMusicOn && (off.contains(m_mouseWorldPosition.x, m_mouseWorldPosition.y))) {
		SoundManager::getInstance()->playMusic(Filename::musicFilename);
		isMusicOn(true);
	}
}

void Menu::draw()
{
	Screen::window.draw(*backgroundSprite);
	m_isMusicOn ? Screen::window.draw(*soundSprite) : Screen::window.draw(*noSoundSprite);
	m_mouseWorldPosition = Screen::window.mapPixelToCoords(m_mouseScreenPosition);
}

void Menu::update(sf::Time& elapsedTime)
{
	m_mouseScreenPosition = sf::Mouse::getPosition();
	for (auto& text : m_menuButtons)
	{
		mouseHover(text);
	}
}

Menu::~Menu()
{
}