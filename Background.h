#pragma once
#include "Test.h"
#include "Character.h"
#include "Mon.h"
#include <iostream>

#define NUM_OBJECT_SPRITES (20) // +4 trees
#define NUM_OBJ_TYPES (6)

enum OBJECT { FLOWER, MUSHROOM, SPROUT, BUSH, SAPLING, TREE }; // organized in terms of priority drawn (why is tree first??)
// NONE is temp!!
class Scene
{
private:
	VertexArray background, forestLayer;
	Texture ssTrans; // transparent texture; loaded from spritesheet
	Image spritesheet; // get rid of flower hitbox
	//Sprite sprites[NUM_OBJECT_SPRITES]; // somehow associate index number with what type of obj they are
	std::map<std::pair<OBJECT, int>, Sprite> spriteMap;
	int numObj[NUM_OBJ_TYPES];
	FloatRect hitboxes[NUM_OBJ_TYPES];
	std::map<std::pair<OBJECT, int>, FloatRect> hitboxMap;
	std::map<std::pair<OBJECT, int>, RectangleShape> reps;

public:
	Scene();
	int* getNumObj();
	void makeBackground(VertexArray& background);
	//void makeForest(unsigned int startIndex);
	void makeHitboxes();
	VertexArray getBackground();
	//VertexArray getForestLayer();
	Texture& getTexture();
	std::map<std::pair<OBJECT, int>, Sprite> get_spriteMap();
	void makeSprite(OBJECT type, Vector2f pos, Sprite& sprite);
	void initialize_spriteMap();
	bool isNearby(int x, int y, OBJECT* nearby);
	std::map<std::pair<OBJECT, int>, FloatRect> get_hitboxMap();
	//bool checkCollisions(Mon mon);
	std::map<std::pair<OBJECT, int>, RectangleShape> get_Reps();
};


// TODO
// spritemap --> map of sprites
// hitbox implementation
// debug collisions

// add a couple of random events and extra mons
// maybe different backgrounds?
// music