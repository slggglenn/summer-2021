#pragma once

#include "Test.h"
#include <map>
using namespace std;

#define NUM_SPRITES (42)
#define SPRITE_SIDE_LEN (26)
#define NUM_IDLE (16)
#define NUM_IDLE_ANIM_SPRITES (NUM_IDLE / 8)
#define NUM_WALK (24)
#define NUM_WALK_ANIM_SPRITES (NUM_WALK / 8)
#define NUM_SLEEP (2)
#define IDLE_START_X (73)
#define IDLE_START_Y (29)
#define MOVE_START_X (143)
#define MOVE_START_Y (38)
#define SLEEP_START_X (8)
#define SLEEP_START_Y (23)

class Animation
{
private:
	Texture texture_;
	Image textBack_; // updated to hold masked spritesheet
	Sprite sprite_;

	Sprite idle_[NUM_IDLE];
	Sprite moving_[NUM_WALK];
	Sprite asleep_[NUM_SLEEP];
	

public:
	Animation();
	void setTexture(const std::string imgPath);
	Texture getTexture();

	void updateIdle();
	void updateMoving();
	void updateAsleep();

	Sprite getSprite();
	void updateSprite(State state, Direction dir);
	void playAnim(Direction dir, State sta);
};