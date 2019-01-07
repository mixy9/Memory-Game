#include "Card.h" 


Card::Card()
{
}

Card::Card(sPtr<sf::Sprite>& cardSprite, size_t cardNumber) :
	m_backSprite(cardSprite), m_number(cardNumber), m_showCard(false)
{  
	m_backSprite = std::make_shared<sf::Sprite>();
	m_backSprite->setScale(sf::Vector2f(Main::cardWidht, Main::cardHeight));
	m_frontCardTexture = "Graphics/Cards/" + std::to_string(cardNumber) + ".png";
}

int Card::getNumber()
{
	return m_number;
}
 
bool Card::getID()
{	
	// Each instance of the object requires a unique id
	if (m_showCard == true)
	return m_ID++;
}

sf::Sprite& Card::setFrontSprite()
{
	m_frontSprite = std::make_shared<sf::Sprite>();
	m_frontSprite->setScale(sf::Vector2f(Main::cardWidht, Main::cardHeight));
	m_texture.load(Resource::Texture, m_frontCardTexture);
	m_frontSprite->setTexture(*m_texture.get(m_frontCardTexture));
	return *m_frontSprite;
}

sf::Sprite& Card::setBackSprite()
{
	m_texture.load(Resource::Texture, Filename::backCard);
	m_backSprite->setTexture(*m_texture.get(Filename::backCard));
	return *m_backSprite;
}

void Card::setPosition(float posX, float posY)
{
	m_backSprite->setPosition(posX, posY);
	m_frontSprite->setPosition(posX, posY);
}

void Card::animateCardFlip(sf::Time &elapsedTime, bool show)
{
	sf::Time currentTime = sf::Time::Zero;
	const sf::Time spinTime = sf::milliseconds(500);
	const sf::Time halfSpinTime = spinTime / 2.f;
	sf::Time delta = m_clock.restart();  

	if (m_showCard == show)
	{
		if (currentTime < spinTime - delta)
			currentTime += delta;
		else
		{
			currentTime = spinTime; 
		}
	}  
	if (currentTime > spinTime / 2.f)
	{
		float scale = (currentTime - halfSpinTime) / halfSpinTime;
		m_backSprite->setScale(std::sin(scale * PI() / 2.f) * Main::cardWidht, Main::cardHeight);
		this->isShown(show);
	}
	else 
	{ 
		float scale = 1.f - currentTime / halfSpinTime;
		m_frontSprite->setScale(std::sin(scale * PI() / 2.f) * Main::cardWidht, Main::cardHeight);
		this->isShown(!show);
	}
}

bool Card::isShown(bool show)
{ 
	return m_showCard = show;
}

void Card::draw()
{ 
	if (m_showCard == true)
	{
		Main::window.draw(*m_frontSprite);
	}
	else 
	{
		Main::window.draw(*m_backSprite);
	}
}

Card::~Card()
{
}



