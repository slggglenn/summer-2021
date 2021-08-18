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
#define NUM_OBJECT_SPRITES (8)

class Scene
{
private:
	VertexArray background;
	Texture ssTrans;
	Image spritesheet;
	Sprite sprites[NUM_OBJECT_SPRITES]; // somehow associate index number with what type of obj they are
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
	bool checkCollisions(Mon mon, Time dt);
	RectangleShape* getReps();
};