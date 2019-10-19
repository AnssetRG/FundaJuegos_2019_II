#include "MainGame.h"
#include "Sprite.h"
#include "ImageLoader.h"
#include <iostream>
#include "ResourceManager.h"
#include "PapuEngine.h"


using namespace std;

void MainGame::run() {
	init();
	update();
}

void MainGame::init() {
	Papu::init();
	_window.create("Ella se fue :'v", _witdh, _height, 0);
	initLevel();
	initShaders();
}

void MainGame::initLevel(){
	currentLevel = 0;
	levels.push_back(new Level("Levels/level.txt"));
	player = new Player();
	player->init(1.0f,
		levels[currentLevel]->getPlayerPosition(),
		&_inputManager,
		"Textures/circle.png");
	_spriteBacth.init();
}

void MainGame::initShaders() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}


void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1,GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBacth.begin();
	levels[currentLevel]->draw();
	player->draw(_spriteBacth);
	for (auto& sprite_object : _sprites) {
		sprite_object->draw(_spriteBacth);
	}
	_spriteBacth.end();
	_spriteBacth.renderBatch();
	
	
	glBindTexture(GL_TEXTURE_2D, 0);

	_program.unuse();
	_window.swapBuffer();
}

void MainGame::procesInput() {
	SDL_Event event;
	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				_inputManager.setMouseCoords(event.motion.x,event.motion.y);
			break;
			case  SDL_KEYUP:
				_inputManager.releaseKey(event.key.keysym.sym);
				break;
			case  SDL_KEYDOWN:
				_inputManager.pressKey(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.pressKey(event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.releaseKey(event.button.button);
				break;
		}

		if (_inputManager.isKeyPressed(SDLK_a)) {
			glm::vec2 randomPos = levels[currentLevel]->getRandomFreePosition();
			_sprites.push_back(new Sprite());
			_sprites.back()->init(randomPos.x, randomPos.y, randomPos, 50, 50, "Textures/A.png");
			player->setPosition(randomPos);
		}
		if (_inputManager.isKeyPressed(SDLK_b)) {
			glm::vec2 randomPos = levels[currentLevel]->getRandomFreePosition();
			_sprites.push_back(new Sprite());
			_sprites.back()->init(randomPos.x, randomPos.y, randomPos, 50, 50, "Textures/B.png");
			player->setPosition(randomPos);
		}
		if (_inputManager.isKeyPressed(SDLK_c)) {
			glm::vec2 randomPos = levels[currentLevel]->getRandomFreePosition();
			_sprites.push_back(new Sprite());
			_sprites.back()->init(randomPos.x, randomPos.y, randomPos, 50, 50, "Textures/C.png");
			player->setPosition(randomPos);
		}
		if (_inputManager.isKeyPressed(SDLK_d)) {
			glm::vec2 randomPos = levels[currentLevel]->getRandomFreePosition();
			_sprites.push_back(new Sprite());
			_sprites.back()->init(randomPos.x, randomPos.y, randomPos, 50, 50, "Textures/D.png");
			player->setPosition(randomPos);
		}
		if (_inputManager.isKeyPressed(SDLK_e)) {
			glm::vec2 randomPos = levels[currentLevel]->getRandomFreePosition();
			_sprites.push_back(new Sprite());
			_sprites.back()->init(randomPos.x, randomPos.y, randomPos, 50, 50, "Textures/E.png");
			player->setPosition(randomPos);
		}
		/*
		if (_inputManager.isKeyPressed(SDLK_UP)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
		}
		if (_inputManager.isKeyPressed(SDLK_DOWN)) {
			_camera.setPosition(_camera.getPosition() - glm::vec2(0.0, CAMERA_SPEED));
		}
		if (_inputManager.isKeyPressed(SDLK_LEFT)) {
			_camera.setPosition(_camera.getPosition() - glm::vec2(CAMERA_SPEED, 0.0));
		}
		if (_inputManager.isKeyPressed(SDLK_RIGHT)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
		}*/
		if (_inputManager.isKeyPressed(SDLK_z)) {
			_camera.setScale(_camera.getScale() + SCALE_SPEED);
		}
		if (_inputManager.isKeyPressed(SDLK_x)) {
			_camera.setScale(_camera.getScale() - SCALE_SPEED);
		}/*
		if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
			glm::vec2 mouseCoords =  _camera.convertScreenToWorl(_inputManager.getMouseCoords());
			cout << mouseCoords.x << " " << mouseCoords.y << endl;
		}*/
	}
}

void MainGame::update() {

	while (_gameState != GameState::EXIT) {
		procesInput();
		draw();
		_camera.update(player->getPosition());
		_time += 0.002f;
		//_camera.setPosition(player->getPosition());
		player->update();
	}
}

#include "wtypes.h"

MainGame::MainGame(): 
					  _witdh(1800),
					  _height(1000),
					  _gameState(GameState::PLAY),
					  _time(0)
{
	//Hacer dinámico el tamaño de pantalla
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0) and the bottom right corner will have coordinates (horizontal, vertical)

	_witdh = desktop.right / 1.5;
	_height = desktop.bottom / 1.5;
	//cout << horizontal << '\n' << vertical << '\n';

	_camera.init(_witdh, _height); //_width = 800, _height = 600
	//_camera.init(horizontal, vertical);
}


MainGame::~MainGame()
{
}
