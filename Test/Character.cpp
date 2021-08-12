
#include "Test.h"
#include "Character.h"


Character::Character(float x_start, float y_start, std::string imgPath) {
	updatePosition(x_start, y_start);
	imgRef_ = imgPath;
	// do i need parameter for this really?? when is orientation used
	// animation already initialized
	animation_.setTexture(imgPath);
	animation_.getSprite().setPosition(position_);
}

Vector2f Character::get_directionVect()
{
	return directionVect_;
}

void Character::set_directionVect(float new_x, float new_y)
{
	directionVect_.x = new_x;
	directionVect_.y = new_y;
}

State Character::getState()
{
	return state_;
}

void Character::setState(State new_state)
{
	state_ = new_state;
}

Animation Character::getAnimation()
{
	return animation_;
}

void Character::zeroDirection()
{
	directionVect_.x = 0;
	directionVect_.y = 0;
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
	animation_.getSprite().setPosition(position_); // NOT A CAUSE OF THE ERRO!!!//
}