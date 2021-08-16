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

    Player player = Player(SCRN_W / 2, SCRN_H / 3);
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
                player.setState(MOVING);
                player.updateDirection();
                Direction dir = player.getOrientation();
                player.getAnimation().updateSprite(MOVING, dir);

                player.updateDirection();
            }
            if (event.type == Event::KeyReleased)
            {
                player.setState(IDLE);
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
        //window.draw(player.getAnimation().getSprite()); // Make sprite bigger and remove background

        // show everything just drawn
        window.display();
    }

}
