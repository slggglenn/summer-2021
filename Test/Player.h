#pragma once

#include "Test.h"
#include "Character.h"

class Player : public Character
{
private:
	const std::string text_loc = "graphics/eevee.png";

public:
	Player(float new_x, float new_y);
	void updateDirection();
};