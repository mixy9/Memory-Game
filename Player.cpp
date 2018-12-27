#include "Player.h"



Player::Player() :
	movesCounter(0),
    matchingCards(0)
{		
}

void Player::initialize()
{	
	m_textUnderline.setPosition(sf::Vector2f(Main::screenWidth / 2.5f, Main::screenHeight / 1.6f));
	m_textUnderline.setSize(sf::Vector2f(Main::screenWidth / 3.4f, Main::screenHeight / 307.f));
	m_textUnderline.setFillColor(sf::Color::White);

	m_paper = std::make_unique<SpriteNode>(Filename::paper, 50.f, 16.f, 1290.f, 853.f);

	name = std::make_shared<TextNode>(PLAYER_TEXT, 17u, 4.1f, 2.f, sf::Color::White, Filename::font2);
	playerName = std::make_shared<TextNode>("", 17u, NULL, NULL, sf::Color(121, 77, 36), Filename::font2);
	result = std::make_shared<TextNode>("", 27u, 3.7f, 2.3f, sf::Color::White, Filename::font2);
	hud = std::make_shared<TextNode>("", 40u, 19.f, 4.5f, sf::Color(121, 77, 36), Filename::font2);
	star = std::make_shared<TextNode>("", 11u, 2.5f, 2.f, sf::Color(255, 173, 51), Filename::font2);

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
	else if (uCode == 8 && m_inputtedText.getSize() > 0) {
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
	if (movesCounter <= 20) {
		rating << "* * *";
	}
	else if (movesCounter > 20 && movesCounter <= 30) {
		rating << "* *";
	}
	else if (movesCounter > 30) {
		rating << "*";
	}
	star->setString(rating.str());
}

void Player::drawHud()
{
	playerName->setCharacterSize(Main::screenWidth / 27u);
	playerName->setPosition(sf::Vector2f(Main::screenWidth / 18.f, Main::screenHeight / 7.5f));
	Main::window.draw(*m_paper);
	Main::window.draw(*playerName);
	Main::window.draw(*hud);
}

void Player::drawResult()
{
	playerName->setCharacterSize(Main::screenWidth / 17u);
	playerName->setPosition(sf::Vector2f(Main::screenWidth / 1.7f, Main::screenHeight / 3.4f));
	Main::window.draw(*playerName);
	Main::window.draw(*result);
	Main::window.draw(*star);
}

void Player::resetScore()
{
	minutes = 0; 
	movesCounter = 0; 
	matchingCards = 0;
}

int Player::allMatching()
{
	return matchingCards == 12;
}

void Player::draw()
{
	playerName->setPosition(sf::Vector2f(Main::screenWidth / 2.4f, Main::screenHeight / 2.f));
	playerName->setString(m_inputtedText);
	Main::window.draw(m_textUnderline);
	Main::window.draw(*playerName);
	Main::window.draw(*name);
}

void Player::update(sf::Time& elapsedTime, unsigned int seconds)
{
	// Time setting loop
	minutes = 0;
	while (seconds > 60) {
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
