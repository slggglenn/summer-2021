
#include "Animation.h"

// constructor
Animation::Animation(std::string img_ref)
{
	setTexture(img_ref);
	//setSprite();
}

// sets the texture
void Animation::setTexture(std::string img_ref)
{
	textBack_.loadFromFile("graphics/eevee.png");// !!! en.sfml-dev.org/forums/index.php?topic=12663.0
	textBack_.createMaskFromColor(Color(0, 128, 128), 0); // !!! NEED: program to get color pixels from the thing itself
	texture_.loadFromImage(textBack_);
}

// gets the texture
Texture Animation::getTexture()
{
	return texture_;
}

// gets the sprite
Sprite Animation::getSprite()
{
	return sprite_;
}

// gets sprite global bounds
FloatRect Animation::getSpriteBounds()
{
	return sprite_.getGlobalBounds();
}

Sprite* Animation::setspritesArray()
{
	for (unsigned int i = 0; i < NUM_IDLE; i++)
	{
		spritesArray[i].setTextureRect(IntRect (IDLE_START_X,
										 IDLE_START_Y + (SPRITE_SIDE_LEN * i),
										 SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
		spritesArray[i].setScale(3, 3);
	}

	for (unsigned int j = 0; j < NUM_WALK; j++)
	{
		spritesArray[j].setTextureRect(IntRect (MOVE_START_X,
			MOVE_START_Y + (SPRITE_SIDE_LEN * j),
			SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
		spritesArray[j].setScale(3, 3);
	}

	for (unsigned int k = 0; k < NUM_SLEEP; k++)
	{
		spritesArray[k].setTextureRect(IntRect (SLEEP_START_X,
			SLEEP_START_Y + (SPRITE_SIDE_LEN * k),
			SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
		spritesArray[k].setScale(3, 3);
	}
}

// gets range of indeces for animation
unsigned int* Animation::getAnimIndeces(Direction dir, bool moving)
{

}

// draws Animation based on keyword for animation type
void Animation::playAnim(Direction dir, bool moving)
{

}

