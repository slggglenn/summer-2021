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
    window.setSize(sf::Vector2u(640, 360));
    Clock clock;

    // initializing textures and background constants
    VertexArray background;
    Texture ssTrans;
    Image spritesheet;

    if (!spritesheet.loadFromFile("graphics/SPRITESHEET.png")) std::cout << "ERROR" << std::endl;
    spritesheet.createMaskFromColor(Color::White, 0);
    ssTrans.loadFromImage(spritesheet);

    // creates Mon character
    Mon eevee = Mon((SCRN_W * 2 / 3) + 70, (SCRN_H / 4) + 450, "graphics/eevee.png");

    Scene fieldScene;

    //// makes background object sprites
    //Sprite tree, sapling, grass, mushroom, bush, fruit, sprout, flowers;
    //tree.setTexture(ssTrans);
    //sapling.setTexture(ssTrans);
    //grass.setTexture(ssTrans);
    //mushroom.setTexture(ssTrans);
    //bush.setTexture(ssTrans);
    //fruit.setTexture(ssTrans);
    //sprout.setTexture(ssTrans);
    //flowers.setTexture(ssTrans);

    //// initializes properties:
    //tree.setTextureRect(IntRect(10, 1535, 43, 55));
    //sapling.setTextureRect(IntRect(70, 1553, 20, 37));
    //grass.setTextureRect(IntRect(199, 2236, 19, 18));
    //mushroom.setTextureRect(IntRect(40, 2301, 16, 17));
    //bush.setTextureRect(IntRect(106, 6998, 18, 15));
    //fruit.setTextureRect(IntRect(159, 1557, 34, 27));
    //sprout.setTextureRect(IntRect(135, 2847, 16, 14));
    //flowers.setTextureRect(IntRect(95, 2420, 33, 33));

    //tree.setScale(6, 6);
    //sapling.setScale(6, 6);
    //grass.setScale(6, 6);
    //mushroom.setScale(6, 6);
    //bush.setScale(6, 6);
    //fruit.setScale(6, 6);
    //sprout.setScale(6, 6);
    //flowers.setScale(6, 6);

    //tree.setPosition((SCRN_W * 2/ 3) + 40, (SCRN_H / 4) + 50);
    //sapling.setPosition(SCRN_W * 3 / 5, (SCRN_H / 4) + 20);
    //grass.setPosition(SCRN_W / 3, SCRN_H / 3);
    //mushroom.setPosition(5 * SCRN_W / 6, 2 * SCRN_H / 5);
    //bush.setPosition(SCRN_W / 2, 3 * SCRN_H / 4);
    //fruit.setPosition((SCRN_W * 2 / 3) + 80, (2 * SCRN_H / 7) + 70);
    //sprout.setPosition((SCRN_W * 3 / 5) + 100, (SCRN_H / 4) + 80);
    //flowers.setPosition(SCRN_W / 3, SCRN_H / 7);

    //// makes hitboxes for each sprite
    //FloatRect treeHB, saplingHB, grassHB, mushroomHB, bushHB, fruitHB, sproutHB, flowersHB, rWindowHB, lWindowHB, uWindowHB, bWindowHB;
    //treeHB = { 0, 0, 43, 55 };
    //saplingHB = { 0, 0, 20, 37 };
    //grassHB = { 0, 0, 19, 18 };
    //mushroomHB = { 0, 0, 16, 17 };
    //bushHB = { 0, 0, 18, 15 };
    //fruitHB = { 0, 0, 34, 27 };
    //sproutHB = { 0, 0, 16, 14 };
    //flowersHB = { 0, 0, 33, 33 };
    //
    //// hitboxes for boundaries of world
    //lWindowHB = { 0, 0, 1, 1080 };
    //rWindowHB = { 1920, 0, 1, 1080 };
    //uWindowHB = { 0, 0, 1920, 1 };
    //bWindowHB = { 0, 1080, 1920, 1 };

    //// sets hitbox to the object
    //tree.getTransform().transformRect(treeHB);
    //sapling.getTransform().transformRect(saplingHB);
    //grass.getTransform().transformRect(grassHB);
    //mushroom.getTransform().transformRect(mushroomHB);
    //bush.getTransform().transformRect(bushHB);
    //fruit.getTransform().transformRect(fruitHB);
    //sprout.getTransform().transformRect(sproutHB);
    //flowers.getTransform().transformRect(flowersHB);

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
        if (!eevee.get_stepCounter())
        {
            int steps = eevee.randSteps(dt);
            Direction dir = eevee.randDir(dt); // sets here so if no movement, sprite has chance of turning
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
        
        // collisions checking
        if (eevee.willCollide(dt, fieldScene.getSprites()[TREE_INDEX], fieldScene.getHitboxes()[TREE_INDEX]))
        {
            Direction old = eevee.getOrientation();
            while (eevee.getOrientation() == old) { eevee.setOrientation(eevee.randDir(dt)); }
        }
        //if (fieldScene.checkCollisions(eevee, dt))
        //{
        //    // will stop moving; effectively resets movement
        //    //eevee.set_stepCounter(0);
        //    Direction old = eevee.getOrientation();
        //    while (eevee.getOrientation() == old) { eevee.setOrientation(eevee.randDir(dt));}
        //}
        eevee.update(dt); // if no collisions, moves as normal
        eevee.updateHitbox(); // right place??

        // reduces step counter after moving
        if (eevee.getState() == MOVING) eevee.set_stepCounter(eevee.get_stepCounter() - 1);


        /* draw scene */
        window.clear();
        window.draw(fieldScene.getBackground(), &fieldScene.getTexture());
        for (unsigned int i = 0; i < NUM_OBJECT_SPRITES; i++)
        {
            window.draw(fieldScene.getSprites()[i]);
            window.draw(fieldScene.getReps()[i]);
        }
        for (unsigned int j = 8; j < 12; j++)
        {
            window.draw(fieldScene.getReps()[j]);
        }

        window.draw(eevee.getSprite());
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


// fix collisions
// more sophisticated movement AI to prevent trapped and to look natural