#include "Deck.h"


Deck::Deck() :
	m_rows(6),
	m_numberOfCards(24)
{
}

void Deck::initialize()
{
	const float spacing = Screen::screenWidth / 10.11f;
	float posX = Screen::screenWidth / 3.5f;
	float posY = Screen::screenHeight / 24.0f;
	const sf::Vector2f topLeftPosition(posX, posY);

	for (auto i = 0; i < m_numberOfCards; ++i)
	{
		m_cards[i]->setFrontSprite();
		m_cards[i]->setBackSprite();
		sf::Vector2f position(spacing * (i % m_rows), (spacing + (spacing / 3)) * (i / m_rows));
		m_cards[i]->setPosition(topLeftPosition.x + position.x, topLeftPosition.y + position.y);
	}
}

void Deck::addCards()
{
	// Fill the deck
	for (size_t i = 0; i < m_numberOfCards; ++i)
	{    
		m_cards.push_back(std::make_shared<Card>(m_backSprite, i / 2));
	}
}

void Deck::resetCards()
{
	// Shuffle and hide all cards before starting a new game
	for (auto& card : m_cards)
	{ 
		card->isShown(false);
	}
	this->shuffleCards();
	this->initialize();
}

void Deck::shuffleCards()
{
	// Returns and counts a time point representing the current point in time and shuffles the deck 
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(m_cards.begin(), m_cards.end(), std::default_random_engine(static_cast<unsigned>(seed)));
}

Card* Deck::clickCard(sf::Vector2f& mousePosition)
{
	// Check if a card is clicked
	std::vector<sPtr<Card>>::iterator it = std::find_if(m_cards.begin(), m_cards.end(), [&mousePosition](sPtr<Card>& card)
	{ return (card->setBackSprite().getGlobalBounds().contains((float)mousePosition.x, (float)mousePosition.y) && card->inactive()); });
	return it != m_cards.end() ? (*it).get() : nullptr;
}

bool Deck::pickCards(Card* card, Player& player, sf::Time& elapsedTime)
{   
	if (m_cardPick[0] == nullptr)
	{
		m_cardPick[0] = card;  
		m_cardPick[0]->isShown(true);
	}
	else if (m_cardPick[0] != nullptr && m_cardPick[1] == nullptr)
	{ 
		m_cardPick[1] = card;
		m_cardPick[1]->isShown(true);
		player.movesCounter++;
	}  
	else return false;
}

bool Deck::unmatched(sf::Time &elapsedTime)
{
	if (m_cardPick[0] != nullptr && m_cardPick[1] != nullptr)
	{
		if (m_cardPick[0]->getNumber() != m_cardPick[1]->getNumber())
		{
			m_cardPick[0]->isShown(false);
			m_cardPick[1]->isShown(false);
			SoundManager::getInstance()->playSound(Resource::Sounds, Filename::unmatchedSound);
		}  
	}
	return true;
}

bool Deck::matched(Player& player)
{ 
	if (m_cardPick[0] != nullptr && m_cardPick[1] != nullptr)
	{
		if (m_cardPick[0]->getNumber() == m_cardPick[1]->getNumber())
		{ 
			player.matchingCards++;
			m_cardPick[0]->isShown(true);
			m_cardPick[1]->isShown(true);  
			SoundManager::getInstance()->playSound(Resource::Sounds, Filename::matchedSound); 
		}  
	}
	return true;
}

void Deck::clearChoices()
{
	m_cardPick[0] = nullptr;
	m_cardPick[1] = nullptr;
}

void Deck::drawDeck()
{
	for (auto& card : m_cards)
	{
		card->draw();
	}
}

void Deck::update(sf::Time& elapsedTime) 
{ 
}

Deck::~Deck()
{
}