
#include "Test.h"
#include "Character.h";

Character::Character(float x_start, float y_start, std::string imgPath) {
	position_.x = x_start;
	position_.y = y_start;
	imgRef_ = imgPath;
	// do i need parameter for this really?? when is orientation used
	// animation already initialized
	
	animation_.getSprite().setPosition(position_);
}

Vector2f Character::get_directionVect()
{
	return directionVect_;
}

State Character::getState()
{
	return state_;
}

Animation Character::getAnimation()
{
	return animation_;
}
// updates direction vector based on key presses
Vector2f Character::updateDirection()
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) // more cases for iskeyheld stuff...should update state
	{
		setOrientation(LEFT);
		directionVect_.x = -1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		setOrientation(RIGHT);
		directionVect_.x = 1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		setOrientation(UP);
		directionVect_.y = -1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		setOrientation(DOWN);
		directionVect_.y = 1;
	}
	return directionVect_;
}

Vector2f Character::zeroDirection()
{
	directionVect_.x = 0;
	directionVect_.y = 0;
	return directionVect_;
}

Direction Character::getOrientation()
{
	return orientation_;
}

void Character::setOrientation(Direction new_orient)
{
	orientation_ = new_orient;
}

Vector2f Character::getPosition()
{
	return position_;
}

// updates position vector with x and y
void Character::updatePosition(float new_x, float new_y) {
	position_.x = new_x;
	position_.y = new_y;
}


// need set position!!

float Character::getSpeed()
{
	return speed_;
}

// 
void Character::updateSpeed()
{
	if (getState() == MOVING) speed_ = 80;
	else speed_ = 0;
}

// updates position for movement speed, current direction, and time
void Character::update(Time dt)
{
	// each frame, calculates new position
	position_.x += dt.asSeconds() * speed_ * get_directionVect().x;
	position_.y += dt.asSeconds() * speed_ * get_directionVect().y;

	// moves sprite to that location
	animation_.getSprite().setPosition(position_);
}