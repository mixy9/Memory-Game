#include "Card.h" 



Card::Card()
{
}

Card::Card(sPtr<sf::Sprite>& cardSprite, size_t cardNumber) :
	m_sprite(cardSprite), m_number(cardNumber)
{ 
	m_frontCardTexture = "Graphics/Cards/" + std::to_string(cardNumber) + ".png";

	//m_backSprite = std::make_shared<SpriteNode>(Filename::backCard, NULL, NULL, Main::cardWidht, Main::cardHeight);
	//m_frontSprite = std::make_shared<SpriteNode>(m_frontCardTexture, NULL, NULL, Main::cardWidht, Main::cardHeight);

	m_sprite = std::make_shared<sf::Sprite>();
	m_texture.load(Resource::Texture, Filename::backCard);
	m_sprite->setScale(sf::Vector2f(Main::cardWidht, Main::cardHeight));
	
	m_sprite = std::make_shared<sf::Sprite>();
	m_texture.load(Resource::Texture, m_frontCardTexture);
	m_sprite->setScale(sf::Vector2f(Main::cardWidht, Main::cardHeight));
}

sf::Sprite&  Card::setSprite()
{
	if (m_showCard == true)
	{ 
		m_sprite->setTexture(*m_texture.get(m_frontCardTexture));
	}
	else 
	{
		m_sprite->setTexture(*m_texture.get(Filename::backCard));
	}
	return *m_sprite;
}

void Card::setPosition(float posX, float posY)
{
	m_sprite->setPosition(posX, posY);
}

void Card::animateCardFlip(sf::Time &elapsedTime, bool show)
{
	sf::Time currentTime = sf::Time::Zero;
	const sf::Time spinTime = sf::milliseconds(400);
	const sf::Time halfSpinTime = spinTime / 3.f;
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
	m_showCard = currentTime >= halfSpinTime;
	if (m_showCard) {
		float scale = (currentTime - halfSpinTime) / halfSpinTime;
		m_sprite->setScale(std::sin(scale * PI() / 2.f) * Main::cardWidht, Main::cardHeight);
		this->isShown(false);
	}
	else 
	{  
		float scale = 1.f - currentTime / halfSpinTime;
		m_sprite->setScale(std::sin(scale * PI() / 2.f) * Main::cardWidht, Main::cardHeight);
		this->isShown(true);
	}
}

bool Card::isShown(bool show)
{
	return m_showCard = show;
}

int Card::getNumber()
{
	return m_number;
}

void Card::draw()
{ 
	Main::window.draw(*m_sprite);
}

void Card::update(sf::Time &elapsedTime)
{
	this->animateCardFlip(elapsedTime, false);
}

Card::~Card()
{
}



