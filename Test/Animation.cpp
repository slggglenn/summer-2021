
#include "Animation.h"
#include <iostream>

Animation::Animation() // ???? if derived class has path, how to get it to object of base class????
{
	//setTexture(imgPath); // initializes textBack_ and texture_ ... why not here??
	set_animSprites(&texture_); ///??
	updateIdleSprite(LEFT);
}

Sprite Animation::getSprite()
{
	return sprite_;
}

void Animation::setTexture(std::string imgPath)
{//imgRef_
	textBack_.loadFromFile("graphics/eevee.png");// !!! en.sfml-dev.org/forums/index.php?topic=12663.0
	textBack_.createMaskFromColor(Color(0, 128, 128), 0); // !!! NEED: program to get color pixels from the thing itself
	texture_.loadFromImage(textBack_);
}

Texture Animation::getTexture()
{
	return texture_;
}

// loads temporary sprites into animSprites
void Animation::set_animSprites(Texture* texture)
{
	Direction directions[8] = {DOWN, UP, LEFT, RIGHT, LEFT_DOWN, RIGHT_DOWN, LEFT_UP, RIGHT_UP};

	// determine how many IDLE, MOVING, SLEEP sprites how many for each direction XXX
	for (unsigned int i = 0; i < 2; i++) // repeats once for IDLE and once for MOVING
	{
		State currState;
		unsigned int currX, currY;
		if (!i) // boundary?? 
		{
			currState = IDLE; // IDLE on first run
			currX = IDLE_START_X;
			currY = IDLE_START_Y;
		} else {
			currState = MOVING; // MOVING on second
			currX = MOVE_START_X;
			currY = MOVE_START_Y;
		}

		// gets row for specific DIRECTION animation for current STATE
		for (unsigned int j = 0; j < 8; j++)
		{
			Sprite row;
			row.setTexture(*texture);
			row.setTextureRect(IntRect(currX, currY + (SPRITE_SIDE_LEN * j),
												 2 * SPRITE_SIDE_LEN, SPRITE_SIDE_LEN)); // SAME as below
			row.setScale(3, 3);
			animSprites_[make_pair(currState, directions[j])] = row;

		}
	}

	Sprite sleepChunk;
	sleepChunk.setTexture(*texture);
	sleepChunk.setTextureRect(IntRect(SLEEP_START_X,
					SLEEP_START_Y, 3 * SPRITE_SIDE_LEN, SPRITE_SIDE_LEN)); // CHHECK 2.5 if enough size and if width param!!
	sleepChunk.setScale(3, 3);
	animSprites_[make_pair(ASLEEP, NONE)] = sleepChunk;
}

// sets the current sprite given STATE and DIRECTION
void Animation::updateIdleSprite(Direction dir) // CURRENTLY JUST FOR IDLE
{
	//Sprite s;
	//s = animSprites_[make_pair(IDLE, dir)]; // pointer ok??????!!!!
	//s.setTextureRect(IntRect(s.getTextureRect().left, s.getTextureRect().top, s.getTextureRect().width / 2, s.getTextureRect().height));
	////    //cout << "top: " << s.getGlobalBounds().top << "left: " << s.getGlobalBounds().left << "height: " << s.getTextureRect().
	//return s;
	sprite_ = animSprites_[make_pair(IDLE, dir)]; // i'm not sure if below is working
	sprite_.setTextureRect(IntRect(sprite_.getTextureRect().left, sprite_.getTextureRect().top, sprite_.getTextureRect().width / 2, sprite_.getTextureRect().height));
}

// draws Animation based on keyword for animation type
//void Animation::playAnim(Direction dir, bool moving)
//{
//
//}

// error handling?