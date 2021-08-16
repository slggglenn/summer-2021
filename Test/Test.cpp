// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Character.h"
#include "Player.h"
#include "Mon.h"
#include "Test.h"
#include <iostream>

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Test", Style::Fullscreen);

    Player player = Player(SCRN_W / 2, SCRN_H / 3, "graphics/eevee.png");
    //Mon eevee = Mon(SCRN_W / 2, SCRN_H / 2, "graphics/eevee.png"); // don't use other slash (gets yellow highlighted) recognized as escape characters

    Clock clock;
    const unsigned int TILE_SIZE = 32;
    const unsigned int TILE_TYPES = 4;
    VertexArray background;
    Texture backgroundTexture;
    
    if (!backgroundTexture.loadFromFile("graphics/tilesetCut.png")) std::cout << "ERROR" << std::endl;

    background.setPrimitiveType(Quads);
    background.resize((SCRN_H / TILE_SIZE) * (SCRN_W / TILE_SIZE) * TILE_TYPES);

    int currVertex = 0;
    for (unsigned int c = 0; c < SCRN_W / TILE_SIZE; c++) {

        for (unsigned int r = 0; r < SCRN_H / TILE_SIZE; r++) {
            background[currVertex].position = Vector2f(c * TILE_SIZE, r * TILE_SIZE); // 96 2240, 128 2272
            background[currVertex + 1].position = Vector2f((c * TILE_SIZE) + TILE_SIZE, r * TILE_SIZE);
            background[currVertex + 2].position = Vector2f((c * TILE_SIZE) + TILE_SIZE, (r * TILE_SIZE) + TILE_SIZE);
            background[currVertex + 3].position = Vector2f(c * TILE_SIZE, (r * TILE_SIZE) + TILE_SIZE);


            // TO DO: scale up background sprites, increas TILE_SIZE, change resize of vertex array
            // get correct coordinates
            srand((int)time(0) + r * c - r);
            int eitherGrassFlower = (rand() % TILE_SIZE);
            int verticalOffset = eitherGrassFlower * TILE_SIZE;

            background[currVertex].texCoords = Vector2f(0, verticalOffset);
            background[currVertex + 1].texCoords = Vector2f(TILE_SIZE, verticalOffset);
            background[currVertex + 2].texCoords = Vector2f(TILE_SIZE, verticalOffset + TILE_SIZE);
            background[currVertex + 3].texCoords = Vector2f(0, verticalOffset + TILE_SIZE);

            currVertex += 4; // incrementing for # of vertices in quad
        }
    }
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
        window.draw(background, &backgroundTexture);
        window.draw(player.getSprite()); // Make sprite bigger and remove background

        // show everything just drawn
        window.display();
    }

}

// alpha: little eevee skitters around map with randomly generated movement (!!!)
// iter 1: can click on it to bring up status (hungry, play level, fatigue, etc.) also option to talk (random dialogue)
// adventures to different places... finding lost eggs and raising more... friendship
// iter 2: set timer for certain amount... send poke out on adventures and find stuff and interactions when done