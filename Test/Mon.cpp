#include "Character.h"
#include "Mon.h"

// constructor
Mon::Mon(float new_x, float new_y, std::string text_loc) : Character(new_x, new_y, text_loc)
{
	Character::setTexture(text_loc);
	Character::setSprite();
	Character::updatePosition(new_x, new_y);
	state_ = IDLE;
};

Direction Mon::randDir(Time dt)
{
	srand((int) time(0));
	int randFour = rand() % 4;
	return (Direction) randFour;

}

int Mon::randSteps(Time dt)
{
	srand((int)time(0)); // make these different?
	int randTen = rand() % 10;
	if (randTen >= 0 && randTen <= 3) return randTen;
	else if (randTen == 5) return 1;
	else if (randTen == 6) return 2;
	else return 0;
}