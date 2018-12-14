#include "Deck.h"



Deck::Deck() :
	mRows(6),
	mNumberOfCards(24)
{
}

void Deck::addCard(sPtr<sf::Sprite>& sprite, size_t number)
{
	cards.push_back(std::make_shared<Card>(sprite, number));
}

void Deck::initialize()
{
	const float spacing = 135.f;
	float posX = Main::screenWidth / 3.5f;
	float posY = Main::screenHeight / 24.0f;
	const sf::Vector2f topLeftPosition(posX, posY);

	for (auto i = 0; i < mNumberOfCards; ++i)
	{
		cards[i]->getSprite();
		sf::Vector2f position(spacing * (i % mRows), (spacing + (spacing / 3)) * (i / mRows));
		cards[i]->setPosition(topLeftPosition.x + position.x, topLeftPosition.y + position.y);
	}
}

void Deck::display()
{
	for (size_t i = 0; i < mNumberOfCards; ++i)
	{
		addCard(mSprite, i / 2);
	}
}

void Deck::resetCards()
{
	// Shuffle and hide all cards before starting a new game
	std::for_each(cards.begin(), cards.end(), [](sPtr<Card>& card)
	{
		return card->hide();
	});
	this->shuffleCards();
	this->initialize();
}

void Deck::shuffleCards()
{
	// Returns and counts a time point representing the current point in time
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(cards.begin(), cards.end(), std::default_random_engine(static_cast<unsigned>(seed)));
}

Card* Deck::clickCard(sf::Vector2f& mousePosition)
{
	// Find if a card is clicked
	std::vector<sPtr<Card>>::iterator it = std::find_if(cards.begin(), cards.end(), [=, &mousePosition](sPtr<Card>& card)
	{
		return (card->getSprite().getGlobalBounds().contains((float)mousePosition.x, (float)mousePosition.y));
	});
	return it != cards.end() ? (*it).get() : nullptr;
}

bool Deck::pickCards(Card* card, Player& player, sf::Time &elapsedTime)
{ 
	if (cardPick[0] == nullptr)
	{
		cardPick[0] = card;
		card->animateCardFlip(elapsedTime);
	}
	else if (cardPick[0] != nullptr && cardPick[1] == nullptr)
	{
		cardPick[1] = card;
		card->animateCardFlip(elapsedTime);
		player.movesCounter++; 
	} 
	else return false;
}

bool Deck::matched(Player& player)
{
	if (cardPick[0] != nullptr && cardPick[1] != nullptr)
	{
		if (cardPick[0]->getNumber() == cardPick[1]->getNumber())
		{
			cardPick[0]->show();
			cardPick[1]->show();
			player.matchingCards++; 
			SoundManager::getInstance()->playSound(Resource::Sound, Filename::matchCards);
		} 
	}
	return true;
}

bool Deck::unmatched()
{
	if (cardPick[0] != nullptr && cardPick[1] != nullptr)
	{
		if (cardPick[0]->getNumber() != cardPick[1]->getNumber()) {
			cardPick[0]->hide();
			cardPick[1]->hide();  
		}  
	}
	return true;
}

void Deck::drawDeck()
{
	for (auto& card : cards)
	{
		card->draw();
	}
}

void Deck::clearChoices()
{
	cardPick[0] = nullptr;
	cardPick[1] = nullptr;
}

void Deck::update(sf::Vector2f& mousePosition)
{
	clickCard(mousePosition);
}

Deck::~Deck()
{
}