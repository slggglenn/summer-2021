#pragma once

#include "Test.h"
// don't forget ifndef

class Mon
{
private:
	std::string text_loc = "graphics / eevee.png"; // make this pickable with method/initializer
	State state_;
	FloatRect hitbox_;
	unsigned int stepCounter_;
	RectangleShape rep;

	Vector2f position_;
	Texture texture_;
	//Animation animation_;
	float speed_ = 0;

	Vector2f direction = { 0, 0 };
	Image textBack_; //!!!
	Sprite sprite_;
	Direction orientation_ = DOWN;
	int idleFrame, movingFrame, asleepFrame;

	//IntRect idleL[2], idleR[2], idleU[2], idleD[2];
	std::map<std::tuple<State, Direction, int>, IntRect> frameMap;
	//IntRect idleRects[2] = {};
	//Int 

public:
	Mon(float new_x, float new_y, std::string img_loc); //https://stackoverflow.com/questions/14693745/string-as-parameter

	void initialize_frameMap();
	Vector2f getPosition();
	void updatePosition(float new_x, float new_y);
	FloatRect getSpriteBounds(); // !!! MODIFY !!!
	Texture getTexture();
	void setTexture(std::string img_loc);
	Sprite getSprite(); // !!! MODIFY !!!
	void setSprite(); // !!! MODIFY !!!
	void setOrientation(Direction new_orient);
	Direction getOrientation();
	Vector2f updateDirection();
	Vector2f zeroDirection();
	float getSpeed();
	void isMoving(bool moving);
	void update(Time dt);
	// randomly generated movement
	// set orientation
	void setDirection(Direction dir);
	Vector2f getDirection();

	Direction randDir();
	int randSteps();
	unsigned int get_stepCounter();
	void set_stepCounter(unsigned int steps);
	State getState();
	FloatRect getGlobalHitbox();
	void setState(State state);
	//bool willCollide(Sprite obj, FloatRect objHB);
	void updateRep();
	void updateHitbox();
	RectangleShape getRep();
	Direction oppDirection(Direction dir);

	// randomly generated movement
};