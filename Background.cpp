#include "Background.h"
#include "Character.h"
#include "Mon.h"
#include <iostream>
#include <math.h>
using namespace std;

Scene::Scene() {
    if (!spritesheet.loadFromFile("graphics/SPRITESHEET.png")) std::cout << "ERROR" << std::endl;
    spritesheet.createMaskFromColor(Color::White, 0);
    transSS.loadFromImage(spritesheet);
    makeBackground(background);
    initialize_spriteMap();
}

// TODO: more concise way? no need for vertex array??
void Scene::makeBackground(VertexArray& background) {
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

void Scene::initialize_spriteMap()
{
    srand(time(0));
    int percent[NUM_OBJ_TYPES] = { 5, 7, 3, 4, 0, 0 }; // percent that each obj will spawn
    int densityBuffer[NUM_OBJ_TYPES] = { 0,0,0,0,0,0 }; // exxtra likelihood based on density of same type obj nearby
    int willPlaceObj = 0;

    for (int i = 0; i < NUM_OBJ_TYPES; i++) willPlaceObj += percent[i]; // threshold for placing any object

    // moves through board
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 15; c++)
        {
            int randObj = rand() % 99 + 1;
            if (randObj <= willPlaceObj) // obj will be placed
            {
                static OBJECT nearby = TREE; // just placeholder

                int xL, xR, yL, yR; // 4 potential adjacents for a tile
                xL = c - 1;
                xR = c + 1;
                yL = r - 1;
                yR = r + 1;

                // coords for all possible adj tiles
                int adjCoords[8][2] = { {xL, yL}, {xL, r}, {xL, yL}, {c, yL}, {xR, yL}, {xR, r}, {xR, yR}, {c, yR} };

                // more efficient way to trigger nearby updates
                for (unsigned int i = 0; i < 8; i++)
                {
                    if (isNearby(adjCoords[i][0], adjCoords[i][1], &nearby)) densityBuffer[(int)nearby] += 1;
                    else if (adjCoords[i][0] && adjCoords[i][1] &&
                             !isNearby(adjCoords[i][0], adjCoords[i][1], &nearby))
                            {
                                if (densityBuffer[(int)nearby]) densityBuffer[(int)nearby] -= 1; // decreases is none around
                            }
                }

                // making the object
                OBJECT currType;

                // calculating percent
                int fP, mP, spP, bP, saP, tP;
                fP = percent[(int)FLOWER] + densityBuffer[(int)FLOWER];
                mP = percent[(int)MUSHROOM] + densityBuffer[(int)MUSHROOM];
                spP = percent[(int)SPROUT] + densityBuffer[(int)SPROUT];
                bP = percent[(int)BUSH] + densityBuffer[(int)BUSH];
                saP = percent[(int)SAPLING];
                tP = percent[(int)TREE] + densityBuffer[(int)TREE];

                // determining type
                if (randObj <= fP) currType = FLOWER;
                else if (randObj > fP && randObj <= fP + mP) currType = MUSHROOM;
                else if (randObj > fP + mP && randObj <= fP + mP + spP) currType = SPROUT;
                else if (randObj > fP + mP + spP && randObj <= fP + mP + spP + bP) currType = BUSH;
                else if (randObj > fP + mP + spP + bP && randObj <= fP + mP + spP + bP + saP) currType = SAPLING;
                else if (randObj > fP + mP + spP + bP + saP && randObj <= fP + mP + spP + bP + saP + tP) currType = TREE;

                makeSprite(currType, Vector2f(c * TILE_SIZE, r * TILE_SIZE), spriteMap[std::make_pair(currType, numObj[(int)currType])]); 
                
                // start at 0, then you increment as index
                (numObj[(int)currType])++;
            }
        }
    }
}

// initializes texture, scale, and position
void Scene::makeSprite(OBJECT type, Vector2f pos, Sprite& sprite)
{
    sprite.setTexture(transSS);
    sprite.setScale(5, 5);
    switch (type)
    {
    case TREE:
        sprite.setTextureRect(IntRect(10, 1535, 43, 55));
        break;
    case FLOWER:
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
        /*case FRUIT:
            sprite.setTextureRect(IntRect(159, 1557, 34, 27));
            break;*/
    }
    sprite.setPosition(pos);
}

void Scene::makeHitboxes() {
    for (int i = 0; i < NUM_OBJ_TYPES; i++)
    {
        for (int j = 0; j < numObj[i]; j++)
        {
            int objWidth, objHeight;

            objWidth = 10;

            switch (i)
            {
            case FLOWER:
                objWidth = 33;
                objHeight = 33;
                break;
            case TREE:
                objWidth = 43;
                objHeight = 55;
                break;
            case SAPLING:
                objWidth = 20;
                objHeight = 37;
                break;
            case MUSHROOM:
                objWidth = 16;
                objHeight = 17;
                break;
            case BUSH:
                objWidth = 18;
                objHeight = 15;
                break;
            case SPROUT:
                objWidth = 16;
                objHeight = 14;
                break;
            }
            hitboxMap[std::make_pair((OBJECT)i, j)].left = spriteMap[std::make_pair((OBJECT)i, j)].getPosition().x;
            hitboxMap[std::make_pair((OBJECT)i, j)].top = spriteMap[std::make_pair((OBJECT)i, j)].getPosition().y;

            hitboxMap[std::make_pair((OBJECT)i, j)].width = objWidth;
            hitboxMap[std::make_pair((OBJECT)i, j)].height = objHeight;

            reps[std::make_pair((OBJECT)i, j)].setSize(Vector2f(hitboxMap[std::make_pair((OBJECT)i, j)].width * spriteMap[std::make_pair((OBJECT)i, j)].getScale().x,
                                                                hitboxMap[std::make_pair((OBJECT)i, j)].height * spriteMap[std::make_pair((OBJECT)i, j)].getScale().y)); // DOES THIS CHANGE WORK
            reps[std::make_pair((OBJECT)i, j)].setFillColor(Color(101, 5, 56, 70));
            reps[std::make_pair((OBJECT)i, j)].setPosition(hitboxMap[std::make_pair((OBJECT)i, j)].left, hitboxMap[std::make_pair((OBJECT)i, j)].top);
        };

    }
}

// https://stackoverflow.com/questions/28690526/c-how-to-pass-an-uninitialized-pointer-to-a-function
bool Scene::isNearby(int x, int y, OBJECT* nearby)
{
    if (!x || !y) return false;

    for (int i = 0; i < NUM_OBJ_TYPES; i++)
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

VertexArray Scene::getBackground() { return background; }

int* Scene::getNumObj() { return numObj; }

Texture& Scene::getTexture() { return transSS; }

std::map<std::pair<OBJECT, int>, Sprite> Scene::get_spriteMap() { return spriteMap; }

std::map<std::pair<OBJECT, int>, FloatRect> Scene::get_hitboxMap() { return hitboxMap; }

std::map<std::pair<OBJECT, int>, RectangleShape> Scene::get_Reps() { return reps; }