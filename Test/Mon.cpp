#include "Character.h"
#include "Mon.h"
#include <iostream>

// constructor
Mon::Mon(float new_x, float new_y, std::string text_loc) : Character(new_x, new_y, text_loc)
{
	Character::setTexture(text_loc);
	Character::setSprite();
	Character::updatePosition(new_x, new_y);
	state_ = IDLE;
	stepCounter_ = 0;
	hitbox_ = { 3, 3, 18, 18 }; // how to set location and ave follow?
	getGlobalHitbox(); // sets hitbox to sprite location
	updateHitbox();
	rep.setSize(Vector2f(18 * 6, 18 * 6));
	rep.setFillColor(Color(2, 207, 188, 40));
	updateRep();

};


void Mon::updateRep()
{
	rep.setPosition(Character::getSprite().getPosition());
}

void Mon::updateHitbox()
{
	hitbox_.left = Character::getSprite().getGlobalBounds().left;
	hitbox_.top = Character::getSprite().getGlobalBounds().top;
}

RectangleShape Mon::getRep() {
	return rep;
}

FloatRect Mon::getGlobalHitbox()
{
	return Character::getSprite().getTransform().transformRect(hitbox_);
}

bool Mon::willCollide(Sprite obj, FloatRect objHB)
{
	return (getGlobalHitbox().intersects(obj.getTransform().transformRect(objHB))); //something about this isn't working
	/*{
		rep.setFillColor(Color(201, 114, 144, 40));
		std::cout << "collision!";
		return true;
	}
	else
	{
		rep.setFillColor(Color(2, 207, 188, 40));
		return false;
	}*/
	/*Character::updatePosition(Character::getPosition().x - dt.asSeconds() * Character::getSpeed() * Character::getDirection().x,
		Character::getPosition().y - dt.asSeconds() * Character::getSpeed() * Character::getDirection().y);*/
	// resets with our update (eevee.getSprite()) command in main none the wiser
}


unsigned int Mon::get_stepCounter()
{
	return stepCounter_;
}

void Mon::set_stepCounter(unsigned int steps)
{
	stepCounter_ = steps;
}

void Mon::setState(State state)
{
	state_ = state;
}

State Mon::getState()
{
	return state_;
}

Direction Mon::randDir(Time dt)
{
	srand((int) time(0));
	int randFour = rand() % 2; // 4
	if (!randFour) return UP;
	else return DOWN;
	//return UP;
	//return (Direction) randFour;
}

int Mon::randSteps(Time dt)
{
	srand((int)time(0)); // make these different?
	int randTen = rand() % 50; // 0-49
	state_ = MOVING;
	if (randTen > 0 && randTen <= 5) {
		stepCounter_ = 2;
		return 2;
	}
	else if (randTen > 5 && randTen <= 7) {
		stepCounter_ = 1;
		return 1;
	}
	else if (randTen == 8) {
		stepCounter_ = 3;
		return 3;
	}
	else {
		stepCounter_ = 0;
		state_ = IDLE;
		return 0;
	}
}

// getTransform().transformRect(m_hitbox);
//const bool colliding = player.getGlobalHitbox().intersects(enemy.getGlobalHitbox());