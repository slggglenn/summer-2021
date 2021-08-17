#pragma once

#include "Test.h"

class Character {
private:
	Vector2f position_;
	Texture texture_;
	//Animation animation_;
	float speed_ = 0;
	Direction orientation_ = DOWN;
	Vector2f direction = { 0, 0 };
	Image textBack_; //!!!
	Sprite sprite_;

public:
	Character(float x_start, float y_start, const std::string img_loc); //https://stackoverflow.com/questions/14693745/string-as-parameter
	Vector2f getPosition(); // vector?
	void updatePosition(float new_x, float new_y);
	//Animation setAnimation()
	FloatRect getSpriteBounds(); // !!! MODIFY !!!
	//void setPosition()
	Texture getTexture();
	void setTexture(std::string img_loc);
	Sprite getSprite(); // !!! MODIFY !!!
	void setSprite(); // !!! MODIFY !!!
	void setOrientation(Direction new_orient);
	Direction getOrientation();
	//Direction* setmovementMatrix(Direction x, Direction y);
	Vector2f updateDirection();
	Vector2f zeroDirection();
	float getSpeed();
	void isMoving(bool moving);
	void update(Time dt);
	// randomly generated movement
	// set orientation
	void setDirection(Direction dir);
	Vector2f getDirection();
};