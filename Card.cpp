#include "Card.h"


Card::Card() 
{
}

Card::Card(sPtr<sf::Sprite>& cardSprite, size_t cardNumber) :
	mSprite(cardSprite), mNumber(cardNumber)
{
	frontCardTexture = "Graphics/Cards/" + std::to_string(cardNumber) + ".png";
	
	mSprite = std::make_shared<sf::Sprite>();
	mSprite->setScale(sf::Vector2f(screenWidth / 2101.53f, screenHeight / 1129.41f));
}

sf::Sprite& Card::getSprite()
{
	if (mShowCard == true)
	{
		Texture.load(Resource::frontCard, frontCardTexture);
		mSprite->setTexture(*Texture.get(frontCardTexture));
	}
	else {
		Texture.load(Resource::backCard, Filename::backCard);
		mSprite->setTexture(*Texture.get(Filename::backCard));
	}
	return *mSprite;
}

void Card::setPosition(float posX, float posY)
{
	mSprite->setPosition(posX, posY);
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

void Card::draw(sf::RenderWindow& window)
{
	window.draw(*mSprite);
}

Card::~Card()
{
}



