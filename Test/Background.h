#pragma once
#include "Test.h"
#include "Character.h"
#include "Mon.h"
#include <iostream>

#define TREE_INDEX (0)
#define SAPLING_INDEX (1)
#define GRASS_INDEX (2)
#define MUSHROOM_INDEX (3)
#define BUSH_INDEX (4)
#define FRUIT_INDEX (5)
#define SPROUT_INDEX (6)
#define FLOWERS_INDEX (7)
#define rWINDOW_INDEX (8)
#define lWINDOW_INDEX (9)
#define uWINDOW_INDEX (10)
#define bWINDOW_INDEX (11)
#define TREE1_INDEX (12)
#define TREE2_INDEX (13)
#define TREE3_INDEX (14)
#define TREE4_INDEX (15)
#define TREE5_INDEX (16)
#define NUM_OBJECT_SPRITES (13) // added 5 more trees!!

class Scene
{
private:
	VertexArray background;
	Texture ssTrans;
	Image spritesheet; // get rid of flower hitbox
	Sprite sprites[NUM_OBJECT_SPRITES + 4]; // somehow associate index number with what type of obj they are
	FloatRect hitboxes[NUM_OBJECT_SPRITES + 4];
	RectangleShape reps[NUM_OBJECT_SPRITES + 4];

public:
	Scene();
	void makeBackground(VertexArray& background);
	void makeSprites();
	void makeHitboxes();
	VertexArray getBackground();
	Texture& getTexture();
	Sprite* getSprites();
	FloatRect* getHitboxes();
	bool checkCollisions(Mon mon);
	RectangleShape* getReps();
};