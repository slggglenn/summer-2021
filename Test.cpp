#include "Test.h"
#include "Character.h"
#include "Player.h"
#include "Mon.h"
#include "Background.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    // setting up window and time
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Test");
    window.setSize(sf::Vector2u(960, 540));
    Clock clock;

    // initializing textures and background constants
    VertexArray background;
    Texture ssTrans;
    Image spritesheet;

    if (!spritesheet.loadFromFile("graphics/SPRITESHEET.png")) std::cout << "ERROR" << std::endl;
    spritesheet.createMaskFromColor(Color::White, 0);
    ssTrans.loadFromImage(spritesheet);

    // creates Mon character
    Mon eevee = Mon(SCRN_W / 2, SCRN_H / 2, "graphics/eevee.png");
    //Player player = Player(SCRN_W / 3, SCRN_H / 3, "graphics/eevee.png");

    Scene fieldScene;
    bool showRep = true;

    // game loop
    while (window.isOpen())
    {
        // Event event;
         // quit if window closed
        /* while (window.pollEvent(event))
         {
             window.close();
         }*/
         /* handle player input */

         // sfml-dev.org/tutorials/1.6/window-events.php

        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

        if (Keyboard::isKeyPressed(Keyboard::Tab)) showRep = !showRep;

       //Event event;

       // while (window.pollEvent(event))
       // {
       //     if (event.type == Event::KeyPressed)
       //     {
       //         player.isMoving(true);
       //         player.setSprite();
       //         player.updateDirection(); // try switching with setSprite to see if detects LEFT_UP
       //     }
       //     if (event.type == Event::KeyReleased)
       //     {
       //         player.isMoving(false);
       //         player.zeroDirection();
       //     }
       // }



        // update time
        Time dt = clock.restart();

        // if eevee doesn't have steps remaining, will generate more
        if (!eevee.get_stepCounter())
        {
            int steps = eevee.randSteps();
            Direction dir = eevee.randDir(); // sets here so if no movement, sprite has chance of turning
            if (steps) {
                eevee.setDirection(dir);
                eevee.setOrientation(dir);
                eevee.setSprite();
                eevee.set_stepCounter(steps); // !!! type convo !!!
                eevee.isMoving(true); // update speed
            }
            else { // random chance of turning in place
                srand((int)time(0));
                int still = rand() % 10;
                if (!still) {
                    eevee.setDirection(dir);
                    eevee.setOrientation(dir);
                    eevee.setSprite();
                }
                eevee.isMoving(false);
            }
        }
        
        // tree, bush, sapling 
        // 
        // collisions checking
        //if (eevee.willCollide(fieldScene.getSprites()[TREE_INDEX], fieldScene.getHitboxes()[TREE_INDEX]))
        //{
        //    std::cout << "COLLISION";
        //   // fieldScene.getReps()[TREE_INDEX].setFillColor(Color(201, 114, 144, 40));
        //    Direction old = eevee.getOrientation();
        //    while (eevee.getOrientation() == old) { eevee.setOrientation(eevee.randDir()); }
        //    eevee.setDirection(eevee.getOrientation());
        //    eevee.setSprite(); // isMoving??
        //}

        // works kinda but opengl error
        //if (fieldScene.checkCollisions(eevee))
        //{
        //    //std::cout << "COLLISION";
        //    Direction old = eevee.getOrientation();
        //    while (eevee.getOrientation() == old) { eevee.setOrientation(eevee.randDir()); }
        //    eevee.setDirection(eevee.getOrientation());
        //    eevee.setSprite(); // isMoving??
        //}

        
        // collisions
        for (int i = (int)BUSH; i < NUM_OBJ_TYPES - 1; i++) // bush->tree
        {
            for (int j = 0; j < fieldScene.getNumObj()[i]; j++)
            {

                //if (eevee.willCollide(fieldScene.get_spriteMap[std::make_pair((OBJECT)i, j)], 
                //                      fieldScene.get_hitboxMap[std::make_pair((OBJECT)i, j)])) // something added with this loop or implementation in Test.cpp that caused opengl
                //{
                    Sprite obj = fieldScene.get_spriteMap()[std::make_pair((OBJECT)i, j)];
                    FloatRect objHB = fieldScene.get_hitboxMap()[std::make_pair((OBJECT)i, j)];

                    if (eevee.getGlobalHitbox().intersects(obj.getTransform().transformRect(objHB)))
                    {
                        fieldScene.get_Reps()[std::make_pair((OBJECT)i, j)].setFillColor(Color(201, 114, 144, 40)); // this isn't triggering
                        std::cout << "COLLISION: " << (OBJECT)i << j << std::endl;
                        // while (eevee.getOrientation() == old) { 
                            //} // generated paused...jumped up and moved off !!
                        eevee.isMoving(false);
                        eevee.setDirection(eevee.oppDirection(eevee.getOrientation())); // generate opposite direction
                        eevee.isMoving(true);
                        eevee.setSprite(); // isMoving?? // what if multiple collisions? only first returned
                        //  possibleCollisions[i] = sprites[i];
                    //break; // or continue? // maybe instead accumulates all directions it can't go in and chooses from remaining
                    }
                else {
                    fieldScene.get_Reps()[std::make_pair((OBJECT)i, j)].setFillColor(Color(101, 5, 56, 70));
                }
            }
        }

            // does this one not work??
        //if (fieldScene.checkCollisions(eevee))
        //{
        //    std::cout << "COLLISION";
        //    Direction old = eevee.getOrientation();
        //    while (eevee.getOrientation() == old) { eevee.setOrientation(eevee.randDir()); }
        //    eevee.setDirection(eevee.getOrientation());
        //    eevee.setSprite(); // isMoving??
        //}
        eevee.update(dt); // if no collisions, moves as normal
        eevee.updateHitbox(); // right place??

        // reduces step counter after moving
        if (eevee.getState() == MOVING) eevee.set_stepCounter(eevee.get_stepCounter() - 1);


        /* draw scene */
        window.clear();
        window.draw(fieldScene.getBackground(), &fieldScene.getTexture());
        for (int i = 0; i < NUM_OBJ_TYPES; i++) // 2 is # of Object types!!!
        {
            // gets number of sprites of current OBJECT type
           // int numTree = fieldScene.getNumObj();
            for (int j = 0; j < fieldScene.getNumObj()[i]; j++) // some reason tree being dranw at 0,0? not in initialized
            {
                //std::cout << fieldScene.getNumObj()[i] << std::endl;
                Vector2f pos;
                
               // if ((OBJECT)i == TREE) pos = fieldScene.get_treeMap()[j];
                //else
                
                //std::cout << "pos: " << pos.x << ", " << pos.y << std::endl; // all have same pos
                window.draw(fieldScene.get_spriteMap()[std::make_pair((OBJECT)i, j)]);
                if (showRep) window.draw(fieldScene.get_Reps()[std::make_pair((OBJECT)i, j)]);

                //if ((OBJECT)i == TREE) { // apples blink on and off
                //    srand(time(0));
                //    int notFruit = rand() % 10;
                //    if (!notFruit) {
                //        Sprite fruit;
                //        Vector2f fruitPos;
                //        fruitPos = pos;
                //        fruitPos.y += 45;
                //        fruitPos.x += 15;
                //        fieldScene.makeSprite(FRUIT, fruitPos, fruit);
                //        window.draw(fruit);
                //    }
                //}
            }
            //std::cout << std::endl << std::endl;
            
           // window.draw(fieldScene.getReps()[i]);
        }
        /*for (unsigned int j = 8; j < 12; j++)
        {
            window.draw(fieldScene.getReps()[j]);
        }*/

        window.draw(eevee.getSprite());
       // window.draw(player.getSprite());
        eevee.updateRep();
        window.draw(eevee.getRep());

        // show everything just drawn
        window.display();
    }
}


//TODO
// boundary area so won't go offscreen + wall and object collision
// ++switching sprites mid-move? also not changing sprite to correct one when movig?
// maybe first check current coords and compare with coords of other objects...if object in range, then check collision
// file for all collision handling
// file for background setup
// put displayable rectangles over each HB to check
// PROTOCOL: if mon has collision, reduces chance it'll make a viable move.. combat this somehow


//TODO:
// increase HB size so won't overlap before changing directions
// test current iter
// once working, instead of swithcing opp dir, just eliminate certain ones and then move
// // apples
// aniamtions!!
// more creatures
// creature interactions
// no sprite overlap (NASTY overlap between sapling and tree)
// more backgrounds
// if flower by itslef, sprite with 2, else full