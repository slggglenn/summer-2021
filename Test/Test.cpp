// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Character.h"
#include "Player.h"
#include "Mon.h"
#include "Test.h"

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Test", Style::Fullscreen);

    Player player = Player(SCRN_W / 2, SCRN_H / 3, "graphics/eevee.png");
    //Mon eevee = Mon(SCRN_W / 2, SCRN_H / 2, "graphics/eevee.png"); // don't use other slash (gets yellow highlighted) recognized as escape characters

    Clock clock;

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

                if (Keyboard::isKeyPressed(Keyboard::Left))
                {
                    player.setOrientation(LEFT);
                }

                if (Keyboard::isKeyPressed(Keyboard::Right))
                {
                    player.setOrientation(RIGHT);
                }

                if (Keyboard::isKeyPressed(Keyboard::Up))
                {
                    player.setOrientation(UP);
                }

                if (Keyboard::isKeyPressed(Keyboard::Down))
                {
                    player.setOrientation(DOWN);
                }
            }
            if (event.type == Event::KeyReleased)
            {
                player.isMoving(false);
            }
        }


        /* update scene */

        // update time
        Time dt = clock.restart();
        player.update(dt);


        /* draw scene */

        // eevee sprite: 652/2/4/2, 267/11
        window.clear();
        window.draw(player.getSprite()); // Make sprite bigger and remove background

        // show everything just drawn
        window.display();
    }

}

// alpha: little eevee skitters around map with randomly generated movement (!!!)
// iter 1: can click on it to bring up status (hungry, play level, fatigue, etc.) also option to talk (random dialogue)
// adventures to different places... finding lost eggs and raising more... friendship
// iter 2: set timer for certain amount... send poke out on adventures and find stuff and interactions when done