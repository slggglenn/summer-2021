#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

#define SCRN_H (1080)
#define SCRN_W (1920)

enum Direction { LEFT, RIGHT, UP, DOWN, LEFT_UP, RIGHT_UP, LEFT_DOWN, RIGHT_DOWN, NONE };
enum State { IDLE, MOVING, ASLEEP, INTERACTING };

const unsigned int TILE_SIZE = 128;
const unsigned int TREE_TILE = 128 * 5/4;