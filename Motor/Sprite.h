#pragma once
#include <GL/glew.h>
class Sprite {
private:
	float x;
	float y;
	int width;
	int height;
	//todo vbo vertex Buffer Object 
	GLuint vboID;
public:
	Sprite();
	~Sprite();
	void init(float _x, float _y, int _width, int _height);
	void draw();
};