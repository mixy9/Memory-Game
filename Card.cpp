#include "Card.h" 


Card::Card()
{
}

Card::Card(sPtr<SpriteNode>& cardSprite, size_t cardNumber) :
	m_backSprite(cardSprite),
	m_number(cardNumber),
	m_showCard(false)
{
	m_frontCardTexture = "Graphics/Cards/" + std::to_string(cardNumber) + ".png";
	m_backSprite = std::make_shared<SpriteNode>(Filename::backCard, NULL, NULL, 2101.53f, 1129.41f);
	m_frontSprite = std::make_shared<SpriteNode>(m_frontCardTexture, NULL, NULL, 2101.53f, 1129.41f);	
}

sf::Sprite& Card::setBackSprite()
{ 
	return *m_backSprite;
}

sf::Sprite& Card::setFrontSprite()
{
	return *m_frontSprite;
}

void Card::setPosition(float posX, float posY)
{
	m_backSprite->setPosition(posX, posY);
	m_frontSprite->setPosition(posX, posY);
}

void Card::animateCardFlip(sf::Time& elapsedTime)
{
	sf::Time delta = m_clock.restart();
	const sf::Time spinTime = sf::milliseconds(500);
	const sf::Time halfSpinTime = spinTime / 2.f;
	sf::Time currentTime = sf::Time::Zero;
	m_backSprite->setScale(Screen::cardWidht, Screen::cardHeight); 
	if (m_showCard == false)
	{
		if (currentTime < spinTime - delta)
			currentTime += delta;
		else
		{
			currentTime = spinTime; 
		}
	} 
	m_showCard = currentTime >= halfSpinTime;
	if (m_showCard)
	{ 
		float scale = (currentTime - halfSpinTime) / halfSpinTime;
		float angle = std::sin(scale * PI() / 2.f);
		m_backSprite->setScale(angle * (Screen::cardWidht / 2), Screen::cardHeight);
		m_backSprite->move(angle * 20.f, 0.f);
		this->isShown(false);
	}
	else
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		float scale = 1.f - currentTime / halfSpinTime;
		float angle = std::sin(scale * PI() / 2.f);
		m_frontSprite->setScale(angle * Screen::cardWidht, Screen::cardHeight);
		m_backSprite->move(angle * -20.f, 0.f);
		this->isShown(true);
	}
}
 
int Card::getNumber()
{
	return m_number;
}

bool Card::inactive()
{
	if (m_showCard == true)
		return false;
}

bool Card::isShown(bool show)
{ 
	return m_showCard = show;
}

void Card::draw()
{ 
	if (m_showCard == true)
	{
		Screen::window.draw(*m_frontSprite);
	}
	else 
	{ 
		Screen::window.draw(*m_backSprite);
	}
}

Card::~Card()
{
}



