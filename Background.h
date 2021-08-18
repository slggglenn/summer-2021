#pragma once
#include "Test.h"
using namespace sf;

class Scene
{
private:
	VertexArray background;
	Texture ssTrans;
	Image spritesheet;

public:
	Scene();
	void makeBackground(VertexArray& background);
	VertexArray getBackground();
	Texture& getTexture();
};