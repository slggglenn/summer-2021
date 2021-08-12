#pragma once

#include "Test.h"
#include "Character.h"

class Player : public Character
{
private:
	std::string text_loc = "graphics / player.png"; /// !!!
	//Vector2f position_; // character also has position tho....

	// TEMP //
	Texture temp;
	Sprite temp_sprite;
	Vector2f temp_position;

public:
	Player(float new_x, float new_y, std::string text_loc);
	/*Vector2f getPosition();*/
	void updateDirection();

	void tempSetup(std::string text_loc);
	Sprite getTempSprite();
};