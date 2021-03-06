#include "MainGame.h"
#include <iostream>

using namespace std;

MainGame::MainGame()
{
	window = nullptr;
	witdh = 800;
	height = 600;
	gameState = GameState::PLAY;
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	init();
	sprite.init(-1, -1, 1, 1);
	update();
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << event.motion.x << ", "<<event.motion.y << "\n";
			break;
		}
	}
}

void MainGame::init()
{
	window = SDL_CreateWindow("Clase 01", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, witdh, height, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		//TODO mostrar error
	}
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) 
	{
		//TODO mostrar error de glew
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //Generando 2 ventanas que se dibujando simultaneamente
	glClearColor(0.0f, 0.0, 1.0f, 1.0f);
	initShaders();
}
void MainGame::initShaders()
{
	
	glProgram.compileShader("Shaders/colorShaderVert.txt","Shaders/colorShaderFrag.txt");
}
void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sprite.draw();
	SDL_GL_SwapWindow(window);
}

void MainGame::update()
{
	while (gameState != GameState::EXIT) 
	{	
		processInput();
		draw();
	}
}
