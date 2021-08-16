
#include "Animation.h"
#include <iostream>

Animation::Animation()
{
	updateIdle();
	updateMoving();
	updateAsleep();
	updateSprite(IDLE, RIGHT); // this command actually works
}

Sprite Animation::getSprite()
{
	return sprite_;
}

void Animation::setTexture(const std::string imgPath)
{// en.sfml-dev.org/forums/index.php?topic=12663.0
	textBack_.loadFromFile(imgPath);
	textBack_.createMaskFromColor(Color(0, 128, 128), 0);
	texture_.loadFromImage(textBack_);
}

Texture Animation::getTexture()
{
	return texture_;
}

void Animation::updateIdle() // not very memory efficient
{
	for (unsigned int j = 0; j < NUM_IDLE; j++)
	{
		idle_[j].setTexture(texture_);
		if (!(j % 2))
		{
			idle_[j].setTextureRect(IntRect(IDLE_START_X, IDLE_START_Y + (SPRITE_SIDE_LEN * (j / 2)),
				SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
		}
		else {
			idle_[j].setTextureRect(IntRect(IDLE_START_X + SPRITE_SIDE_LEN, IDLE_START_Y,
				SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
	}
		idle_[j].setScale(3, 3);
	}
}

void Animation::updateMoving()
{
	for (unsigned int j = 0; j < NUM_WALK; j++)
	{
		moving_[j].setTexture(texture_);
		if (!(j % 2))
		{
			moving_[j].setTextureRect(IntRect(MOVE_START_X, MOVE_START_Y + (SPRITE_SIDE_LEN * (j / 2)),
				SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
		}
		else {
			moving_[j].setTextureRect(IntRect(MOVE_START_X + SPRITE_SIDE_LEN, MOVE_START_Y,
				SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
		}
		moving_[j].setScale(3, 3);
	}
}

void Animation::updateAsleep()
{
	for (unsigned int j = 0; j < NUM_SLEEP; j++)
	{
		asleep_[j].setTexture(texture_);
		if (!j)
		{
			asleep_[j].setTextureRect(IntRect(SLEEP_START_X, SLEEP_START_Y + (SPRITE_SIDE_LEN * (j / 2)),
				SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
		}
		else {
			asleep_[j].setTextureRect(IntRect(SLEEP_START_X + SPRITE_SIDE_LEN, SLEEP_START_Y,
				SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
		}
		asleep_[j].setScale(3, 3);
	}
}


// sets the current sprite given STATE and DIRECTION
// (currently just for IDLE state)
void Animation::updateSprite(State state, Direction dir)
{
	unsigned int index, num;
	Sprite* arrFirst;

	switch (state) {
	case IDLE:
		arrFirst = idle_;
		num = NUM_IDLE;
		break;
	case MOVING:
		arrFirst = moving_;
		num = NUM_WALK;
		break;
	case ASLEEP:
		arrFirst = asleep_;
		num = NUM_SLEEP;
		break;
	default: // TEMP!! THIS MUST BE REPLACED WITH ERROR! //
		arrFirst = idle_;
		num = NUM_IDLE;
		break;
	}

	switch (dir) {
	case DOWN:
		index = 0;
		break;
	case UP:
		index = num / 8;
		break;
	case LEFT:
		index = 2 * (num / 8);
		break;
	case RIGHT:
		index = 3 * (num / 8);
		break;
	case LEFT_DOWN:
		index = 4 * (num / 8);
		break;
	case RIGHT_DOWN:
		index = 5 * (num / 8);
		break;
	case LEFT_UP:
		index = 6 * (num / 8);
		break;
	case RIGHT_UP:
		index = 7 * (num / 8);
		break;
	default: // THIS MUST BE ERROR //
		index = 0;
		break;
	}

	sprite_ = *(arrFirst + index);
}


void Animation::playAnim(Direction dir, State sta)
{
	switch (dir) {
		case DOWN:
			break;
		case UP:
			break;
		case LEFT:
			break;
		case LEFT_DOWN:
			break;
		case LEFT_UP:
			break;
		case RIGHT:
			break;
		case RIGHT_DOWN:
			break;
		case RIGHT_UP:
			break;
	}
}