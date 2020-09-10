#pragma once
#include <GL/glew.h>

struct Position 
{
	float x;
	float y;

};

struct Vertex 
{
	Position position;
	void setPosition(float _x, float _y) 
	{
		position.x = _x;
		position.y = _y;
	}

};