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
    //Mon eevee = Mon(SCRN_W / 2, SCRN_H / 2, "graphics/eevee.png");

    Scene fieldScene;

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

       /* Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                player.isMoving(true);
                player.setSprite();
                player.updateDirection(); // try switching with setSprite to see if detects LEFT_UP
            }
            if (event.type == Event::KeyReleased)
            {
                player.isMoving(false);
                player.zeroDirection();
            }
        }*/



        // update time
        Time dt = clock.restart();

        // if eevee doesn't have steps remaining, will generate more
        //if (!eevee.get_stepCounter())
        //{
        //    int steps = eevee.randSteps(dt);
        //    Direction dir = eevee.randDir(dt); // sets here so if no movement, sprite has chance of turning
        //    if (steps) {
        //        eevee.setDirection(dir);
        //        eevee.setOrientation(dir);
        //        eevee.setSprite();
        //        eevee.set_stepCounter(steps); // !!! type convo !!!
        //        eevee.isMoving(true); // update speed
        //    }
        //    else { // random chance of turning in place
        //        srand((int)time(0));
        //        int still = rand() % 10;
        //        if (!still) {
        //            eevee.setDirection(dir);
        //            eevee.setOrientation(dir);
        //            eevee.setSprite();
        //        }
        //        eevee.isMoving(false);
        //    }
        //}


        
        // collisions checking
        //if (eevee.willCollide(fieldScene.getSprites()[TREE_INDEX], fieldScene.getHitboxes()[TREE_INDEX]))
        //{
        //    std::cout << "COLLISION";
        //    fieldScene.getReps()[TREE_INDEX].setFillColor(Color(201, 114, 144, 40));
        //    Direction old = eevee.getOrientation();
        //    while (eevee.getOrientation() == old) { eevee.setOrientation(eevee.randDir(dt)); }
        //    eevee.setDirection(eevee.getOrientation());
        //    eevee.setSprite(); // isMoving??
        //}

       // for (unsigned int i = 0; i < NUM_OBJECT_SPRITES; i++)
       // {
       //     if (eevee.willCollide(fieldScene.getSprites()[i], fieldScene.getHitboxes()[i])) // something added with this loop or implementation in Test.cpp that caused opengl
       //     {
       //        // fieldScene.getReps()[i].setFillColor(Color(201, 114, 144, 40));
       //         std::cout << "COLLISION";
       //        // while (eevee.getOrientation() == old) { 
       //          //} // generated paused...jumped up and moved off !!
       //         eevee.isMoving(false);
       //         eevee.setDirection(eevee.oppDirection(eevee.getOrientation())); // generate opposite direction
       //         eevee.isMoving(true);
       //         eevee.setSprite(); // isMoving?? // what if multiple collisions? only first returned
       //       //  possibleCollisions[i] = sprites[i];
       //         break;
       //     }
       //     /*else {
       //         fieldScene.getReps()[i].setFillColor(Color(2, 207, 188, 40));
       //     }*/
       // }

       // //if (fieldScene.checkCollisions(eevee))
       // //{
       // //    std::cout << "COLLISION";
       // //    Direction old = eevee.getOrientation();
       // //    while (eevee.getOrientation() == old) { eevee.setOrientation(eevee.randDir(dt)); }
       // //    eevee.setDirection(eevee.getOrientation());
       // //    eevee.setSprite(); // isMoving??
       // //}
       // eevee.update(dt); // if no collisions, moves as normal
       //// eevee.updateHitbox(); // right place??

       // // reduces step counter after moving
       // if (eevee.getState() == MOVING) eevee.set_stepCounter(eevee.get_stepCounter() - 1);


        /* draw scene */
        window.clear();
        window.draw(fieldScene.getBackground(), &fieldScene.getTexture());
        for (unsigned int i = 0; i < NUM_OBJECT_SPRITES; i++)
        {
            window.draw(fieldScene.getSprites()[i]);
           // window.draw(fieldScene.getReps()[i]);
        }
        /*for (unsigned int j = 8; j < 12; j++)
        {
            window.draw(fieldScene.getReps()[j]);
        }*/

       // window.draw(eevee.getSprite());
        /*eevee.updateRep();
        window.draw(eevee.getRep());*/

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


// fix collisions
// more sophisticated movement AI to prevent trapped and to look natural