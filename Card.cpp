#include "Card.h" 


Card::Card()
{
}

Card::Card(sPtr<sf::Sprite>& cardSprite, size_t cardNumber) :
	m_sprite(cardSprite), m_number(cardNumber)
{
	// Each instance of the object requires a unique id
	m_currentId = ++m_ID; 
	m_sprite = std::make_shared<sf::Sprite>();
	m_sprite->setScale(sf::Vector2f(Main::cardWidht, Main::cardHeight));
	m_frontCardTexture = "Graphics/Cards/" + std::to_string(cardNumber) + ".png";
}

bool Card::getID()
{
	if (m_showCard == true)
	return m_ID++;
}

sf::Sprite&  Card::setSprite()
{
	if (m_showCard == true)
	{
		m_texture.load(Resource::Texture, m_frontCardTexture);
		m_sprite->setTexture(*m_texture.get(m_frontCardTexture));
	}
	else 
	{
		m_texture.load(Resource::Texture, Filename::backCard);
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
	const sf::Time halfSpinTime = spinTime / 4.f;
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
		this->isShown(show);
	}
	else 
	{
		float scale = 1.f - currentTime / halfSpinTime;
		m_sprite->setScale(std::sin(scale * PI() / 2.f) * Main::cardWidht, Main::cardHeight);
		this->isShown(!show);
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



