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
    initialize_spriteMap();
    makeHitboxes();
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

//int Scene::initializeSubtype(OBJECT type, int num, int rMax, int cMax, int percentMax, int randNum)
//{
//    srand(randNum);
//    int count = 0;
//    for (int r = 0; r < rMax; r++) // 6, 9 always going to be misevenly distributed
//    {
//        for (int c = 0; c < cMax; c++) // lesss rows to get rid of overlap
//        {
//            int flow = (rand() % 99) + 1;
//
//            if (flow >= 1 && flow <= percentMax) // temp to figure out how many rows + cs needed
//            { // have rowcount instead ?? (implement for both)
//                if (count == num) break;
//                else {
//                    spriteMap[std::make_pair(type, count)].x = c * (TILE_SIZE + 20);
//                    spriteMap[std::make_pair(type, count)].y = r * (TILE_SIZE + 20);
//                    //std::cout << "flow: #: " << count << "pos: " << c << ", " << r << endl;
//                    count++;
//                }
//            }
//        }
//    }
//    return count;
//}



void Scene::initialize_spriteMap() // start with 0
{
    srand(time(0));
    //int randNums[NUM_OBJ_TYPES];
    //for (unsigned int j = 0; j < NUM_OBJ_TYPES; j++) // NEED TO EXCLUDE TREE!! WASTE TO INCLUDE
    //{
    //    randNums[j] = rand() % (j + 1) + 1;
    //} // better to generatet
    int percent[NUM_OBJ_TYPES - 1] = { 5, 7, 3, 4, 3, 9}; // WO FRUIT
    int densityBuffer[NUM_OBJ_TYPES - 1] = { 0,0,0,0,0,0 };
    int willPlaceObj = 0;

    for (int i = 0; i < NUM_OBJ_TYPES - 1; i++) // DON"T INCLUDE FRUIT
    {
        //std::cout << percent[i] << ", ";
        willPlaceObj += percent[i];
    }
   // cout << endl << endl;

    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 15; c++) // not enough columns so increased to 15.. check if offscreen stuff
        {// clause to check nearby to skip (tree overlap) or increase odds of obj (if more nearby)

            // if row = 0 --> can't check y - 1; if col = 0 --> can't check x - 1
            // if row = 8 --> can't check y + 1; if col = 14 --> can't check x + 1
            //Q: generates random first right?

            // mushrooms near trees and othermushrooms
            // saplings near trees and other saplings
            // flowers near each other
            int randObj = rand() % 99 + 1;
            if (randObj <= willPlaceObj)
            {
                // boost //
                // checks adj
               // OBJECT nearby = TREE;
                static OBJECT nearby = TREE; // just placeholder
                int xL, xR, yL, yR, mult;// 4 potential adjacents for a tile
                xL = c - 1;
                xR = c + 1;
                yL = r - 1;
                yR = r + 1;

                int adjCoords[8][2] = { {xL, yL}, {xL, r}, {xL, yL}, {c, yL}, {xR, yL}, {xR, r}, {xR, yR}, {c, yR} };

                // more efficient way to trigger nearby updates
                for (unsigned int i = 0; i < 8; i++)
                {
                    if ((OBJECT)i == SAPLING) continue;

                    if (isNearby(adjCoords[i][0], adjCoords[i][1], &nearby)) densityBuffer[(int)nearby] += 1;
                    else if (adjCoords[i][0] && adjCoords[i][1] && !isNearby(adjCoords[i][0], adjCoords[i][1], &nearby))
                    {
                        if (densityBuffer[(int)nearby]) densityBuffer[(int)nearby] -= 1; // decreases is none around
                        // for flower 
                    }
                    
                }

                OBJECT currType;
                int fP, mP, spP, bP, saP, tP, frP;
                fP = percent[(int)FLOWER] + densityBuffer[(int)FLOWER];
                mP = percent[(int)MUSHROOM] + densityBuffer[(int)MUSHROOM];
                spP = percent[(int)SPROUT] + densityBuffer[(int)SPROUT];
                bP = percent[(int)BUSH] + densityBuffer[(int)BUSH];
                saP = percent[(int)SAPLING];
                tP = percent[(int)TREE] + densityBuffer[(int)TREE];

                if (randObj <= fP) currType = FLOWER;
                else if (randObj > fP && randObj <= fP + mP) currType = MUSHROOM;
                else if (randObj > fP + mP && randObj <= fP + mP + spP) currType = SPROUT;
                else if (randObj > fP + mP + spP && randObj <= fP + mP + spP + bP) currType = BUSH;
                else if (randObj > fP + mP + spP + bP && randObj <= fP + mP + spP + bP + saP) currType = SAPLING;
                else if (randObj > fP + mP + spP + bP + saP && randObj <= fP + mP + spP + bP + saP + tP)
                {
                    currType = TREE;

                    // random chance of having fruit
                    int hasFruit = rand() % - 1;
                    if (hasFruit)
                    {
                        makeSprite(FRUIT, Vector2f(c * TILE_SIZE, r * TILE_SIZE), spriteMap[std::make_pair(FRUIT, numObj[(int)FRUIT])]); // makes fruit
                        (numObj[(int)FRUIT])++;
                    }
                }
                
                
                makeSprite(currType, Vector2f(c * TILE_SIZE, r * TILE_SIZE), spriteMap[std::make_pair(currType, numObj[(int)currType])]); // start at 0, then you increment as index
                //spriteMap[std::make_pair(currType, numObj[(int)currType])].y = r * TILE_SIZE;
                (numObj[(int)currType])++;
            }
        }
    }
}


// https://stackoverflow.com/questions/28690526/c-how-to-pass-an-uninitialized-pointer-to-a-function
bool Scene::isNearby(int x, int y, OBJECT* nearby)
{
    if (!x || !y) return false;

    for (int i = 0; i < NUM_OBJ_TYPES - 1; i++) // excludes fruit
    {
        for (int j = 0; j < numObj[i]; j++)
        {
            if (spriteMap[std::make_pair((OBJECT)i, j)].getPosition().x / TILE_SIZE == x &&
                spriteMap[std::make_pair((OBJECT)i, j)].getPosition().y / TILE_SIZE == y)
                {// idk if this'll work for tree
                    (*nearby) = (OBJECT)i;
                    return true; // will this break??
                }
        }
    }
    return false;
}


void Scene::makeSprite(OBJECT type, Vector2f pos, Sprite& sprite)
{
    sprite.setTexture(ssTrans);
    sprite.setScale(5, 5);
    switch (type)
    {
    case TREE:
        //if (modified) sprite.setTextureRect(IntRect(10, 1535, 43, 55)); differet
        //else
        sprite.setTextureRect(IntRect(10, 1535, 43, 55));
        break;
    case FLOWER:
        //if (modified) sprite.setTextureRect(IntRect(105, 2462, 17, 16)); // change hitbox! if nec 
       // else 
        sprite.setTextureRect(IntRect(95, 2420, 33, 33));
        sprite.setScale(4, 4); // necessary, but tech redundant
        break;
    case MUSHROOM:
        sprite.setTextureRect(IntRect(40, 2301, 16, 17));
        break;
    case SPROUT:
        sprite.setTextureRect(IntRect(135, 2847, 16, 14));
        break;
    case SAPLING:
        sprite.setTextureRect(IntRect(70, 1553, 20, 37));
        break;
    case BUSH:
        sprite.setTextureRect(IntRect(106, 6998, 18, 15));
        sprite.setScale(6, 6);
        break;
    case FRUIT:
        // determines fruit color
        srand(time(0));
        int isBlue = rand() % 2;
        if (isBlue) sprite.setTextureRect(IntRect(160, 1557, 33, 24));
        else sprite.setTextureRect(IntRect(160, 1526, 33, 24));
        break;
    }
    sprite.setPosition(pos);
}


void Scene::makeHitboxes() {


    for (int i = (int)BUSH; i < NUM_OBJ_TYPES - 1; i++)
    {
        for (int j = 0; j < numObj[i]; j++)
        {
            int objWidth, objHeight;

            objWidth = 10;

            switch (i)
            {
            case TREE:
                objWidth = 43;
                objHeight = 55;
                break;
            case SAPLING:
                objWidth = 20;
                objHeight = 37;
                break;
            case BUSH:
                objWidth = 18;
                objHeight = 15;
                break;
            }
            hitboxMap[std::make_pair((OBJECT)i, j)].left = spriteMap[std::make_pair((OBJECT)i, j)].getPosition().x;//0; // else messes with transform call in test? spriteMap[std::make_pair((OBJECT)i, j)].getPosition().x;
            hitboxMap[std::make_pair((OBJECT)i, j)].top = spriteMap[std::make_pair((OBJECT)i, j)].getPosition().y; // spriteMap[std::make_pair((OBJECT)i, j)].getPosition().y;
            hitboxMap[std::make_pair((OBJECT)i, j)].width = objWidth * spriteMap[std::make_pair((OBJECT)i, j)].getScale().x;
            hitboxMap[std::make_pair((OBJECT)i, j)].height = objHeight * spriteMap[std::make_pair((OBJECT)i, j)].getScale().y;

           // spriteMap[std::make_pair((OBJECT)i, j)].getTransform().transformRect(hitboxMap[std::make_pair((OBJECT)i, j)]); // may not need toput this here?? called another time in test
            reps[std::make_pair((OBJECT)i, j)].setSize(Vector2f(hitboxMap[std::make_pair((OBJECT)i, j)].width, hitboxMap[std::make_pair((OBJECT)i, j)].height));
           // hitboxMap[std::make_pair((OBJECT)i, j)].
            // run

            /*reps[std::make_pair((OBJECT)i, j)].setSize(Vector2f
                                                                (objWidth * spriteMap[std::make_pair((OBJECT)i, j)].getScale().x, 
                                                                 objHeight * spriteMap[std::make_pair((OBJECT)i, j)].getScale().y)); */// scale exception for bushes and other!
            reps[std::make_pair((OBJECT)i, j)].setFillColor(Color(101, 5, 56, 70));
            //reps[std::make_pair((OBJECT)i, j)].setPosition(Vector2f(hitboxMap[std::make_pair((OBJECT)i, j)].left, hitboxMap[std::make_pair((OBJECT)i, j)].top));
            reps[std::make_pair((OBJECT)i, j)].setPosition(hitboxMap[std::make_pair((OBJECT)i, j)].left, hitboxMap[std::make_pair((OBJECT)i, j)].top);
                //Vector2f(spriteMap[std::make_pair((OBJECT)i, j)].getPosition().x, spriteMap[std::make_pair((OBJECT)i, j)].getPosition().y));
        };
            
        }
    }
    // initial positions must be 0 so that they'll overlap when getTransform called ater
   // hitboxes[TREE_INDEX] = { 0, 0, 43, 55 };
   // hitboxes[SAPLING_INDEX] = { 0, 0, 20, 37 };
   // hitboxes[GRASS_INDEX] = { 0, 0, 19, 18 };
   // hitboxes[MUSHROOM_INDEX] = { 0, 0, 16, 17 };
   // hitboxes[BUSH_INDEX] = { 0, 0, 18, 15 };
   // hitboxes[FRUIT_INDEX] = { 0, 0, 34, 27 };
   //// hitboxes[SPROUT_INDEX] = { 0, 0, 16, 14 };
   // hitboxes[FLOWERS_INDEX] = { 0, 0, 33, 33 };
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
    //for (unsigned int i = 0; i < NUM_OBJECT_SPRITES; i++) { // how to do this if sprites not made???
    //    spriteMap[i].getTransform().transformRect(hitboxes[i]);
    //   // reps[i].setFillColor(Color(101, 5, 56, 70));
    //   // reps[i].setPosition(Vector2f(sprites[i].getPosition().x, sprites[i].getPosition().y));
    //    /*if (i == rWINDOW_INDEX) reps[i].setPosition(Vector2f(sprites[i].getPosition().x + ))*/
    //}

//}

//bool Scene::checkCollisions(Mon mon)
//{
//    //Sprite possibleCollisions[NUM_OBJECT_SPRITES]; // use this later
//    for (int i = (int) BUSH; i < NUM_OBJ_TYPES; i++)
//    {
//        for (int j = 0; j < numObj[i]; j++)
//        {
//            if (mon.willCollide(spriteMap[std::make_pair((OBJECT)i, j)], hitboxMap[std::make_pair((OBJECT)i, j)])) // something added with this loop or implementation in Test.cpp that caused opengl
//            {
//              //  reps[i].setFillColor(Color(201, 114, 144, 40));
//                return true; // what if multiple collisions? only first returned
//              //  possibleCollisions[i] = sprites[i];
//            }
//            else {
//                // reps[i].setFillColor(Color(2, 207, 188, 40));
//                return false;
//            }
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

std::map<std::pair<OBJECT, int>, Sprite> Scene::get_spriteMap() { return spriteMap; }

std::map<std::pair<OBJECT, int>, FloatRect> Scene::get_hitboxMap() { return hitboxMap; }

std::map<std::pair<OBJECT, int>, RectangleShape> Scene::get_Reps() { return reps; }