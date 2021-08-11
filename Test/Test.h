#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

#define SCRN_H (1080)
#define SCRN_W (1920)

enum Direction { LEFT, RIGHT, UP, DOWN, LEFT_UP, RIGHT_UP, LEFT_DOWN, RIGHT_DOWN, NONE }; // remove clas?? add this to gen header for use in others
enum State { IDLE, MOVING, ASLEEP };