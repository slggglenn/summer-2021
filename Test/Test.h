#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

#define SCRN_H (1080)
#define SCRN_W (1920)

enum Direction { LEFT, RIGHT, UP, DOWN, LEFT-UP, RIGHT-UP, LEFT-DOWN, RIGHT-DOWN, NONE }; // remove clas?? add this to gen header for use in others