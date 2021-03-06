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
		else frame_ = !frame_; // always starts at 0 for new animation

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

Vector2f Mon::zeroDirection()
{
	direction.x = 0;
	direction.y = 0;
	return direction;
}

// updates position for movement speed, current direction, and time
void Mon::update(Time dt)
{
	for (int i = 0; i < 8; i++) isOption[i] = true;

	waitFrame_++;
	
	// updates frame #
	
	setSprite();

	// updates position vector
	position_.x += dt.asSeconds() * speed_ * direction.x;
	position_.y += dt.asSeconds() * speed_ * direction.y;

	if (position_.x <= 1 || position_.x >= 1919 || position_.y <= 1 || position_.y >= 1079)
	{
		srand(time(0));
		isMoving(false);
		set_stepCounter(0);

		// only due to barrier rn
		Direction restricted[3] = { NONE, NONE, NONE };
		for (int i = 0; i < 3; i++)
		{
			if (restricted[i] == NONE)
			{
				if (position_.x <= 1) restricted[i] = LEFT;
				else if (position_.x >= 1919) restricted[i] = RIGHT;
				else if (position_.y <= 1) restricted[i] = UP;
				else if (position_.y >= 1079) restricted[i] = DOWN;
			}
		}

		setDirection(randDir(restricted[0], restricted[1], restricted[2])); // generate opposite direction
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

void Mon::updateRep()
{
	rep.setPosition(hitbox_.left, hitbox_.top);
}

void Mon::updateHitbox()
{
	hitbox_.left = getSprite().getPosition().x;
	hitbox_.top = getSprite().getPosition().y;
}

RectangleShape Mon::getRep() {
	return rep;
}

FloatRect Mon::getGlobalHitbox()
{
	return getSprite().getTransform().transformRect(hitbox_);
}

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

Direction Mon::randDir(Direction constr1, Direction constr2, Direction constr3)
{
	int numChoices = 4; // try first w/o the combos
	//ol isOption[8];// = { true, true, true, true, true, true, true, true }
	if (constr1 == LEFT || constr2 == LEFT || constr3 == LEFT)
	{// need to counteract when out of bounds??
		numChoices--;
		isOption[(int)LEFT] = false;
		isOption[(int)LEFT_UP] = false;
		isOption[(int)LEFT_DOWN] = false; // get rid fo extras if unnec
	}
	else if (constr1 == RIGHT || constr2 == RIGHT || constr3 == RIGHT)
	{
		numChoices--;
		isOption[(int)RIGHT] = false;
		isOption[(int)RIGHT_UP] = false;
		isOption[(int)RIGHT_DOWN] = false;
	}
	else if (constr1 == UP || constr2 == UP || constr3 == UP)
	{
		numChoices--;
		isOption[(int)UP] = false;
		isOption[(int)LEFT_UP] = false;
		isOption[(int)RIGHT_UP] = false;
	}
	else if (constr1 == DOWN || constr2 == DOWN || constr3 == DOWN)
	{
		numChoices--;
		isOption[(int)DOWN] = false;
		isOption[(int)LEFT_DOWN] = false;
		isOption[(int)RIGHT_DOWN] = false;
	}
	// error case + make available 
	srand((int)time(0));
	return (Direction)(rand() % numChoices);
}

int Mon::randSteps()
{
	srand((int)time(0));
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