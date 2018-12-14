#include "Player.h"



Player::Player() :
	movesCounter(0),
    matchingCards(0)
{		
}

void Player::initialize()
{	
	mTextUnderline.setPosition(sf::Vector2f(Main::screenWidth / 2.5f, Main::screenHeight / 1.6f));
	mTextUnderline.setSize(sf::Vector2f(400.f, 2.5f));
	mTextUnderline.setFillColor(sf::Color::White);

	paper = std::make_unique<SpriteNode>(Filename::paper, 38.f, 16.f, 1366.f, 853.f);

	name = std::make_shared<TextNode>("Player: ", 17u, 4.1f, 2.f, sf::Color::White, Filename::font2);
	playerName = std::make_shared<TextNode>("", 17u, NULL, NULL, sf::Color(121, 77, 36), Filename::font2);
	result = std::make_shared<TextNode>("", 27u, 3.7f, 2.3f, sf::Color::White, Filename::font2);
	hud = std::make_shared<TextNode>("", 40u, 18.f, 4.5f, sf::Color(121, 77, 36), Filename::font2);
	star = std::make_shared<TextNode>("", 11u, 2.5f, 2.f, sf::Color(255, 173, 51), Filename::font2);

	star->setOutlineThickness(2.f);
	star->setOutlineColor(sf::Color::White);
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

void Player::clearPlayerInput()
{
	// Clear the inputted text and enter a new name
	mInputtedText.clear();
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
	Main::window.draw(*paper);
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
	playerName->setString(mInputtedText);
	Main::window.draw(mTextUnderline);
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
