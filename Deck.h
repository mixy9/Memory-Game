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

	void addCards();
	void resetCards();
	void shuffleCards();

	Card* clickCard(sf::Vector2f& mousePosition);

	bool pickCards(Card* card, Player& player, sf::Time& elapsedTime);
	bool checkMatching(sf::Time& elapsedTime, Player& player);

	void clearChoices();

	virtual void draw();
	virtual void initialize();
	virtual void update(sf::Time& elapsedTime);

	~Deck();
};

