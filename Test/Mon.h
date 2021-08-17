#pragma once

#include "Test.h"
#include "Character.h"
// don't forget ifndef

class Mon : public Character
{
private:
	std::string text_loc = "graphics / eevee.png"; // make this pickable with method/initializer
	State state_;

public:
	Mon(float new_x, float new_y, std::string text_loc); //https://stackoverflow.com/questions/14693745/string-as-parameter
	Direction randDir(Time dt);
	int randSteps(Time dt);

	// randomly generated movement
};