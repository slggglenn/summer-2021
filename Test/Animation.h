#pragma once

#include "Test.h"

#define NUM_SPRITES (42)
#define SPRITE_SIDE_LEN (26) // 22 b4
#define NUM_IDLE (16)
#define NUM_WALK (24)
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
	Sprite spritesArray[NUM_SPRITES];
	Texture texture_;
	Sprite sprite_;
	Image textBack_;
	// load 1 texture for ALL animation sprites
	// put into vertex array
	// store indeces for diff animations
	// play() method (1 unique for player based on key pressed) + default idle... or maybe based on states altogether


public:
	Animation(std::string img_ref);
	void setTexture(std::string img_ref);
	Texture getTexture();
	//void setSprite();
	Sprite getSprite();
	FloatRect getSpriteBounds();
	Sprite* setspritesArray();
	unsigned int* getAnimIndeces(Direction dir, bool moving);
	void playAnim(Direction dir, bool moving);
};