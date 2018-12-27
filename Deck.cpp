#include "Deck.h"



Deck::Deck() :
	m_rows(6),
	m_numberOfCards(24)
{
}

void Deck::addCard(sPtr<sf::Sprite>& sprite, size_t number)
{
	m_cards.push_back(std::make_shared<Card>(sprite, number));
}

void Deck::initialize()
{ 
	const float spacing = Main::screenWidth / 10.11f;
	float posX = Main::screenWidth / 3.5f;
	float posY = Main::screenHeight / 24.0f;
	const sf::Vector2f topLeftPosition(posX, posY);

	for (auto i = 0; i < m_numberOfCards; ++i)
	{ 
		m_cards[i]->setSprite();
		sf::Vector2f position(spacing * (i % m_rows), (spacing + (spacing / 3)) * (i / m_rows));
		m_cards[i]->setPosition(topLeftPosition.x + position.x, topLeftPosition.y + position.y);
	}
}

void Deck::display()
{
	for (size_t i = 0; i < m_numberOfCards; ++i)
	{
		addCard(m_sprite, i / 2);
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
	// Returns and counts a time point representing the current point in time
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(m_cards.begin(), m_cards.end(), std::default_random_engine(static_cast<unsigned>(seed)));
}

Card* Deck::clickCard(sf::Vector2f& mousePosition)
{
	// Find if a card is clicked
	std::vector<sPtr<Card>>::iterator it = std::find_if(m_cards.begin(), m_cards.end(), [&mousePosition](sPtr<Card>& card)
	{ return (card->setSprite().getGlobalBounds().contains((float)mousePosition.x, (float)mousePosition.y)); });
	return it != m_cards.end() ? (*it).get() : nullptr;
}

bool Deck::pickCards(Card* card, Player& player, sf::Time &elapsedTime)
{ 
	if (m_cardPick[0] == nullptr)
	{
		m_cardPick[0] = card; 
		m_cardPick[0]->animateCardFlip(elapsedTime, false);
	}
	else if (m_cardPick[0] != nullptr && m_cardPick[1] == nullptr)
	{
		m_cardPick[1] = card; 
		m_cardPick[1]->animateCardFlip(elapsedTime, false);
		player.movesCounter++; 
	} 
	else return false;
}

bool Deck::matched(Player& player)
{
	if (m_cardPick[0] != nullptr && m_cardPick[1] != nullptr)
	{
		if (m_cardPick[0]->getNumber() == m_cardPick[1]->getNumber())
		{
			m_cardPick[0]->isShown(true);
			m_cardPick[1]->isShown(true);
			player.matchingCards++; 
			SoundManager::getInstance()->playSound(Resource::Sound, Filename::matchCards);
		} 
		return true;
	}
	else return false;
}

bool Deck::unmatched(sf::Time& elapsedTime)
{
	if (m_cardPick[0] != nullptr && m_cardPick[1] != nullptr)
	{
		if (m_cardPick[0]->getNumber() != m_cardPick[1]->getNumber()) {
			m_cardPick[0]->isShown(false);
			m_cardPick[1]->isShown(false); 
		}  
		return true;
	}
	else return false;
}

void Deck::drawDeck()
{
	for (auto& card : m_cards)
	{
		card->draw();
	}
}

void Deck::clearChoices()
{
	m_cardPick[0] = nullptr;
	m_cardPick[1] = nullptr;
}

void Deck::update(sf::Vector2f& mousePosition, sf::Time& elapsedTime, Player& player)
{	
	clickCard(mousePosition);
}

Deck::~Deck()
{
}