#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

#define SCRN_H (1080)
#define SCRN_W (1920)

enum Direction { LEFT, LEFT_UP, UP, RIGHT_UP, RIGHT, RIGHT_DOWN, DOWN, LEFT_DOWN, NONE };
enum State { IDLE, MOVING, ASLEEP, INTERACTING };

const unsigned int TILE_SIZE = 128;
const unsigned int TREE_TILE = 128 * 5 / 4;