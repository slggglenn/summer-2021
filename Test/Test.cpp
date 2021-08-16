// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Character.h"
#include "Player.h"
#include "Mon.h"
#include "Background.h"
#include "Test.h"
#include <iostream>

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Test");
    window.setSize(sf::Vector2u(640, 360));

    //static const std::vector<VideoMode>& arr = vm.getFullscreenModes();
   // vm = arr[1];

    Player player = Player(SCRN_W / 2, SCRN_H / 3, "graphics/eevee.png");
    //Mon eevee = Mon(SCRN_W / 2, SCRN_H / 2, "graphics/eevee.png"); // don't use other slash (gets yellow highlighted) recognized as escape characters

    Clock clock;
    const unsigned int TILE_SIZE = 64;
    const unsigned int TILE_TYPES = 4;
    VertexArray background;
    Texture ssTrans;
    Image spritesheet;

    if (!spritesheet.loadFromFile("graphics/tilesetCut.png")) std::cout << "ERROR" << std::endl;
    spritesheet.createMaskFromColor(Color(255, 255, 255, 0), 0);
    ssTrans.loadFromImage(spritesheet);

    makeBackground(background);

    // other stuff
    Sprite tree, sapling, grass, mushroom, bush, fruit, sprout, flowers;
    tree.setTexture(ssTrans);
    sapling.setTexture(ssTrans);
    grass.setTexture(ssTrans);
    mushroom.setTexture(ssTrans);
    bush.setTexture(ssTrans);
    fruit.setTexture(ssTrans);
    sprout.setTexture(ssTrans);
    flowers.setTexture(ssTrans);


    tree.setTextureRect(IntRect(24, 3088, 83, 108));
    sapling.setTextureRect(IntRect(142, 3122, 40, 76));
    grass.setTextureRect(IntRect(400, 4489, 33, 35));
    mushroom.setTextureRect(IntRect(79, 4618, 34, 33));
    bush.setTextureRect(IntRect(208, 14200, 34, 38));
    fruit.setTextureRect(IntRect(321, 3130, 63, 51));
    sprout.setTextureRect(IntRect(270, 5710, 33, 27));
    flowers.setTextureRect(IntRect(189, 4860, 67, 63));

    tree.setScale(3, 3);
    sapling.setScale(3, 3);
    grass.setScale(3, 3);
    mushroom.setScale(3, 3);
    bush.setScale(3, 3);
    fruit.setScale(3, 3);
    sprout.setScale(3, 3);
    flowers.setScale(3, 3);

    tree.setPosition(SCRN_W * 2/ 3, SCRN_H / 4);
    sapling.setPosition((SCRN_W * 2/ 3) + 20, (SCRN_H / 4) + 20);
    grass.setPosition(SCRN_W / 3, SCRN_H / 3);
    mushroom.setPosition((SCRN_W * 2 / 3) + 40, (SCRN_H / 4) + 10);
    bush.setPosition(SCRN_W / 2, 3 * SCRN_H / 4);
    fruit.setPosition(SCRN_W * 2 / 3, (SCRN_H / 4) - 60);
    sprout.setPosition((SCRN_W * 2 / 3) - 20, (SCRN_H / 4) - 30);
    flowers.setPosition(SCRN_W / 2, SCRN_H / 5);

    // draw background with texture ref

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

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                player.isMoving(true);
                player.setSprite();
                player.updateDirection();
            }
            if (event.type == Event::KeyReleased)
            {
                player.isMoving(false);
                player.zeroDirection();
            }
        }


        /* update scene */

        // update time
        Time dt = clock.restart();
        player.update(dt);


        /* draw scene */

        // eevee sprite: 652/2/4/2, 267/11
        window.clear();
        window.draw(background, &ssTrans);
        window.draw(tree);
        window.draw(sapling);
        window.draw(grass);
        window.draw(mushroom);
        window.draw(bush);
        window.draw(fruit);
        window.draw(sprout);
        window.draw(flowers);
        window.draw(player.getSprite()); // Make sprite bigger and remove background

        // show everything just drawn
        window.display();
    }

}

// alpha: little eevee skitters around map with randomly generated movement (!!!)
// iter 1: can click on it to bring up status (hungry, play level, fatigue, etc.) also option to talk (random dialogue)
// adventures to different places... finding lost eggs and raising more... friendship
// iter 2: set timer for certain amount... send poke out on adventures and find stuff and interactions when done