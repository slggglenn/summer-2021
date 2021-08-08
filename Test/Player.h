#pragma once

#include "Test.h"
#include "Character.h"

//using namespace sf;

class Player : public Character
{
private:
	std::string text_loc = "graphics / player.png";

public:
	Player(float new_x, float new_y, std::string text_loc);
	/*void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();*/
};