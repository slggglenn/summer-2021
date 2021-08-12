// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Character.h"
#include "Player.h"
#include "Mon.h"
#include "Test.h"
#include <iostream>


std::map<std::pair<State, Direction>, Sprite> setAnimSprites(Texture* texture_, std::map<std::pair<State, Direction>, Sprite> animSprites_);
Sprite updateIdleSprite(Direction dir, std::map<std::pair<State, Direction>, Sprite> animSprites_);

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Test", Style::Fullscreen);

    //Player player = Player(SCRN_W / 2, SCRN_H / 3, "graphics/eevee.png");
    //Animation animTest = Animation();
   // Character A = Character(SCRN_W / 2, SCRN_H / 3, "graphics/eevee.png");
    // ERROR HERE??? //
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
       
        /*Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                player.setState(MOVING);
                cout << "setState (M)" << endl;
                player.getAnimation().updateIdleSprite(player.getOrientation());
                cout << "updateIdleSprite" << endl;

                player.updateDirection();
                cout << "updateDirection" << endl;
            }
            if (event.type == Event::KeyReleased)
            {
                player.setState(IDLE);
                cout << "setState" << endl;
                player.zeroDirection();
                cout << "zeroDire" << endl;
            }
        }*/


        /* update scene */

        // update time
        Time dt = clock.restart();
        //player.update(dt);
        // ERROR CAUSED HERE?? //





        Texture texture;
        Image img;
        img.loadFromFile("graphics/eevee.png");// !!! en.sfml-dev.org/forums/index.php?topic=12663.0
        img.createMaskFromColor(Color(0, 128, 128), 0); // !!! NEED: program to get color pixels from the thing itself
        texture.loadFromImage(img);

        Sprite sprite;
        sprite.setTexture(texture);

        std::map<std::pair<State, Direction>, Sprite> animSprites_;



        animSprites_ = setAnimSprites(&texture, animSprites_);
        sprite = updateIdleSprite(DOWN, animSprites_);

        //nd opengl error
        // edit1: got rid of sprite_ parameter in updateIdleSprite --> same white box but biggger
        // edit2: got rid of ASLEEP and MOVING states since unnecessary --> same as above
        // edit3: got rid of last line of updateIdleSprite --> shows white box as rectangle (think it's space of texture but not displaying)
        // line 160: texture_ parameter should be pointer??
        //https://stackoverflow.com/questions/27951870/sfml-texture-displaying-as-a-white-box






        /* draw scene */

        //animTest.getSprite().setPosition(SCRN_W / 3, SCRN_H / 3);

        // eevee sprite: 652/2/4/2, 267/11
        window.clear();
        window.draw(sprite);
        //window.draw(animTest.getSprite());
        //window.draw(player.getTempSprite());
       // window.draw(A.getAnimation().getSprite());
        //window.draw(player.getAnimation().getSprite()); // Make sprite bigger and remove background
        // !!! THINK ERROR CAUSED HERE !!!

        // show everything just drawn
        window.display();
    }

}

// alpha: little eevee skitters around map with randomly generated movement (!!!)
// iter 1: can click on it to bring up status (hungry, play level, fatigue, etc.) also option to talk (random dialogue)
// adventures to different places... finding lost eggs and raising more... friendship
// iter 2: set timer for certain amount... send poke out on adventures and find stuff and interactions when done


std::map<std::pair<State, Direction>, Sprite> setAnimSprites(Texture* texture_, std::map<std::pair<State, Direction>, Sprite> animSprites_)
{
    //State states[2] = { IDLE, ASLEEP };
    Direction directions[8] = { DOWN, UP, LEFT, RIGHT, LEFT_DOWN, RIGHT_DOWN, LEFT_UP, RIGHT_UP };

    // determine how many IDLE, MOVING, SLEEP sprites how many for each direction XXX
    //for (unsigned int i = 0; i < 2; i++) // repeats once for IDLE and once for MOVING
    //{
        State currState;
        unsigned int currX, currY;
        //if (!i) // boundary?? 
        //{
            currState = IDLE; // IDLE on first run
            currX = IDLE_START_X;
            currY = IDLE_START_Y;
        //}
        //else {
        //    currState = MOVING; // MOVING on second
        //    currX = MOVE_START_X;
        //    currY = MOVE_START_Y;
        //}

        // gets row for specific DIRECTION animation for current STATE
        for (unsigned int j = 0; j < 8; j++)
        {
            Sprite row;
            row.setTexture(*texture_);
            row.setTextureRect(IntRect(currX, currY + (SPRITE_SIDE_LEN * j),
                2 * SPRITE_SIDE_LEN, SPRITE_SIDE_LEN)); // SAME as below
            row.setScale(3, 3);
            animSprites_[make_pair(currState, directions[j])] = row;

        }
    //}

    //Sprite sleepChunk;
    //sleepChunk.setTexture(texture_);
    //sleepChunk.setTextureRect(IntRect(SLEEP_START_X,
    //    SLEEP_START_Y, 3 * SPRITE_SIDE_LEN, SPRITE_SIDE_LEN)); // CHHECK 2.5 if enough size and if width param!!
    //sleepChunk.setScale(3, 3);
    //animSprites_[make_pair(ASLEEP, NONE)] = sleepChunk;

    return animSprites_;
}


Sprite updateIdleSprite(Direction dir, std::map<std::pair<State, Direction>, Sprite> animSprites_) // CURRENTLY JUST FOR IDLE
{
    Sprite s;
    s = animSprites_[make_pair(IDLE, dir)]; // pointer ok??????!!!!
    //s.setTextureRect(IntRect(0, 0, SPRITE_SIDE_LEN, SPRITE_SIDE_LEN));
    return s;
}