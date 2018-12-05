#include "Player.h"



Player::Player() :
	movesCounter(0),
    matchingCards(0)
{		
}

void Player::initialize()
{	
	mTextUnderline.setPosition(sf::Vector2f(screenWidth / 2.5f, screenHeight / 1.6f));
	mTextUnderline.setSize(sf::Vector2f(400.f, 2.5f));
	mTextUnderline.setFillColor(sf::Color::White);

	name = std::make_shared<TextNode>("Player: ", 80u, 4.1f, 2.f, sf::Color::White, Filename::font2);
	playerName = std::make_shared<TextNode>("", 80u, NULL, NULL, sf::Color(121, 77, 36), Filename::font2);
	result = std::make_shared<TextNode>("", 50u, 3.7f, 2.3f, sf::Color::White, Filename::font2);
	hud = std::make_shared<TextNode>("", 35u, 25.f, 5.f, sf::Color::White, Filename::font2);
	star = std::make_shared<TextNode>("", 120u, 2.5f, 2.f, sf::Color(255, 173, 51), Filename::font2);

	star->setOutlineThickness(2.f);
	star->setOutlineColor(sf::Color::White);
}

int Player::allMatching()
{
	return matchingCards == 12;
}

void Player::rating()
{
	std::stringstream rating;
	if (movesCounter <= 30) {
		rating << "* * *";
	}
	else if (movesCounter > 30 && movesCounter <= 40) {
		rating << "* *";
	}
	else if (movesCounter > 40) {
		rating << "*";
	}
	star->setString(rating.str());
}

void Player::resetScore()
{
	minutes = 0; movesCounter = 0; matchingCards = 0;
}

void Player::clearPlayerInput()
{
	// Clear the inputted text and enter a new name
	mInputtedText.clear();
}

void Player::playerInput(sf::Event& Event)
{
	// Handle ASCII characters only
	char uCode = Event.text.unicode;
	if (uCode >= 48 && uCode <= 122 && mInputtedText.getSize() < 9) // Maximum 9 characters
	{
		mInputtedText += uCode;
	}
	// Delete characters using the backspace key
	else if (uCode == 8 && mInputtedText.getSize() > 0) {
		mInputtedText.erase(mInputtedText.getSize() - 1, mInputtedText.getSize());
	}
}

void Player::drawHud(sf::RenderWindow& window)
{
	playerName->setCharacterSize(50u);
	playerName->setPosition(sf::Vector2f(screenWidth / 25, screenHeight / 9.5));
	window.draw(*playerName);
	window.draw(*hud);
}

void Player::drawResult(sf::RenderWindow& window)
{
	playerName->setCharacterSize(80u);
	playerName->setPosition(sf::Vector2f(screenWidth / 1.7f, screenHeight / 3.4f));
	window.draw(*playerName);
	window.draw(*result);
	window.draw(*star);
}

void Player::draw(sf::RenderWindow& window)
{
	playerName->setPosition(sf::Vector2f(screenWidth / 2.4f, screenHeight / 2.f));
	playerName->setString(mInputtedText);
	window.draw(mTextUnderline);
	window.draw(*playerName);
	window.draw(*name);
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
	HUDstream << "Time: " << minutes << "m" << seconds << "s Moves: " << movesCounter << "\nMatching cards: " << matchingCards << "/12";
	hud->setString(HUDstream.str());
	// Update results
	resultsStream << "->  Your time: " << minutes << "m" << seconds << "s\tMoves: " << movesCounter << "  <-";
	result->setString(resultsStream.str());
}

Player::~Player()
{
}
