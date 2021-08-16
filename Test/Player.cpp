
#include "Character.h"
#include "Player.h"

Player::Player(float new_x, float new_y) : Character(new_x, new_y, text_loc)
{
	//Character::getAnimation().setTexture(text_loc);
};

// updates orientation_ and direction vector based on key presses
void Player::updateDirection()
{
	if (Keyboard::isKeyPressed(Keyboard::Left) && (Keyboard::isKeyPressed(Keyboard::Up)))
	{
		setOrientation(LEFT_UP);
		Character::set_directionVect(-1.00, -1.00);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && (Keyboard::isKeyPressed(Keyboard::Down)))
	{
		setOrientation(LEFT_DOWN);
		Character::set_directionVect(-1.00, 1.00);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		setOrientation(LEFT);
		Character::set_directionVect(-1.00, Character::get_directionVect().y);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && (Keyboard::isKeyPressed(Keyboard::Down)))
	{
		setOrientation(RIGHT_DOWN);
		Character::set_directionVect(1.00, 1.00);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && (Keyboard::isKeyPressed(Keyboard::Up)))
	{
		setOrientation(RIGHT_UP);
		Character::set_directionVect(1.00, -1.00);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		setOrientation(RIGHT);
		Character::set_directionVect(1.00, Character::get_directionVect().y);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		setOrientation(UP);
		Character::set_directionVect(Character::get_directionVect().x, -1.00);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		setOrientation(DOWN);
		Character::set_directionVect(Character::get_directionVect().x, 1.00);
	}
}