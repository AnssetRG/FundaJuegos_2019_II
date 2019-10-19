#include "Player.h"
#include <SDL\SDL.h>

Player::Player()
{
}

void Player::init(float _speed,
	glm::vec2 _position, InputManager* _inputManager, string im_url) {
	inputManager = _inputManager;
	speed = _speed;
	position = _position;
	color.r = 240;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	imageURL = im_url;
}

void Player::update() {
	if (inputManager->isKeyPressed(SDLK_UP)) {
		position.y += speed;
	}

	if (inputManager->isKeyPressed(SDLK_DOWN)) {
		position.y -= speed;
	}

	if (inputManager->isKeyPressed(SDLK_LEFT)) {
		position.x -= speed;
	}

	if (inputManager->isKeyPressed(SDLK_RIGHT)) {
		position.x += speed;
	}
	
	if (alphaWay) {
		color.a -= 1;
		if (color.a < 1) alphaWay = false;
	}else{
		color.a += 1;
		if (color.a > 254) alphaWay = true;
	}
}

void Player::setPosition(glm::vec2 _position)
{
	position = _position;
}


Player::~Player()
{
}
