
#include "Character.h"
#include "Player.h"

Player::Player(float new_x, float new_y, std::string text_loc) : Character(new_x, new_y, text_loc)
{
	//Character::getAnimation().setTexture(text_loc); // NOT A CAUSE OF ERROR
	//Character::getAnimation().updateIdleSprite(; // UPDATE TO SET SPRITE
	//Character::updatePosition(new_x, new_y);
	tempSetup(text_loc);
	temp_position.x = new_x;
	temp_position.y = new_y;
};

void Player::tempSetup(std::string text_loc)
{
	temp.loadFromFile(text_loc);
	temp_sprite.setTexture(temp);
}

Sprite Player::getTempSprite()
{
	return temp_sprite;
}

//Vector2f Player::getPosition()
//{
//	return position_;
//}

// updates direction vector based on key presses
void Player::updateDirection()
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) // more cases for iskeyheld stuff...should update state
	{
		setOrientation(LEFT);
		Character::set_directionVect(-1.00, Character::get_directionVect().y);
	}

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		setOrientation(RIGHT);
		Character::set_directionVect(1.00, Character::get_directionVect().y);
	}

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		setOrientation(UP);
		Character::set_directionVect(Character::get_directionVect().x, -1.00);
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		setOrientation(DOWN);
		Character::set_directionVect(Character::get_directionVect().x, 1.00);
	}
}