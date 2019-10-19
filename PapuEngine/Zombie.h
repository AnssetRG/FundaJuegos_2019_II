#pragma once
#include "Agent.h"

class Zombie : public Agent
{
public:
	void init(glm::vec2 _position, string im_url);
	void update();
	Zombie();
	~Zombie();
};

