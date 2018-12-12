#include "Card.h"


Card::Card()
{
}

Card::Card(sPtr<sf::Sprite>& cardSprite, size_t cardNumber) :
	mSprite(cardSprite), mNumber(cardNumber)
{
	mSprite = std::make_shared<sf::Sprite>();
	mSprite->setScale(sf::Vector2f(Main::cardWidht, Main::cardHeight));
	frontCardTexture = "Graphics/Cards/" + std::to_string(cardNumber) + ".png";
}

sf::Sprite& Card::getSprite()
{
	if (mShowCard == true)
	{
		Texture.load(Resource::Texture, frontCardTexture); 
		mSprite->setTexture(*Texture.get(frontCardTexture));
	}
	else {
		Texture.load(Resource::Texture, Filename::backCard);
		mSprite->setTexture(*Texture.get(Filename::backCard));
	}
	return *mSprite;
}

void Card::setPosition(float posX, float posY)
{
	mSprite->setPosition(posX, posY);
}

void Card::animateCardFlip(sf::Time &elapsedTime)
{
	sf::Time currentTime = sf::Time::Zero;
	const sf::Time spinTime = sf::milliseconds(400);
	const sf::Time halfSpinTime = spinTime / 3.f;
	sf::Time delta = clock.restart();
	if (mShowCard == false)
	{
		if (currentTime < spinTime - delta)
			currentTime += delta;
		else {
			currentTime = spinTime;
		}
	}
	mShowCard = currentTime >= halfSpinTime;
	if (mShowCard) {
		float scale = (currentTime - halfSpinTime) / halfSpinTime;
		mSprite->setScale(std::sin(scale * PI() / 2) * Main::cardWidht, Main::cardHeight);
		this->hide();
	}
	else {  
		float scale = 1.f - currentTime / halfSpinTime;
		mSprite->setScale(std::sin(scale * PI() / 2) * Main::cardWidht, Main::cardHeight);
		this->show();
	}
}

bool Card::show()
{
	return mShowCard = true;
}

bool Card::hide()
{
	return mShowCard = false;
}

int Card::getNumber()
{
	return mNumber;
}

void Card::draw()
{
	Main::window.draw(*mSprite);
}

void Card::update(sf::Time &elapsedTime)
{
	this->animateCardFlip(elapsedTime);
}

Card::~Card()
{
}



