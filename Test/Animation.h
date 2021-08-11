#pragma once

#include "Test.h"

#define NUM_SPRITES (42)
#define SPRITE_SIDE_LEN (26) // 22 b4
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
	//Sprite spritesArray[NUM_SPRITES]; // get rid!!
	Texture texture_;
	std::string imgRef_;
	Sprite sprite_;
	//Sprite spritesheet_;
	Image textBack_; // updated to hold masked spritesheet
	// stores sequence of sprites for each animation,
	// paired with keys for state and direction
	std::map<std::pair<State, Direction>, Sprite> animSprites_;
	Direction orientation_ = DOWN;
	Vector2f direction_; //driectionVect
	//Vector2f direction = { 0, 0 };

	// load 1 texture for ALL animation sprites
	// divide into temporary srites based on state and direction
	// when playing animation, divide temp sprites into individuals and loop
	// 
	// play() method (1 unique for player based on key pressed) + default idle... or maybe based on states altogether


public:
	Animation();
	void setTexture();
	Texture getTexture();

	void setOrientation(Direction new_orient);
	Direction getOrientation();
	//Direction* setmovementMatrix(Direction x, Direction y);
	Vector2f getDirection();
	Vector2f updateDirection();
	Vector2f zeroDirection();

	//void setSprite();
	//Sprite getSprite();
	//FloatRect getSpriteBounds(); // migt need??
	//Sprite* setspritesArray();
	void set_animSprites();
	void updateIdleSprite();
	//unsigned int* getAnimIndeces(Direction dir, bool moving);
	void playAnim(Direction dir, bool moving);
};