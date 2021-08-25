#pragma once

#include "Test.h"
#include "Character.h"
// don't forget ifndef

class Mon : public Character
{
private:
	std::string text_loc = "graphics / eevee.png"; // make this pickable with method/initializer
	State state_;
	FloatRect hitbox_;
	unsigned int stepCounter_;
	RectangleShape rep;

public:
	Mon(float new_x, float new_y, std::string text_loc); //https://stackoverflow.com/questions/14693745/string-as-parameter
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