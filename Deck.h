#pragma once

#include "Card.h"
#include "Player.h"
#include "SoundManager.h"


class Deck : public Card
{
private:
	unsigned int mRows, mNumberOfCards;
	std::vector<sPtr<Card>> cards;
	Card* arr[2];
	
public:

	Deck();
	
	void addCard(sPtr<sf::Sprite>& sprite, size_t number);
	virtual void initialize();
	void display();
	void resetCards();
	void shuffleCards();

	Card* clickCard(sf::Vector2f& mousePosition);

	bool pickCards(Card* card, Player& player);
	bool chechMatching(Player& player);

	void clearChoices();
	void drawDeck(sf::RenderWindow& window);
	virtual void update(sf::Vector2f& mousePosition);	

	~Deck();
};

