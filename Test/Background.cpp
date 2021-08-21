#include "Background.h"
#include "Character.h"
#include "Mon.h"
#include <iostream>
#include <math.h>
using namespace std;

Scene::Scene() {
    if (!spritesheet.loadFromFile("graphics/SPRITESHEET.png")) std::cout << "ERROR" << std::endl;
    spritesheet.createMaskFromColor(Color::White, 0);
    ssTrans.loadFromImage(spritesheet);
    makeBackground(background);
   // makeSprites();
    makeForest(0);
   // makeHitboxes();
}

void Scene::makeBackground(VertexArray &background) {
    background.setPrimitiveType(Quads);
    background.resize(((SCRN_H / TILE_SIZE) + TILE_SIZE) * (SCRN_W / TILE_SIZE) * 4);

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


// 4 - 13 (row * r) + col + 1)
// 0, 0, 0, 
//4 --> 12
// r = 5, c = 4
void Scene::makeForest(unsigned int startIndex) {
   /* const unsigned int TREE_WIDTH = 43 * 5;
    const unsigned int TREE_HEIGHT = 55 * 5;*/

    srand(time(0));
   //3% chance for tree, 1% flower

    int currVertex = 0;
    int index = startIndex;

    for (unsigned int r = 0; r < ((SCRN_H / TILE_SIZE) + TILE_SIZE); r++)
    {
        for (unsigned int c = 0; c < SCRN_W / TILE_SIZE; c++)
        {

            unsigned int chance = (rand() % 3);
            switch (chance) {
            case 1: // flowers
                sprites[index].setTexture(ssTrans);
                sprites[index].setScale(5, 5);
                sprites[index].setTextureRect(IntRect(10, 1535, 43, 55));
                sprites[index].setPosition(r * TILE_SIZE, c * TILE_SIZE);
                index++;
                //hitboxes[startIndex + (r * SCRN_W / TREE_WIDTH) + c] = { 0, 0, 33, 33 };
                break;
            case 2: // trees
                break;
            case 3:
           // case 4:
                sprites[index].setTexture(ssTrans);
                sprites[index].setScale(5, 5);
                sprites[index].setTextureRect(IntRect(95, 2420, 33, 33));
                sprites[index].setPosition(r * TILE_SIZE, c * TILE_SIZE);
                index++;
                //hitboxes[startIndex + (r * SCRN_W / TREE_WIDTH) + c] = { 0, 0, 43, 55 };
                break;
            default:
                break;
            }
        }
    }

    //for (unsigned int c = 0; c < SCRN_W / TREE_WIDTH; c++) {

    //    for (unsigned int r = 0; r < SCRN_H / TREE_HEIGHT; r++) {
    //        background[currVertex].position = Vector2f(c * TREE_WIDTH, r * TREE_HEIGHT);
    //        background[currVertex + 1].position = Vector2f((c * TREE_WIDTH) + TREE_WIDTH, r * TREE_HEIGHT);
    //        background[currVertex + 2].position = Vector2f((c * TREE_WIDTH) + TREE_WIDTH, (r * TREE_HEIGHT) + TREE_HEIGHT);
    //        background[currVertex + 3].position = Vector2f(c * TREE_WIDTH, (r * TREE_HEIGHT) + TREE_HEIGHT);

    //        unsigned int chance = (rand() % 100) + 1;
    //        switch (chance) {
    //        case 1: // flowers
    //            background[currVertex].texCoords = Vector2f(95, 2420);
    //            background[currVertex + 1].texCoords = Vector2f(128, 2420);
    //            background[currVertex + 2].texCoords = Vector2f(128, 2453);
    //            background[currVertex + 3].texCoords = Vector2f(95, 2453);
    //            //hitboxes[startIndex + (r * SCRN_W / TREE_WIDTH) + c] = { 0, 0, 33, 33 };
    //            break;
    //        case 2: // trees
    //        case 3:
    //        case 4:
    //            background[currVertex].texCoords = Vector2f(10, 1535);
    //            background[currVertex + 1].texCoords = Vector2f(53, 1535);
    //            background[currVertex + 2].texCoords = Vector2f(53, 1590);
    //            background[currVertex + 3].texCoords = Vector2f(10, 1590);
    //            //hitboxes[startIndex + (r * SCRN_W / TREE_WIDTH) + c] = { 0, 0, 43, 55 };
    //            break;
    //        default:
    //            break;
    //        }

    //        currVertex += 4; // incrementing for # of vertices in quad
    //    }
    //}
}


//void Scene::makeSprites() {
//    for (unsigned int i = 0; i < NUM_OBJECT_SPRITES; i++)
//    {
//        sprites[i].setTexture(ssTrans);
//        sprites[i].setScale(5, 5);
//    }
//}

void Scene::makeHitboxes() {
    // initial positions must be 0 so that they'll overlap when getTransform called ater
  //  hitboxes[TREE_INDEX] = { 0, 0, 43, 55 };
   // hitboxes[SAPLING_INDEX] = { 0, 0, 20, 37 };
  //  hitboxes[GRASS_INDEX] = { 0, 0, 19, 18 };
  // // hitboxes[MUSHROOM_INDEX] = { 0, 0, 16, 17 };
  //  hitboxes[BUSH_INDEX] = { 0, 0, 18, 15 };
  ////  hitboxes[FRUIT_INDEX] = { 0, 0, 34, 27 };
  // // hitboxes[SPROUT_INDEX] = { 0, 0, 16, 14 };
  //  hitboxes[FLOWERS_INDEX] = { 0, 0, 33, 33 };
    /*hitboxes[lWINDOW_INDEX] = { 0, 0, 1, 1080 };
    hitboxes[rWINDOW_INDEX] = { 0, 0, 1, 1080 };
    hitboxes[uWINDOW_INDEX] = { 0, 0, 1920, 1 };
    hitboxes[bWINDOW_INDEX] = { 0, 0, 1920, 1 };*/

  //  reps[TREE_INDEX].setSize(Vector2f(43 * 6, 55 * 6 ));
 //   reps[SAPLING_INDEX].setSize(Vector2f(20 * 6, 37 * 6));
   // reps[GRASS_INDEX].setSize(Vector2f(19 * 6, 18 * 6));
   //// reps[MUSHROOM_INDEX].setSize(Vector2f(16 * 6, 17 * 6));
   // reps[BUSH_INDEX].setSize(Vector2f(18 * 6, 15 * 6));
   // //reps[FRUIT_INDEX].setSize(Vector2f(34 * 6, 27 * 6));
   ///// reps[SPROUT_INDEX].setSize(Vector2f(16 * 6, 14 * 6));
   // reps[FLOWERS_INDEX].setSize(Vector2f(33 * 6, 33 * 6));
    /*reps[lWINDOW_INDEX].setSize(Vector2f(20, 1080));
    reps[rWINDOW_INDEX].setSize(Vector2f(20, 1080));
    reps[uWINDOW_INDEX].setSize(Vector2f(1920, 20));
    reps[bWINDOW_INDEX].setSize(Vector2f(1920, 20));*/

    // up until window stuff
    //for (unsigned int i = 0; i < NUM_OBJECT_SPRITES; i++) {
    //    //sprites[i].getTransform().transformRect(hitboxes[i]);
    //    reps[i].setFillColor(Color(101, 5, 56, 70));
    //    reps[i].setPosition(Vector2f(sprites[i].getPosition().x, sprites[i].getPosition().y));
    //    /*if (i == rWINDOW_INDEX) reps[i].setPosition(Vector2f(sprites[i].getPosition().x + ))*/
    //}

}

//bool Scene::checkCollisions(Mon mon)
//{
//    //Sprite possibleCollisions[NUM_OBJECT_SPRITES]; // use this later
//    for (unsigned int i = 0; i < NUM_OBJECT_SPRITES; i++)
//    {
//        if (mon.willCollide(sprites[i], hitboxes[i])) // something added with this loop or implementation in Test.cpp that caused opengl
//        {
//          //  reps[i].setFillColor(Color(201, 114, 144, 40));
//            return true; // what if multiple collisions? only first returned
//          //  possibleCollisions[i] = sprites[i];
//        }
//        else {
//           // reps[i].setFillColor(Color(2, 207, 188, 40));
//            return false;
//        }
//    }
//
//    // get mon's position
//    // loop through sprites to see if sprite position within radius of mon's next move
//    // for each one that is, check to see if HB will intersect
//    // if any potential collision, false
//}

VertexArray Scene::getBackground() { return background; }

VertexArray Scene::getForestLayer() { return forestLayer; }

Texture& Scene::getTexture() { return ssTrans; }

Sprite* Scene::getSprites() { return sprites; }

//FloatRect* Scene::getHitboxes() { return hitboxes; }

RectangleShape* Scene::getReps() { return reps; }