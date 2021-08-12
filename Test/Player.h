#pragma once

#include "Test.h"
#include "Character.h"

class Player : public Character
{
private:
	std::string text_loc = "graphics / player.png"; /// !!!
	//Vector2f position_; // character also has position tho....

public:
	Player(float new_x, float new_y, std::string text_loc);
	/*Vector2f getPosition();*/
	void updateDirection();
};