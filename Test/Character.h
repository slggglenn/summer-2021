#pragma once

#include "Test.h"

class Character{
private:
	Vector2f position_;
	Texture texture_;
	Sprite sprite_;
	float speed_ = 0;
	Direction orientation_ = DOWN;
	Image textBack_; //!!!

public:
	Character(float x_start, float y_start, const std::string img_loc); //https://stackoverflow.com/questions/14693745/string-as-parameter
	Vector2f getPosition(); // vector?
	void updatePosition(float new_x, float new_y);
	FloatRect getSpriteBounds();
	//void setPosition()
	Texture getTexture();
	void setTexture(std::string img_loc);
	Sprite getSprite();
	void setSprite();
	void setOrientation(Direction new_orient);
	void isMoving(bool moving);
	void update(Time dt);
	// randomly generated movement
	// set orientation
};