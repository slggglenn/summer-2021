#pragma once
#include "Test.h"
#include "Character.h"
#include "Mon.h"
#include <iostream>

//#define TREE_INDEX (0)
#define GRASS_INDEX (0)
//#define MUSHROOM_INDEX (1)
//#define BUSH_INDEX (1)
//#define FRUIT_INDEX (3)
//#define SPROUT_INDEX (4)
//#define FLOWERS_INDEX (2)
//#define rWINDOW_INDEX (8)
//#define lWINDOW_INDEX (9)
//#define uWINDOW_INDEX (10)
//#define bWINDOW_INDEX (11)
//#define SAPLING_INDEX (6)
//#define TREE1_INDEX (8)
//#define TREE2_INDEX (9)
//#define TREE3_INDEX (10)
//#define TREE4_INDEX (11)
//#define TREE5_INDEX (3)
#define NUM_OBJECT_SPRITES (20) // +4 trees
#define NUM_OBJ_TYPES (6)
#define TREE_INDEX (5)

enum OBJECT { FLOWER, MUSHROOM, SPROUT, BUSH, SAPLING, TREE }; // organized in terms of priority drawn (why is tree first??)

class Scene
{
private:
	VertexArray background, forestLayer;
	Texture ssTrans; // transparent texture; loaded from spritesheet
	Image spritesheet; // get rid of flower hitbox
	Sprite sprites[NUM_OBJECT_SPRITES]; // somehow associate index number with what type of obj they are
	//std::map<int, Vector2f> treeMap;
	std::map<std::pair<OBJECT, int>, Vector2f> spriteMap;
	int numObj[NUM_OBJ_TYPES];
	//FloatRect hitboxes[NUM_OBJECT_SPRITES];

public:
	Scene();
	int* getNumObj();
	void makeBackground(VertexArray& background);
	//void makeForest(unsigned int startIndex);
	//void makeSprites();
	//void makeHitboxes();
	VertexArray getBackground();
	//VertexArray getForestLayer();
	Texture& getTexture();
	std::map<std::pair<OBJECT, int>, Vector2f> get_spriteMap();
	Vector2f randomPos();
	void makeSprite(OBJECT type, Vector2f pos, Sprite &sprite);
	//Sprite* getSprites();
	int initializeSubtype(OBJECT type, int num, int rMax, int cMax, int percentMax, int randNum); // use for tree?
	void initialize_spriteMap();
	bool isNearby(int x, int y, OBJECT* obj);
	//void initialize_treeMap();
	//std::map<int, Vector2f> get_treeMap();
	/*FloatRect* getHitboxes();
	bool checkCollisions(Mon mon);*/
};