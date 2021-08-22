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
    initialize_spriteMap(); // reference
   // makeHitboxes();
}


int* Scene::getNumObj() { return numObj;  }

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

// functino to give obj type, switch to randomly generate number of them --> store in map
// 
// or map initialization randomly gens obj numbs --> stores
// during draw, creates sprite and initializes and draws (can go through in layers so no unwanted overlapping)

void Scene::initialize_spriteMap() // start with 0
{
    srand(time(0));
    int index = 0;
    for (unsigned int i = 0; i < 2; i++) // 2 is # of Object types
    {
        OBJECT curr = (OBJECT)i;
        int num;
        
        switch (curr)
        {
        case TREE:
            num = (rand() % 20) + 10;
            if (num > 20) num = 20; // between 10-20 trees
            //std::cout << "tree: #: " << num << "pos: " << pos.x << ", " << pos.y << endl;
            break;
        case FLOWER:
            num = (rand() % 30) + 1;
           // std::cout << "flower: #: " << num << "pos: " << pos.x << ", " << pos.y << endl;
            break;
        default:
            num = 0;
            break;
        }
        
        for (int k = index; k < index + num; k++)
        {
            float r = rand() % 9; // update with TILE stuff!! float convo ok?
            float c = rand() % 13;
            Vector2f pos = Vector2f(c, r);
            std::cout << k << " pos: " << c << ", " << r << endl;
            spriteMap[k] = pos;
            numObj[i] = num;
        }
    }
}

Vector2f Scene::randomPos()
{
    srand(time(0));
    float r = rand() % 9; // update with TILE stuff!! float convo ok?
    float c = rand() % 13;
    return Vector2f(c * TILE_SIZE, r * TILE_SIZE); // i want it to generate position once and then never be called
}

std::map<int, Vector2f> Scene::get_spriteMap() { return spriteMap; }

// 4 - 13 (row * r) + col + 1)
// 0, 0, 0, 
//4 --> 12
//// r = 5, c = 4
//void Scene::makeForest(unsigned int startIndex) {
//   /* const unsigned int TREE_WIDTH = 43 * 5;
//    const unsigned int TREE_HEIGHT = 55 * 5;*/
//
//    srand(time(0));
//   //3% chance for tree, 1% flower
//
//    int currVertex = 0;
//    int index = startIndex;
//    int limit = NUM_OBJECT_SPRITES;
//
//    //((SCRN_H / TILE_SIZE) + TILE_SIZE)
//    //SCRN_W / TILE_SIZE
//    for (int r = 0; r < 9; r++) // 9
//    {
//        /*sprites[index].setTexture(ssTrans);
//        sprites[index].setScale(5, 5);
//        sprites[index].setTextureRect(IntRect(10, 1535, 43, 55));
//        sprites[index].setPosition(0, r * TILE_SIZE);
//        std::cout << "tree" << index << ", " << r << ", 0" << endl;
//        index++, limit--;*/
//
//        // random gen # of each thing... put in map?
//        // then when drawing, randomize location
//        for (int c = 0; c < 15; c++) // 15
//        {
//            if (limit)
//            {
//                unsigned int chance = (rand() % 100);
//                if (chance >= 1 && chance <= 2) {
//                    // flowers
//                    sprites[index] = 1;
//                    /*sprites[index].setTexture(ssTrans);
//                    sprites[index].setScale(5, 5);
//                    sprites[index].setTextureRect(IntRect(10, 1535, 43, 55));
//                    sprites[index].setPosition(c * TILE_SIZE, r * TILE_SIZE);*/
//                    index++, limit--;
//                    std::cout << "flower" << index << ", " << c << ", " << r << endl;
//                    //hitboxes[startIndex + (r * SCRN_W / TREE_WIDTH) + c] = { 0, 0, 33, 33 };
//                } 
//                else if (chance >= 3 && chance <= 6) {
//                    // trees
//                    sprites[index] = 2;
//                    /* sprites[index].setTexture(ssTrans);
//                     sprites[index].setScale(5, 5);
//                     sprites[index].setTextureRect(IntRect(95, 2420, 33, 33));
//                     sprites[index].setPosition(c * TILE_SIZE, r * TILE_SIZE);*/
//                     //hitboxes[startIndex + (r * SCRN_W / TREE_WIDTH) + c] = { 0, 0, 43, 55 };
//                    index++, limit--;
//                    std::cout << "tree" << index << ", " << c << ", " << r << endl;
//                }
//                else sprites[index] = 0;
//                }
//            }
//            
//        }
//    }
//
//    //while (limit)
//    //{
//    //    sprites[index].setTexture(ssTrans);
//    //    sprites[index].setColor(Color::Transparent);
//    //    //sprites[index].setTextureRect(IntRect(95, 2420, 33, 33));
//    //    index++, limit--;
//    //}
//}


//void Scene::makeSprites() {
//    for (unsigned int i = 0; i < NUM_OBJECT_SPRITES; i++)
//    {
//        sprites[i].setTexture(ssTrans);
//        sprites[i].setScale(5, 5);
//    }
//}
void Scene::makeSprite(OBJECT type, Vector2f pos, Sprite& sprite)
{
    sprite.setTexture(ssTrans);
    sprite.setScale(5, 5);
    switch (type)
    {
    case TREE:
        sprite.setTextureRect(IntRect(95, 2420, 33, 33));
        break;
    case FLOWER:
        sprite.setTextureRect(IntRect(10, 1535, 43, 55));
        break;
    }
    sprite.setPosition(pos);
}


//void Scene::makeHitboxes() {
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

//}

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

//VertexArray Scene::getForestLayer() { return forestLayer; }

Texture& Scene::getTexture() { return ssTrans; }

//Sprite* Scene::getSprites() { return sprites; }

//FloatRect* Scene::getHitboxes() { return hitboxes; }