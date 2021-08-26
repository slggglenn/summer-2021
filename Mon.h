#pragma once

#include "Test.h"

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
	float speed_ = 0;
	bool isOption[8] = { true, true, true, true, true, true, true, true };

	Vector2f direction = { 0, 0 };
	Image textBack_;
	Sprite sprite_;
	Direction orientation_ = DOWN;
	int frame_ = 0;
	int waitFrame_ = 0;
	Direction orientLastFrame_ = DOWN;
	std::map<std::tuple<State, Direction, int>, IntRect> frameMap;

public:
	void updateFrames(Direction dir);
	Mon(float new_x, float new_y, std::string img_loc); //https://stackoverflow.com/questions/14693745/string-as-parameter
	void initialize_frameMap();
	void updateFrames(Direction dir);
	Vector2f getPosition();
	void updatePosition(float new_x, float new_y);
	FloatRect getSpriteBounds();
	Texture getTexture();
	void setTexture(std::string img_loc);
	Sprite getSprite();
	void setSprite();
	void setOrientation(Direction new_orient);
	Direction getOrientation();
	//Vector2f updateDirection();
	Vector2f zeroDirection();
	float getSpeed();
	void isMoving(bool moving);
	void update(Time dt);
	void setDirection(Direction dir);
	Vector2f getDirection();
	Direction randDir(Direction constr1, Direction constr2, Direction constr3);
	int randSteps();
	unsigned int get_stepCounter();
	void set_stepCounter(unsigned int steps);
	State getState();
	FloatRect getGlobalHitbox();
	void setState(State state);
	void updateRep();
	void updateHitbox();
	RectangleShape getRep();
	Direction oppDirection(Direction dir);
};