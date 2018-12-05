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
	float posX = screenWidth / 3.5f;
	float posY = screenHeight / 24.0f;
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
	shuffle(cards.begin(), cards.end(), std::default_random_engine(static_cast<unsigned>(seed)));
}

Card* Deck::clickCard(sf::Vector2f& mousePosition)
{
	// Find if a card is clicked
	std::vector<sPtr<Card>>::iterator it = std::find_if(cards.begin(), cards.end(), [=, &mousePosition] (sPtr<Card>& card)
	{ 
		return (card->getSprite().getGlobalBounds().contains((float)mousePosition.x, (float)mousePosition.y)); 
	});		
	return it != cards.end() ? (*it).get() : nullptr;
}

bool Deck::pickCards(Card* card, Player& player)
{
	if (arr[0] == nullptr)
	{
		arr[0] = card;
		card->show();
	} 
	else if (arr[0] != nullptr && arr[1] == nullptr)
	{
		arr[1] = card;
		card->show();
		player.movesCounter++;
	}
	else return false;
}

bool Deck::chechMatching(Player& player)
{
	if (arr[0] != nullptr && arr[1] != nullptr)
	{
		if (arr[0]->getNumber() == arr[1]->getNumber())
		{
			arr[0]->show();
			arr[1]->show();
			player.matchingCards++;
		}
		else if (arr[0]->getNumber() != arr[1]->getNumber()) {
			arr[0]->hide();
			arr[1]->hide();
		}
	}	
	return true;
}

void Deck::clearChoices()
{
	arr[0] = nullptr;
	arr[1] = nullptr;
}

void Deck::drawDeck(sf::RenderWindow& window)
{
	for (auto& card : cards)
	{
		card->draw(window);
	}
}

void Deck::update(sf::Vector2f& mousePosition)
{
	clickCard(mousePosition);
}

Deck::~Deck()
{
}