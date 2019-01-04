#pragma once
#include "Card.h"
#include "Player.h"
#include "SoundManager.h"


class Deck : public Card
{
private:
	unsigned int m_rows, m_numberOfCards;
	std::vector<sPtr<Card>> m_cards;
	Card* m_cardPick[2]; 

public:

	Deck();

	void display();
	void resetCards();
	void shuffleCards();

	Card* clickCard(sf::Vector2f& mousePosition);

	bool pickCards(Card* card, Player& player, sf::Time &elapsedTime);
	bool matched(Player& player);
	bool unmatched(sf::Time &elapsedTime);

	void drawDeck();
	void clearChoices();
	bool countMoves(Player& player);
	virtual void initialize();
	virtual void update(sf::Time& elapsedTime);

	~Deck();
};

