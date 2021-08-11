#pragma once

#include "Test.h"
#include "Animation.h"

class Character {
private:
	Vector2f position_;
	//Texture texture_;
	Animation animation_;
	float speed_ = 0;
	Image textBack_; //!!!

public:
	Character(float x_start, float y_start); //https://stackoverflow.com/questions/14693745/string-as-parameter
	Vector2f getPosition(); // vector?
	void updatePosition(float new_x, float new_y);
	Animation setAnimation();
	//FloatRect getSpriteBounds(); // !!! MODIFY !!!
	//void setPosition()
	//Texture getTexture(); // !!! MODIFY !!!
	//void setTexture(std::string img_loc); // !!! MODIFY !!!
	//Sprite getSprite(); // !!! MODIFY !!!
	//void setSprite(); // !!! MODIFY !!!
	//void setOrientation(Direction new_orient);
	//Direction getOrientation();
	////Direction* setmovementMatrix(Direction x, Direction y);
	//Vector2f updateDirection();
	//Vector2f zeroDirection();
	float getSpeed();
	void isMoving(bool moving);
	void update(Time dt);
	// randomly generated movement
	// set orientation
};