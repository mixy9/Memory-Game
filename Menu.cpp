#include "Menu.h"


Menu::Menu() :
	m_isMusicOn(true),
	m_isMouseOver(false)	
{
}

void Menu::initialize()
{
	Textures.load(Resource::Menu, Filename::menu);
	Textures.load(Resource::Sound, Filename::sound);
	Textures.load(Resource::Sound, Filename::noSound);
	Textures.load(Resource::Background, Filename::background);

	backgroundSprite = std::make_shared<sf::Sprite>();
	backgroundSprite->setTexture(*Textures.get(Filename::background));
	backgroundSprite->setScale(screenWidth / backgroundSprite->getLocalBounds().width, 
		                       screenHeight / backgroundSprite->getLocalBounds().height);

	soundSprite = std::make_shared<sf::Sprite>();
	noSoundSprite = std::make_shared<sf::Sprite>();
	soundSprite->setTexture(*Textures.get(Filename::sound));
	noSoundSprite->setTexture(*Textures.get(Filename::noSound));
	soundSprite->setPosition(screenWidth / 1.09f, screenHeight / 19.f);
	noSoundSprite->setPosition(screenWidth / 1.09f, screenHeight / 19.f);

	menuSprite = std::make_shared<sf::Sprite>();
	menuSprite->setTexture(*Textures.get(Filename::menu));
	menuSprite->setScale(sf::Vector2f(0.35f, 0.35f));
    menuSprite->setPosition(screenWidth / 2.9f, screenHeight / 1.9f);

	okay = std::make_shared<TextNode>("OK", 110u, 2.4f, 1.5f, sf::Color::White, Filename::font2);
	quit = std::make_shared<TextNode>("Quit", 75u, 2.3f, 1.36f, sf::Color::White, Filename::font2);
	play = std::make_shared<TextNode>("Play", 75u, 2.3f, 1.77f, sf::Color::White, Filename::font2);
	game = std::make_shared<TextNode>("GAME", 160u, 2.7f, 3.1f, sf::Color(96, 69, 35), Filename::font2);
	tryAgain = std::make_shared<TextNode>("Try again", 75u, 2.6f, 1.6f, sf::Color::White, Filename::font2);
	title = std::make_shared<TextNode>("Memory", 220u, 4.7f, 8.6f, sf::Color(219, 139, 41), Filename::font1);
	theEnd = std::make_shared<TextNode>("CONGRATULATIONS", 70u, 3.9f, 3.2f, sf::Color::White, Filename::font2);

	title->setOutlineThickness(7.5f);
	title->setOutlineColor(sf::Color::White);

	Buttons.push_back(quit);
	Buttons.push_back(play);
	Buttons.push_back(okay);
	Buttons.push_back(tryAgain);
}

bool Menu::quitRect()
{
	sf::FloatRect button = quit->getGlobalBounds();
	return mouseHover(quit);
}

bool Menu::textClick()
{
	// Check if text is clicked
	std::vector<sPtr<TextNode>>::iterator it = std::find_if(Buttons.begin(), Buttons.end(), [=](sPtr<TextNode>& text) -> bool
	{ return (text->getGlobalBounds().contains((float)mouseWorldPosition.x, (float)mouseWorldPosition.y) && mouseHover(text)); });
	
	return it != Buttons.end() ? (*it).get() : nullptr;
}

bool Menu::mouseHover(sPtr<TextNode> text)
{
	if (text->getGlobalBounds().contains((float)mouseWorldPosition.x, (float)mouseWorldPosition.y))
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

void Menu::musicSwitch()
{
	sf::FloatRect on = soundSprite->getGlobalBounds();
	sf::FloatRect off = noSoundSprite->getGlobalBounds();
	
	if (m_isMusicOn && (on.contains(mouseWorldPosition.x, mouseWorldPosition.y))) 
	{
		SoundManager::getInstance()->pauseMusic();
		m_isMusicOn = false; }
	else if (!m_isMusicOn && (off.contains(mouseWorldPosition.x, mouseWorldPosition.y))) {
		SoundManager::getInstance()->playMusic(Filename::musicFilename);
	    m_isMusicOn = true; }
}

void Menu::header(sf::RenderWindow& window)
{
	title->setCharacterSize(110u);
	title->setPosition(screenWidth / 2.7f, screenHeight / 28.f);
	game->setCharacterSize(90u);
	game->setPosition(screenWidth / 2.3f, screenHeight / 7.4f);
	window.draw(*title);
	window.draw(*game);
}

void Menu::drawEnd(sf::RenderWindow& window)
{
	header(window);
	window.draw(*tryAgain);
	window.draw(*theEnd);
	window.draw(*quit);
}

void Menu::drawInput(sf::RenderWindow& window)
{
	m_isMusicOn;
	header(window);
	window.draw(*okay);
}

void Menu::drawIntro(sf::RenderWindow& window)
{
	window.draw(*menuSprite);
	window.draw(*title);
	window.draw(*game);
	window.draw(*play);
	window.draw(*quit);
}

void Menu::update(sf::Time &elapsedTime)
{
	mouseScreenPosition = sf::Mouse::getPosition();
	for (auto& text : Buttons)
	{
		mouseHover(text);
	}
}

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(*backgroundSprite);
	m_isMusicOn ? window.draw(*soundSprite) : window.draw(*noSoundSprite);
	mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition);
}

Menu::~Menu()
{
}