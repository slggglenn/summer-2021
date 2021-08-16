#include "Character.h"
#include "Player.h"

Player::Player(float new_x, float new_y, std::string text_loc) : Character(new_x, new_y, text_loc)
{
	Character::setTexture(text_loc);
	Character::setSprite();
	Character::updatePosition(new_x, new_y);
};

Vector2f Player::getPosition()
{
	return position_;
}


//void Player::movePlayer(Time dt)
//{
//	
//	if (Player::getOrientation() == LEFT)
//	{
//		(Character::getSprite()).move(dt, -1.f, 0.f);// -= dt.asSeconds() * Player::getSpeed();
//	}
//	if (Player::getOrientation() == RIGHT)
//	{
//		position_.x += dt.asSeconds() * Player::getSpeed();
//	}
//	if (Player::getOrientation() == UP)
//	{
//		position_.y -= dt.asSeconds() * Player::getSpeed();
//	}
//	if (Player::getOrientation() == DOWN)
//	{
//		position_.y += dt.asSeconds() * Player::getSpeed();
//	}
//
//	// moves shape representation to that location
//	Player::getSprite().setPosition(position_);
//}
//
//void Player::updatePlayer(Time dt)
//{
//	if (Keyboard::isKeyPressed(Keyboard::Left))
//	{
//		setOrientation(LEFT);
//	}
//
//	if (Keyboard::isKeyPressed(Keyboard::Right))
//	{
//		setOrientation(RIGHT);
//	}
//
//	if (Keyboard::isKeyPressed(Keyboard::Up))
//	{
//		setOrientation(UP);
//	}
//
//	if (Keyboard::isKeyPressed(Keyboard::Down))
//	{
//		setOrientation(DOWN);
//	}
//}