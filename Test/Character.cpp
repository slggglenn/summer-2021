#include "Test.h"
#include "Character.h"


// constructor
Character::Character(float x_start, float y_start, const std::string img_loc) {
	position_.x = x_start;
	position_.y = y_start; // do i need parameter for this really?? when is orientation used
	setTexture(img_loc);
	sprite_.setTexture(texture_);
	setSprite();
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

Vector2f Character::getDirection()
{
	return direction;
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
	switch (orientation_) {
	case DOWN:
		if (Keyboard::isKeyPressed(Keyboard::Left)) sprite_.setTextureRect(IntRect(78, 130, 21, 20));
		else if (Keyboard::isKeyPressed(Keyboard::Right)) sprite_.setTextureRect(IntRect(77, 157, 20, 22));
		else sprite_.setTextureRect(IntRect(73, 29, 20, 19)); // parameters for coordinates!!
		break;
	case UP:
		if (Keyboard::isKeyPressed(Keyboard::Left)) sprite_.setTextureRect(IntRect(81, 182, 18, 22));
		else if (Keyboard::isKeyPressed(Keyboard::Right)) sprite_.setTextureRect(IntRect(85, 209, 17, 21));
		else sprite_.setTextureRect(IntRect(75, 57, 20, 20));
		break;
	case LEFT_UP:
		sprite_.setTextureRect(IntRect(81, 182, 18, 22));
		break;
	case LEFT_DOWN:
		sprite_.setTextureRect(IntRect(78, 130, 21, 20));
		break;
	case RIGHT_UP:
		sprite_.setTextureRect(IntRect(85, 209, 17, 21));
		break;
	case RIGHT_DOWN:
		sprite_.setTextureRect(IntRect(77, 157, 20, 22));
		break;
	case LEFT:
		sprite_.setTextureRect(IntRect(75, 80, 21, 22));
		break;
	case RIGHT:
		sprite_.setTextureRect(IntRect(76, 105, 22, 21));
		break;
	}

	sprite_.setScale(5, 5);
}

float Character::getSpeed()
{
	return speed_;
}

Direction Character::getOrientation()
{
	return orientation_;
}

void Character::setOrientation(Direction new_orient)
{
	orientation_ = new_orient;
}

void Character::isMoving(bool moving)
{
	if (moving) speed_ = 130;
	else speed_ = 0;
}

void Character::setDirection(Direction dir)
{
	switch (dir) {
		case LEFT:
			direction.x = -1;
			break;
		case RIGHT:
			direction.x = 1;
			break;
		case UP:
			direction.y = -1; // others?
			break;
		case DOWN:
			direction.y = 1;
			break;
	}
}

// this should be moved to player!!
Vector2f Character::updateDirection()
{

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			setOrientation(LEFT_UP); // not really working
			direction.x = -1;
			direction.y = -1;
		}
		else {
			setOrientation(LEFT);
			direction.x = -1;
		}	
	}

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		setOrientation(RIGHT);
		direction.x = 1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		setOrientation(UP);
		direction.y = -1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		setOrientation(DOWN);
		direction.y = 1;
	}
	return direction;
}

Vector2f Character::zeroDirection()
{
	direction.x = 0;
	direction.y = 0;
	return direction;
}

// updates position for movement speed, current direction, and time
void Character::update(Time dt)
{
	position_.x += dt.asSeconds() * speed_ * direction.x;
	position_.y += dt.asSeconds() * speed_ * direction.y;
	
	// moves shape representation to that location
	sprite_.setPosition(position_);
}