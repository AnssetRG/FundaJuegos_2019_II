#pragma once
#include "Human.h"
#include "InputManager.h"

class Player : public Human
{
private:
	InputManager* inputManager;
	bool alphaWay = true;
public:
	Player();
	~Player();
	void init(float _speed, 
			glm::vec2 _position, InputManager* _inputManager, string im_url);
	void update();
	void setPosition(glm::vec2 _position);
};

