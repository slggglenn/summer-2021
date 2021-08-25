#include "Mon.h"
#include <iostream>

// constructor
Mon::Mon(float new_x, float new_y, std::string img_loc)
{
	position_.x = new_x;
	position_.y = new_y; // do i need parameter for this really?? when is orientation used
	setTexture(img_loc);
	sprite_.setTexture(texture_);
	idleFrame = 0;
	movingFrame = 0;
	asleepFrame = 0;
	setSprite();

	setTexture(text_loc);
	setSprite();
	updatePosition(new_x, new_y);
	state_ = IDLE;
	stepCounter_ = 0; //* Character::getSprite().getScale().y  // 0,0??? getPosition or global ounds?? why isn't color changing?
	hitbox_ = { getSprite().getPosition().x, getSprite().getPosition().y, getSprite().getGlobalBounds().width, getSprite().getGlobalBounds().height}; // how to set location and ave follow?
//getGlobalHitbox(); // sets hitbox to sprite location
//updateHitbox();
	rep.setSize(Vector2f(hitbox_.height, hitbox_.width));// Character::getSprite().getGlobalBounds().width,
		//Character::getSprite().getGlobalBounds().height)); // if this works update other
	rep.setFillColor(Color(2, 207, 188, 40));
	updateRep();

};



// gets position of the shape representation
Vector2f Mon::getPosition()
{
	return position_;
}

// updates position vector with x and y
void Mon::updatePosition(float new_x, float new_y) {
	position_.x = new_x;
	position_.y = new_y;
}

FloatRect Mon::getSpriteBounds()
{
	return sprite_.getGlobalBounds();
}

Vector2f Mon::getDirection()
{
	return direction;
}

// gets the texture
Texture Mon::getTexture()
{
	return texture_;
}

// sets the texture
void Mon::setTexture(std::string img_loc)//does this overload
{
	textBack_.loadFromFile("graphics/eevee.png");// !!! en.sfml-dev.org/forums/index.php?topic=12663.0
	textBack_.createMaskFromColor(Color(0, 128, 128), 0); // !!! NEED: program to get color pixels from the thing itself
	texture_.loadFromImage(textBack_);
}

// gets the sprite
Sprite Mon::getSprite() { return sprite_; }

// TODO:
// cycle thru animations
// idle animation
// transitioning between
// recognizing diagonal anims
// asleep

// finish meeeee
void Mon::initialize_frameMap()
{
	for (int i = 0; i < 3; i++)
	{
		State state = (State)i;
		for (int j = 0; j < 8; j++)
		{
			Direction dir = (Direction)j;

			if (state == IDLE)
			{
				for (int k = 0; k < 2; k++)
				{
					frameMap[std::make_tuple(state, direction, k)] = 
				}
			}
			else if (state == MOVING)
			{

			}
		}
	}
}

void Mon::setSprite()
{
	switch (orientation_) {
	case DOWN:
		//if (Keyboard::isKeyPressed(Keyboard::Left)) sprite_.setTextureRect(IntRect(78, 130, 21, 20));
		//else if (Keyboard::isKeyPressed(Keyboard::Right)) sprite_.setTextureRect(IntRect(77, 157, 20, 22));
		if (state_ == IDLE)
		sprite_.setTextureRect(IntRect(73, 29, 20, 19)); // parameters for coordinates!!
		break;
	case UP:
		//if (Keyboard::isKeyPressed(Keyboard::Left)) sprite_.setTextureRect(IntRect(81, 182, 18, 22));
		//else if (Keyboard::isKeyPressed(Keyboard::Right)) sprite_.setTextureRect(IntRect(85, 209, 17, 21));
		sprite_.setTextureRect(IntRect(75, 57, 20, 20));
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

float Mon::getSpeed()
{
	return speed_;
}

Direction Mon::getOrientation()
{
	return orientation_;
}

void Mon::setOrientation(Direction new_orient)
{
	orientation_ = new_orient;
}

void Mon::isMoving(bool moving)
{
	if (moving) speed_ = 130;
	else speed_ = 0;
}

void Mon::setDirection(Direction dir)
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
Vector2f Mon::updateDirection()
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

Vector2f Mon::zeroDirection()
{
	direction.x = 0;
	direction.y = 0;
	return direction;
}

// updates position for movement speed, current direction, and time
void Mon::update(Time dt)
{
	if (state_ == IDLE) !idleFrame; // 0 --> 1 --> 0...
	else if(state_ == ASLEEP) !asleepFrame; // 0 --> 1 --> 0...
	else if (state_ == MOVING)
	{
		if (movingFrame != 2) movingFrame++;
		else movingFrame = 0;// 0 --> 1 --> 0...
	}

	position_.x += dt.asSeconds() * speed_ * direction.x;
	position_.y += dt.asSeconds() * speed_ * direction.y;

	// moves shape representation to that location
	sprite_.setPosition(position_);
}

Direction Mon::oppDirection(Direction dir)
{
	switch (dir) {
	case LEFT:
		return RIGHT;
		break;
	case RIGHT:
		return LEFT;
		break;
	case UP:
		return DOWN;
		break;
	case DOWN:
		return UP;
		break;
	case LEFT_UP:
		return RIGHT_DOWN;
		break;
	case LEFT_DOWN:
		return RIGHT_UP;
		break;
	case RIGHT_DOWN:
		return LEFT_UP;
		break;
	case RIGHT_UP:
		return LEFT_DOWN;
		break;

	}
}
// hitbox position
// {} but first two are x and y from sprite's left
// when colliding, getGlobalHitbox

void Mon::updateRep()
{ // mon rep uses transform bc sprite moving, for others just set permanent position
	//rep.setPosition(Character::getSprite().getPosition());
	//if ()
	//std::cout << hitbox_.left << ", " << hitbox_.top << std::endl;
	rep.setPosition(hitbox_.left, hitbox_.top); // sets to top left
}

void Mon::updateHitbox()
{
	//Character::getSprite().getTransform().transformRect(hitbox_);
	hitbox_.left = getSprite().getPosition().x;//getGlobalBounds().left;
	hitbox_.top = getSprite().getPosition().y;
}

RectangleShape Mon::getRep() {
	return rep;
}

FloatRect Mon::getGlobalHitbox()
{
	return getSprite().getTransform().transformRect(hitbox_);
}

//bool Mon::willCollide(Sprite obj, FloatRect objHB)
//{
//	return (getGlobalHitbox().intersects(obj.getTransform().transformRect(objHB))); //something about this isn't working
//	/*{sprites[i].getTransform().transformRect(hitboxes[i]);
//		rep.setFillColor(Color(201, 114, 144, 40));
//		std::cout << "collision!";
//		return true;
//	}
//	else
//	{
//		rep.setFillColor(Color(2, 207, 188, 40));
//		return false;
//	}*/
//	/*Character::updatePosition(Character::getPosition().x - dt.asSeconds() * Character::getSpeed() * Character::getDirection().x,
//		Character::getPosition().y - dt.asSeconds() * Character::getSpeed() * Character::getDirection().y);*/
//	// resets with our update (eevee.getSprite()) command in main none the wiser
//}


unsigned int Mon::get_stepCounter()
{
	return stepCounter_;
}

void Mon::set_stepCounter(unsigned int steps)
{
	stepCounter_ = steps;
}

void Mon::setState(State state)
{
	state_ = state;
}

State Mon::getState()
{
	return state_;
}

Direction Mon::randDir()
{
	srand((int)time(0));
	int randFour = rand() % 4;
	return (Direction)randFour;
}

int Mon::randSteps()
{
	srand((int)time(0)); // make these different?
	int randTen = rand() % 50; // 0-49
	state_ = MOVING;
	if (randTen > 0 && randTen <= 5) {
		stepCounter_ = 2;
		return 2;
	}
	else if (randTen > 5 && randTen <= 7) {
		stepCounter_ = 1;
		return 1;
	}
	else if (randTen == 8) {
		stepCounter_ = 3;
		return 3;
	}
	else {
		stepCounter_ = 0;
		state_ = IDLE;
		return 0;
	}
}

// getTransform().transformRect(m_hitbox);
//const bool colliding = player.getGlobalHitbox().intersects(enemy.getGlobalHitbox());

