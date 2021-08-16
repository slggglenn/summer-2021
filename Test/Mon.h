#pragma once

#include "Test.h"
#include "Character.h"
// don't forget ifndef

class Mon : public Character
{
private:
	const std::string text_loc = "graphics / eevee.png"; // make this pickable with method/initializer

public:
	Mon(float new_x, float new_y, const std::string text_loc); //https://stackoverflow.com/questions/14693745/string-as-parameter
	
	// randomly generated movement
};