#pragma once
#include "Test.h"
#include "Character.h"
#include "Mon.h"
#include <iostream>

#define NUM_OBJ_TYPES (6)

enum OBJECT { FLOWER, MUSHROOM, SPROUT, BUSH, SAPLING, TREE }; // organized in terms of priority drawn

class Scene
{
private:
	VertexArray background;
	Image spritesheet;
	Texture transSS; // transparent texture; loaded from spritesheet
	
	int numObj[NUM_OBJ_TYPES]; // number of each obj; index is enum val
	std::map<std::pair<OBJECT, int>, Sprite> spriteMap;
	std::map<std::pair<OBJECT, int>, FloatRect> hitboxMap;
	std::map<std::pair<OBJECT, int>, RectangleShape> reps; // TEMP //

public:
	Scene();

	void makeBackground(VertexArray& background);
	void initialize_spriteMap();
	void makeSprite(OBJECT type, Vector2f pos, Sprite& sprite);
	void makeHitboxes();

	bool isNearby(int x, int y, OBJECT* nearby);
	
	VertexArray getBackground();
	int* getNumObj();
	Texture& getTexture();
	std::map<std::pair<OBJECT, int>, Sprite> get_spriteMap();
	std::map<std::pair<OBJECT, int>, FloatRect> get_hitboxMap();
	std::map<std::pair<OBJECT, int>, RectangleShape> get_Reps();
};