
#include "Character.h"
#include "Player.h"

Player::Player(float new_x, float new_y, std::string text_loc) : Character(new_x, new_y, text_loc)
{
	Character::setTexture(text_loc);
	Character::setSprite();
	Character::updatePosition(new_x, new_y);
};