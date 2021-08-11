#pragma once

#include "Test.h"
#include "Animation.h"
#include <map>
using namespace std;

class Character {
private:
	std::string imgRef_;
	Vector2f position_;
	Animation animation_;
	Direction orientation_ = DOWN;
	State state_ = IDLE;
	Vector2f directionVect_ = { 0 , 0 }; //?
	float speed_ = 0;

public:
	Character(float x_start, float y_start, std::string imgPath); //https://stackoverflow.com/questions/14693745/string-as-parameter

	void setOrientation(Direction new_orient);
	Direction getOrientation();
	Vector2f get_directionVect();
	void set_directionVect(float new_x, float new_y);
	void zeroDirection();
	State getState();
	void setState(State new_state);


	Vector2f getPosition();
	void updatePosition(float new_x, float new_y);
	Animation getAnimation();
	Animation setAnimation(); // ?
	float getSpeed();
	void updateSpeed();
	void update(Time dt);
};