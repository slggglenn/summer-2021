
#include "Test.h"
#include "Character.h";

// constructor
Character::Character(float x_start, float y_start, const std::string img_loc) {
	position_.x = x_start;
	position_.y = y_start; // do i need parameter for this really?? when is orientation used
	setTexture(img_loc);
	setSprite();
	//cout << img_loc;
	
	// 73,29-95,29 --> 73, 47 - 95,47
	//sprite_.setPosition(position_);
}

// gets position of the shape representation
Vector2f Character::getPosition()
{
	return position_;
}

// updates position vector with x and y
void Character::updatePosition(float new_x, float new_y) {
	position_.x = new_x;
	position_.y = new_y;
}

FloatRect Character::getSpriteBounds()
{
	return sprite_.getGlobalBounds();
}

// gets the texture
Texture Character::getTexture()
{
	return texture_;
}

// sets the texture
void Character::setTexture(std::string img_loc)//does this overload
{
	textBack_.loadFromFile("graphics/eevee.png");// !!! en.sfml-dev.org/forums/index.php?topic=12663.0
	textBack_.createMaskFromColor(Color(0, 128, 128), 0); // !!! NEED: program to get color pixels from the thing itself
	texture_.loadFromImage(textBack_);
}
// gets the sprite
Sprite Character::getSprite()
{
	return sprite_;
}

void Character::setSprite()
{
	sprite_.setTexture(texture_); //652/2/4/2 = 40.75, 267/11 = ~24.3 22x22
	sprite_.setTextureRect(IntRect(73, 29, 22, 22)); // parameters for coordinates!!
	sprite_.setScale(3, 3);
	sprite_.setPosition(position_);
}

void Character::setOrientation(Direction new_orient)
{
	orientation_ = new_orient;
}

void Character::isMoving(bool moving)
{
	if (moving) speed_ = 40;
	else speed_ = 0;
}

// updates position for movement speed, current direction, and time
void Character::update(Time dt)
{
	if (orientation_ == LEFT)
	{
		position_.x -= dt.asSeconds() * speed_;
	}
	if (orientation_ == RIGHT)
	{
		position_.x += dt.asSeconds() * speed_;
	}
	if (orientation_ == UP)
	{
		position_.y -= dt.asSeconds() * speed_;
	}
	if (orientation_ == DOWN)
	{
		position_.y += dt.asSeconds() * speed_;
	}

	// moves shape representation to that location
	sprite_.setPosition(position_);
}