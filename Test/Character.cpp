
#include "Test.h"

#include "Character.h";


// constructor
Character::Character(float x_start, float y_start) {
	position_.x = x_start;
	position_.y = y_start; // do i need parameter for this really?? when is orientation used
	// initialize animation!!
	// 
	//setTexture(img_loc);
	//setSprite();
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

//FloatRect Character::getSpriteBounds()
//{
//	return sprite_.getGlobalBounds();
//}

// gets the texture
//Texture Character::getTexture()
//{
//	return texture_;
//}

// sets the texture
//void Character::setTexture(std::string img_loc)//does this overload
//{
//	textBack_.loadFromFile("graphics/eevee.png");// !!! en.sfml-dev.org/forums/index.php?topic=12663.0
//	textBack_.createMaskFromColor(Color(0, 128, 128), 0); // !!! NEED: program to get color pixels from the thing itself
//	texture_.loadFromImage(textBack_);
//}

// gets the sprite
//Sprite Character::getSprite()
//{
//	return sprite_;
//}

//void Character::setSprite()
//{
//	sprite_.setTexture(texture_); //652/2/4/2 = 40.75, 267/11 = ~24.3 22x22
//
//	switch (orientation_) {
//		case DOWN:
//			if (Keyboard::isKeyPressed(Keyboard::Left)) sprite_.setTextureRect(IntRect(73, 80, 22, 22));
//			else if (Keyboard::isKeyPressed(Keyboard::Right)) sprite_.setTextureRect(IntRect(75, 105, 22, 22));
//			else sprite_.setTextureRect(IntRect(73, 29, 22, 22)); // parameters for coordinates!!
//			break;
//		case UP:
//			if (Keyboard::isKeyPressed(Keyboard::Left)) sprite_.setTextureRect(IntRect(73, 80, 22, 22));
//			else if (Keyboard::isKeyPressed(Keyboard::Right)) sprite_.setTextureRect(IntRect(75, 105, 22, 22));
//			else sprite_.setTextureRect(IntRect(73, 51, 22, 22));
//			break;
//		case LEFT:
//			sprite_.setTextureRect(IntRect(73, 80, 22, 22));
//			break;
//		case RIGHT:
//			sprite_.setTextureRect(IntRect(75, 105, 22, 22));
//			break;
//	}
//
//	//sprite_.setScale(3, 3);
//	sprite_.setPosition(position_);
//}

// need set position!!

float Character::getSpeed()
{
	return speed_;
}

//Direction Character::getOrientation()
//{
//	return orientation_;
//}
//
//void Character::setOrientation(Direction new_orient)
//{
//	orientation_ = new_orient;
//}

void Character::isMoving(bool moving)
{
	if (moving) speed_ = 80;
	else speed_ = 0;
}

//Vector2f Character::updateDirection()
//{
//	if (Keyboard::isKeyPressed(Keyboard::Left))
//	{
//		setOrientation(LEFT);
//		direction.x = -1;
//	}
//
//	if (Keyboard::isKeyPressed(Keyboard::Right))
//	{
//		setOrientation(RIGHT);
//		direction.x = 1;
//	}
//
//	if (Keyboard::isKeyPressed(Keyboard::Up))
//	{
//		setOrientation(UP);
//		direction.y = -1;
//	}
//
//	if (Keyboard::isKeyPressed(Keyboard::Down))
//	{
//		setOrientation(DOWN);
//		direction.y = 1;
//	}
//	return direction;
//}
//
//Vector2f Character::zeroDirection()
//{
//	direction.x = 0;
//	direction.y = 0;
//	return direction;
//}

//Direction* Character::setmovementMatrix(Direction x, Direction y)
//{
//	movementMatrix[0] = x;
//	movementMatrix[1] = y;
//}

// updates position for movement speed, current direction, and time
void Character::update(Time dt)
{
	position_.x += dt.asSeconds() * speed_ * animation_.getDirection().x;
	position_.y += dt.asSeconds() * speed_ * animation_.getDirection().y;
	//if (orientation_ == LEFT)
	/*{
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
	}*/

	// moves shape representation to that location
	sprite_.setPosition(position_);
}

// TODO
// figure out where to put setposition
// modify drawing function
// test