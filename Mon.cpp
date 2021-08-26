#include "Mon.h"
#include <iostream>

// constructor
Mon::Mon(float new_x, float new_y, std::string img_loc)
{
	position_.x = new_x;
	position_.y = new_y; // do i need parameter for this really?? when is orientation used
	setTexture(img_loc);
	sprite_.setTexture(texture_);
	initialize_frameMap();
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
	for (int i = 0; i < 3; i++) // 3/4 states: IDLE, MOVING, ASLEEP
	{
		State state = (State)i;
		for (int j = 0; j < 8; j++) // 8/9 states: all directions
		{
			Direction dir = (Direction)j;

			switch (dir)
			{
			case LEFT:

				if (state == IDLE)
				{
					for (int k = 0; k < 2; k++)
					{
						if(!k) frameMap[std::make_tuple(state, dir, k)] = IntRect(75, 80, 21, 22); // change to 81
						else frameMap[std::make_tuple(state, dir, k)] = IntRect(104, 81, 21, 22); //104, 81
						/*std::cout << frameMap[std::make_tuple(IDLE, LEFT, 0)].left
							<< frameMap[std::make_tuple(IDLE, LEFT, 0)].top
							<< frameMap[std::make_tuple(IDLE, LEFT, 0)].width
							<< frameMap[std::make_tuple(IDLE, LEFT, 0)].height << std::endl << std::endl;*/
					}
				}
				else if (state == MOVING)
				{
					for (int k = 0; k < 3; k++)
					{
						if (!k) frameMap[std::make_tuple(state, dir, k)] = IntRect(142, 97, 22, 21);
						else if (k == 1) frameMap[std::make_tuple(state, dir, k)] = IntRect(173, 99, 25, 18); // need to alwayshave same width/height + mainly x to ensure no sprite movement
						else frameMap[std::make_tuple(state, dir, k)] = IntRect(206, 97, 23, 21); // 97!!
					}
				
				}
				break;
			case RIGHT:

				if (state == IDLE) {
					for (int k = 0; k < 2; k++) {
						if (!k) frameMap[std::make_tuple(state, dir, k)] = IntRect(76, 105, 22, 21);
						else frameMap[std::make_tuple(state, dir, k)] = IntRect(106, 105, 20, 20);
					}
				}
				else if (state == MOVING) {
					for (int k = 0; k < 3; k++) {
						if (!k) frameMap[std::make_tuple(state, dir, k)] = IntRect(143, 124, 22, 21);
						else if (k == 1) frameMap[std::make_tuple(state, dir, k)] = IntRect(174, 125, 25, 18);
						else frameMap[std::make_tuple(state, dir, k)] = IntRect(206, 125, 23, 21);
					}
				}
				break;
			case UP:

				if (state == IDLE) {
					for (int k = 0; k < 2; k++) {
						if (!k) frameMap[std::make_tuple(state, dir, k)] = IntRect(75, 57, 20, 20);
						else frameMap[std::make_tuple(state, dir, k)] = IntRect(102, 57, 19, 19); // check
					}
				}
				else if (state == MOVING) {
					for (int k = 0; k < 3; k++) {
						if (!k) frameMap[std::make_tuple(state, dir, k)] = IntRect(145, 69, 19, 20);
						else if (k == 1) frameMap[std::make_tuple(state, dir, k)] = IntRect(176, 67, 20, 24);
						else frameMap[std::make_tuple(state, dir, k)] = IntRect(208, 70, 19, 17);
					}
				}
				break;
			case DOWN:

				if (state == IDLE) {
					for (int k = 0; k < 2; k++) {
						if (!k) frameMap[std::make_tuple(state, dir, k)] = IntRect(73, 29, 20, 19);
						else frameMap[std::make_tuple(state, dir, k)] = IntRect(101, 30, 19, 18);
					}
				}
				else if (state == MOVING) {
					for (int k = 0; k < 3; k++) {
						if (!k) frameMap[std::make_tuple(state, dir, k)] = IntRect(146, 41, 19, 20);
						else if (k == 1) frameMap[std::make_tuple(state, dir, k)] = IntRect(176, 40, 21, 16);
						else frameMap[std::make_tuple(state, dir, k)] = IntRect(208, 37, 20, 23);
					}
				}
				break;
			}
			
			/*else if (state == MOVING)
			{

			}*/
		}
	}
}

void Mon::setSprite()
{
	sprite_.setTextureRect(frameMap[std::make_tuple(state_, orientation_, frame_)]);

	switch (orientation_) {
	//case DOWN:
	//	//if (Keyboard::isKeyPressed(Keyboard::Left)) sprite_.setTextureRect(IntRect(78, 130, 21, 20));
	//	//else if (Keyboard::isKeyPressed(Keyboard::Right)) sprite_.setTextureRect(IntRect(77, 157, 20, 22));
	//	sprite_.setTextureRect(IntRect(73, 29, 20, 19)); // parameters for coordinates!!
	//	break;
	//case UP:
	//	//if (Keyboard::isKeyPressed(Keyboard::Left)) sprite_.setTextureRect(IntRect(81, 182, 18, 22));
	//	//else if (Keyboard::isKeyPressed(Keyboard::Right)) sprite_.setTextureRect(IntRect(85, 209, 17, 21));
	//	sprite_.setTextureRect(IntRect(75, 57, 20, 20));
	//	break;
	/*case LEFT_UP:
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
		break;*/
	//case LEFT:
	//	/*std::cout << frameMap[std::make_tuple(IDLE, LEFT, 0)].left
	//		<< frameMap[std::make_tuple(IDLE, LEFT, 0)].top
	//		<< frameMap[std::make_tuple(IDLE, LEFT, 0)].width
	//		<< frameMap[std::make_tuple(IDLE, LEFT, 0)].height << std::endl << std::endl;*/

	//	std::cout << orientLastFrame_ << ", " << orientation_ << " frame: " << frame_ << std::endl;

	//	sprite_.setTextureRect(frameMap[std::make_tuple(state_, orientation_, frame_)]);
	//	break;
	//case RIGHT:
	//	sprite_.setTextureRect(IntRect(76, 105, 22, 21));
	//	break;
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

void Mon::updateFrames(Direction dir)
{

	orientLastFrame_ = orientation_;
	orientation_ = dir;

	//std::cout << "hello! ";

	if (waitFrame_ == 60) { // find way to make diff for idle v moving
		if (orientation_ == orientLastFrame_) // looping within same set of frames
		{
			//std::cout << "we're here now ";
			if (state_ == ASLEEP || state_ == IDLE)
			{
				//std::cout << "hi";//!frame_;
				if (frame_ == 2) frame_ = 0;
				else frame_ = !frame_; // does this update?
			}
			else if (state_ == MOVING)
			{
				if (frame_ != 2) frame_++;
				else frame_ = 0;
			}
		}
		else !frame_; // always starts at 0 for new animation

		waitFrame_ = 0;
	}
}

void Mon::setOrientation(Direction new_orient)
{
	orientation_ = new_orient;
}

void Mon::isMoving(bool moving)
{
	if (moving) speed_ = 160;
	else speed_ = 0;
}

void Mon::setDirection(Direction dir)
{
	updateFrames(dir);

	//std::cout << "last frame: " << orientLastFrame_ << std::endl;
	//std::cout << "this frame: " << orientation_ << std::endl << std::endl;

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

//// this should be moved to player!!
//Vector2f Mon::updateDirection()
//{
//
//	if (Keyboard::isKeyPressed(Keyboard::Left))
//	{
//		if (Keyboard::isKeyPressed(Keyboard::Up))
//		{
//			setOrientation(LEFT_UP); // not really working
//			direction.x = -1;
//			direction.y = -1;
//		}
//		else {
//			setOrientation(LEFT);
//			direction.x = -1;
//		}
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

Vector2f Mon::zeroDirection()
{
	direction.x = 0;
	direction.y = 0;
	return direction;
}

// updates position for movement speed, current direction, and time
void Mon::update(Time dt)
{
	waitFrame_++;
	// cases:
	// idle running (0,1,0,1...)
	// start walking-->if idle ends on 1 or 0--> go to 0 (0,1,2,0,1,2...)
	//	if stops: idle 0 (0,1,...)
	//  if changes dir: new direction moving's 0 (0,1,2...)
	
	// updates frame #
	
	setSprite();

	// updates position vector
	position_.x += dt.asSeconds() * speed_ * direction.x;
	position_.y += dt.asSeconds() * speed_ * direction.y;

	if (position_.x == 0 || position_.x == 1920 || position_.y == 0 || position_.y == 1080)
	{
		isMoving(false);
		setDirection(oppDirection(orientation_)); // generate opposite direction
		isMoving(true);
		setSprite();
	} // update collision protocol: if near obj HB, remove direction from possibility

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



// update collision protocol: if near obj HB, remove direction from possibility