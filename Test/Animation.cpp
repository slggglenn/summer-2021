
#include "Animation.h"
#include <map>
using namespace std;


// constructor
Animation::Animation() //update!!
{
	setTexture();
	//setSprite();
}

// sets the texture
void Animation::setTexture()
{//imgRef_
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
//Sprite Animation::getSprite()
//{
//	return spritesheet_;
//}

// gets sprite global bounds
//FloatRect Animation::getSpriteBounds()
//{
//	return spritesheet_.getGlobalBounds();
//}


Vector2f Animation::getDirection()
{
	return direction_;
}


// loads temporary sprites into animSprites
void Animation::set_animSprites()
{
	State states[2] = {IDLE, ASLEEP};
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
			row.setTexture(texture_);
			row.setTextureRect(IntRect(currX, currY + (SPRITE_SIDE_LEN * j),
												 2 * SPRITE_SIDE_LEN, SPRITE_SIDE_LEN)); // SAME as below
			row.setScale(3, 3);
			animSprites_[make_pair(currState, directions[j])] = row;

		}
	}

	Sprite sleepChunk;
	sleepChunk.setTexture(texture_);
	sleepChunk.setTextureRect(IntRect(SLEEP_START_X,
					SLEEP_START_Y, 2.5 * SPRITE_SIDE_LEN, SPRITE_SIDE_LEN)); // CHHECK 2.5 if enough size and if width param!!
	sleepChunk.setScale(3, 3);
	animSprites_[make_pair(ASLEEP, NONE)] = sleepChunk;
}

Vector2f Animation::updateDirection()
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		setOrientation(LEFT);
		direction_.x = -1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		setOrientation(RIGHT);
		direction_.x = 1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		setOrientation(UP);
		direction_.y = -1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		setOrientation(DOWN);
		direction_.y = 1;
	}
	return direction_;
}

Vector2f Animation::zeroDirection()
{
	direction_.x = 0;
	direction_.y = 0;
	return direction_;
}

Direction Animation::getOrientation()
{
	return orientation_;
}

void Animation::setOrientation(Direction new_orient)
{
	orientation_ = new_orient;
}


void Animation::updateIdleSprite() // CURRENTLY JUST FOR IDLE
{
	sprite_.setTexture(*(animSprites_[make_pair(IDLE, orientation_)].getTexture())); // pointer ok??????!!!!
	sprite_.setTextureRect(IntRect(0, 0, SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));

	//switch (orientation_) {
	//case LEFT:
	//	sprite_.setTexture(*(animSprites_[make_pair(IDLE, LEFT)].getTexture())); // pointer ok??????!!!!
	//	sprite_.setTextureRect(IntRect(0, 0, SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
	//	break;
	//case RIGHT:
	//	sprite_.setTexture(*(animSprites_[make_pair(IDLE, LEFT)].getTexture())); // pointer ok??????!!!!
	//	sprite_.setTextureRect(IntRect(0, 0, SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
	//	break;
	//case DOWN:
	//	sprite_.setTexture(*(animSprites_[make_pair(IDLE, LEFT)].getTexture())); // pointer ok??????!!!!
	//	sprite_.setTextureRect(IntRect(0, 0, SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
	//	break;
	//case UP:
	//	sprite_.setTexture(*(animSprites_[make_pair(IDLE, LEFT)].getTexture())); // pointer ok??????!!!!
	//	sprite_.setTextureRect(IntRect(0, 0, SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
	//	break;
	//case LEFT_DOWN:
	//	sprite_.setTexture(*(animSprites_[make_pair(IDLE, LEFT)].getTexture())); // pointer ok??????!!!!
	//	sprite_.setTextureRect(IntRect(0, 0, SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
	//case LEFT_UP:
	//case RIGHT_DOWN:
	//	break;
	//case RIGHT_UP:
	//	break;
	//}

	//sprite_.setScale(3, 3);
	//sprite_.setPosition(position_);
}

// TO DO!!!
// ANimation class functionality of recognizing key presses nad changing orientation
// orientation becomes Animation member
// for now just do idle


// draws Animation based on keyword for animation type
void Animation::playAnim(Direction dir, bool moving)
{

}

// error handling?