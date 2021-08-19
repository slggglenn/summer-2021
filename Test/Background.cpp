#include "Background.h"
#include "Character.h"
#include "Mon.h"
#include <iostream>
using namespace std;

Scene::Scene() {
    if (!spritesheet.loadFromFile("graphics/SPRITESHEET.png")) std::cout << "ERROR" << std::endl;
    spritesheet.createMaskFromColor(Color::White, 0);
    ssTrans.loadFromImage(spritesheet);
    makeBackground(background);
    makeSprites();
    makeHitboxes();
}

void Scene::makeBackground(VertexArray &background) {
    background.setPrimitiveType(Quads);
    background.resize(((SCRN_H / TILE_SIZE) + TILE_SIZE) * (SCRN_W / TILE_SIZE) * TILE_TYPES);

    int currVertex = 0;
    for (unsigned int c = 0; c < SCRN_W / TILE_SIZE; c++) {

        for (unsigned int r = 0; r < (SCRN_H / TILE_SIZE) + TILE_SIZE; r++) {
            background[currVertex].position = Vector2f(c * TILE_SIZE, r * TILE_SIZE);
            background[currVertex + 1].position = Vector2f((c * TILE_SIZE) + TILE_SIZE, r * TILE_SIZE);
            background[currVertex + 2].position = Vector2f((c * TILE_SIZE) + TILE_SIZE, (r * TILE_SIZE) + TILE_SIZE);
            background[currVertex + 3].position = Vector2f(c * TILE_SIZE, (r * TILE_SIZE) + TILE_SIZE);

            background[currVertex].texCoords = Vector2f(96, 2230);
            background[currVertex + 1].texCoords = Vector2f(128, 2230);
            background[currVertex + 2].texCoords = Vector2f(128, 2262);
            background[currVertex + 3].texCoords = Vector2f(96, 2262);

            currVertex += 4; // incrementing for # of vertices in quad
        }
    }
}

void Scene::makeSprites() {
    Sprite tree, sapling, grass, mushroom, bush, fruit, sprout, flowers;
    for (unsigned int i = 0; i < NUM_OBJECT_SPRITES; i++)
    {
        sprites[i].setTexture(ssTrans);
        sprites[i].setScale(6, 6);
    }

    // initializes properties:
    sprites[TREE_INDEX].setTextureRect(IntRect(10, 1535, 43, 55));
    sprites[TREE_INDEX].setTextureRect(IntRect(10, 1535, 43, 55));
    sprites[TREE_INDEX].setTextureRect(IntRect(10, 1535, 43, 55));
    sprites[TREE_INDEX].setTextureRect(IntRect(10, 1535, 43, 55));
    sprites[TREE_INDEX].setTextureRect(IntRect(10, 1535, 43, 55));
    sprites[TREE_INDEX].setTextureRect(IntRect(10, 1535, 43, 55));


    sprites[SAPLING_INDEX].setTextureRect(IntRect(70, 1553, 20, 37));
    sprites[GRASS_INDEX].setTextureRect(IntRect(199, 2236, 19, 18));
    sprites[MUSHROOM_INDEX].setTextureRect(IntRect(40, 2301, 16, 17));
    sprites[BUSH_INDEX].setTextureRect(IntRect(106, 6998, 18, 15));
    sprites[FRUIT_INDEX].setTextureRect(IntRect(159, 1557, 34, 27));
    sprites[SPROUT_INDEX].setTextureRect(IntRect(135, 2847, 16, 14));
    sprites[FLOWERS_INDEX].setTextureRect(IntRect(95, 2420, 33, 33));

    sprites[TREE_INDEX].setPosition((SCRN_W * 2 / 3) + 40, (SCRN_H / 4) + 50);
    sprites[SAPLING_INDEX].setPosition(SCRN_W * 3 / 5, (SCRN_H / 4) + 20);
    sprites[GRASS_INDEX].setPosition(SCRN_W / 3, SCRN_H / 3);
    sprites[MUSHROOM_INDEX].setPosition(5 * SCRN_W / 6, 2 * SCRN_H / 5);
    sprites[BUSH_INDEX].setPosition(SCRN_W / 2, 3 * SCRN_H / 4);
    sprites[FRUIT_INDEX].setPosition((SCRN_W * 2 / 3) + 80, (2 * SCRN_H / 7) + 70);
    sprites[SPROUT_INDEX].setPosition((SCRN_W * 3 / 5) + 100, (SCRN_H / 4) + 80);
    sprites[FLOWERS_INDEX].setPosition(SCRN_W / 3, SCRN_H / 7);
    sprites[lWINDOW_INDEX].setPosition(0, 0);
    sprites[rWINDOW_INDEX].setPosition(1900, 0);
    sprites[uWINDOW_INDEX].setPosition(0, 0);
    sprites[bWINDOW_INDEX].setPosition(0, 1060);
}

void Scene::makeHitboxes() {
    // initial positions must be 0 so that they'll overlap when getTransform called ater
    hitboxes[TREE_INDEX] = { 0, 0, 43, 55 };
    hitboxes[SAPLING_INDEX] = { 0, 0, 20, 37 };
    hitboxes[GRASS_INDEX] = { 0, 0, 19, 18 };
    hitboxes[MUSHROOM_INDEX] = { 0, 0, 16, 17 };
    hitboxes[BUSH_INDEX] = { 0, 0, 18, 15 };
    hitboxes[FRUIT_INDEX] = { 0, 0, 34, 27 };
    hitboxes[SPROUT_INDEX] = { 0, 0, 16, 14 };
    hitboxes[FLOWERS_INDEX] = { 0, 0, 33, 33 };
    hitboxes[lWINDOW_INDEX] = { 0, 0, 1, 1080 };
    hitboxes[rWINDOW_INDEX] = { 0, 0, 1, 1080 };
    hitboxes[uWINDOW_INDEX] = { 0, 0, 1920, 1 };
    hitboxes[bWINDOW_INDEX] = { 0, 0, 1920, 1 };

    reps[TREE_INDEX].setSize(Vector2f(43 * 6, 55 * 6 ));
    reps[SAPLING_INDEX].setSize(Vector2f(20 * 6, 37 * 6));
    reps[GRASS_INDEX].setSize(Vector2f(19 * 6, 18 * 6));
    reps[MUSHROOM_INDEX].setSize(Vector2f(16 * 6, 17 * 6));
    reps[BUSH_INDEX].setSize(Vector2f(18 * 6, 15 * 6));
    reps[FRUIT_INDEX].setSize(Vector2f(34 * 6, 27 * 6));
    reps[SPROUT_INDEX].setSize(Vector2f(16 * 6, 14 * 6));
    reps[FLOWERS_INDEX].setSize(Vector2f(33 * 6, 33 * 6));
    reps[lWINDOW_INDEX].setSize(Vector2f(20, 1080));
    reps[rWINDOW_INDEX].setSize(Vector2f(20, 1080));
    reps[uWINDOW_INDEX].setSize(Vector2f(1920, 20));
    reps[bWINDOW_INDEX].setSize(Vector2f(1920, 20));

    // up until window stuff
    for (unsigned int i = 0; i < NUM_OBJECT_SPRITES + 4; i++) {
        //sprites[i].getTransform().transformRect(hitboxes[i]);
        reps[i].setFillColor(Color(101, 5, 56, 70));
        reps[i].setPosition(Vector2f(sprites[i].getPosition().x, sprites[i].getPosition().y));
        /*if (i == rWINDOW_INDEX) reps[i].setPosition(Vector2f(sprites[i].getPosition().x + ))*/
    }


}

bool Scene::checkCollisions(Mon mon)
{
    //Sprite possibleCollisions[NUM_OBJECT_SPRITES]; // use this later
    for (unsigned int i = 0; i < NUM_OBJECT_SPRITES + 4; i++)
    {
        if (mon.willCollide(sprites[i], hitboxes[i])) // something added with this loop or implementation in Test.cpp that caused opengl
        {
            reps[i].setFillColor(Color(201, 114, 144, 40));
            return true; // what if multiple collisions? only first returned
          //  possibleCollisions[i] = sprites[i];
        }
        else {
            reps[i].setFillColor(Color(2, 207, 188, 40));
            return false;
        }
    }

    // get mon's position
    // loop through sprites to see if sprite position within radius of mon's next move
    // for each one that is, check to see if HB will intersect
    // if any potential collision, false
}

VertexArray Scene::getBackground() { return background; }

Texture& Scene::getTexture() { return ssTrans; }

Sprite* Scene::getSprites() { return sprites; }

FloatRect* Scene::getHitboxes() { return hitboxes; }

RectangleShape* Scene::getReps() { return reps; }