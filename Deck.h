#pragma once

#include "Card.h"
#include "Player.h"
#include "SoundManager.h"


class Deck : public Card
{
private:
	unsigned int mRows, mNumberOfCards;
	std::vector<sPtr<Card>> cards;
	Card* cardPick[2]; 

public:

	Deck();

	void addCard(sPtr<sf::Sprite>& sprite, size_t number);
	void display();
	void resetCards();
	void shuffleCards();

	Card* clickCard(sf::Vector2f& mousePosition);

	bool pickCards(Card* card, Player& player, sf::Time &elapsedTime);
	bool matched(Player& player);
	bool unmatched();

	void drawDeck();
	void clearChoices();

	virtual void initialize();
	virtual void update(sf::Vector2f& mousePosition);

	~Deck();
};

