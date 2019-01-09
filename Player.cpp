#include "Player.h"



Player::Player() :
	seconds(0),
	movesCounter(0),
    matchingCards(0)
{		
}

void Player::initialize()
{
	m_paper = std::make_unique<SpriteNode>(Filename::paper, 50.f, 16.f, 1290.f, 853.f);

	m_textUnderline.setPosition(sf::Vector2f(Screen::screenWidth / 2.5f, Screen::screenHeight / 1.6f));
	m_textUnderline.setSize(sf::Vector2f(Screen::screenWidth / 3.4f, Screen::screenHeight / 307.f));
	m_textUnderline.setFillColor(sf::Color::White);

	name = std::make_shared<TextNode>(PLAYER_TEXT, 17u, 4.1f, 2.f, sf::Color::White, Filename::font2);
	result = std::make_shared<TextNode>(TEXT_INPUT, 27u, 3.7f, 2.3f, sf::Color::White, Filename::font2);
	hud = std::make_shared<TextNode>(TEXT_INPUT, 40u, 21.f, 4.5f, sf::Color(121, 77, 36), Filename::font2);
	star = std::make_shared<TextNode>(TEXT_INPUT, 11u, 2.5f, 2.f, sf::Color(255, 173, 51), Filename::font2);
	playerName = std::make_shared<TextNode>(TEXT_INPUT, 17u, NULL, NULL, sf::Color(121, 77, 36), Filename::font2);

	star->setOutlineThickness(2.f);
	star->setOutlineColor(sf::Color::White);
}

void Player::playerInput(sf::Event& Event)
{
	// Handle ASCII characters only
	char uCode = Event.text.unicode;
	if (uCode >= 48 && uCode <= 122 && m_inputtedText.getSize() < 9) // Maximum 9 characters
	{
		m_inputtedText += uCode;
	}
	// Delete characters using the backspace key
	else if (uCode == 8 && m_inputtedText.getSize() > 0) 
	{
		m_inputtedText.erase(m_inputtedText.getSize() - 1, m_inputtedText.getSize());
	}
}

void Player::clearPlayerInput()
{
	// Clear the inputted text and enter a new name
	m_inputtedText.clear();
}

void Player::rating()
{
	std::stringstream rating;
	if (movesCounter <= 20) 
	{
		rating << "* * *";
	}
	else if (movesCounter > 20 && movesCounter <= 30) 
	{
		rating << "* *";
	}
	else if (movesCounter > 30) 
	{
		rating << "*";
	}
	star->setString(rating.str());
}

void Player::drawHud()
{
	playerName->setCharacterSize(Screen::screenWidth / 27u);
	playerName->setPosition(sf::Vector2f(Screen::screenWidth / 18.f, Screen::screenHeight / 7.5f));
	Screen::window.draw(*m_paper);
	Screen::window.draw(*playerName);
	Screen::window.draw(*hud);
}

void Player::drawResult()
{
	playerName->setCharacterSize(Screen::screenWidth / 17u);
	playerName->setPosition(sf::Vector2f(Screen::screenWidth / 1.7f, Screen::screenHeight / 3.4f));
	Screen::window.draw(*playerName);
	Screen::window.draw(*result);
	Screen::window.draw(*star);
}

void Player::resetScore()
{
	minutes = movesCounter = matchingCards = 0;
}

bool Player::allMatching()
{
	return matchingCards == 12;
}

void Player::draw()
{
	playerName->setPosition(sf::Vector2f(Screen::screenWidth / 2.4f, Screen::screenHeight / 2.f));
	playerName->setString(m_inputtedText);
	Screen::window.draw(m_textUnderline);
	Screen::window.draw(*playerName);
	Screen::window.draw(*name);
}

void Player::update(sf::Time& elapsedTime)
{
	// Time setting loop
	seconds = static_cast<unsigned>(elapsedTime.asSeconds());
	minutes = 0;
	while (seconds > 59) 
	{
		minutes++;
		seconds -= 60;
	}
	std::stringstream HUDstream, resultsStream;
	// Update the 'Head-Up Display' text	
	HUDstream << "Time: " << minutes << "min" << seconds << "s Moves: " << movesCounter << "\nMatching cards: " << matchingCards << "/12";
	hud->setString(HUDstream.str());
	// Update results
	resultsStream << "->  Your time: " << minutes << "min" << seconds << "s\tMoves: " << movesCounter << "  <-";
	result->setString(resultsStream.str());
}

Player::~Player()
{
}
