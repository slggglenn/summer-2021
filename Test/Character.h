#pragma once

#include "Test.h"
#include "Animation.h"
#include <map>
using namespace std;

class Character {
private:
	Vector2f position_;
	Animation animation_;
	Direction orientation_ = DOWN; // direction character faces  (default is DOWN)
	State state_ = IDLE; // IDLE, MOVING, ASLEEP
	Vector2f directionVect_ = { 0 , 0 }; // vector interpretation of orientation_
	float speed_ = 0;

public:
	//https://stackoverflow.com/questions/14693745/string-as-parameter
	Character(float x_start, float y_start, const std::string imgPath);

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
	float getSpeed();
	void updateSpeed();
	void update(Time dt);
};