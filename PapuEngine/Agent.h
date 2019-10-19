#pragma once
#include <glm\glm.hpp>
#include "SpriteBacth.h"
#include "GLTexture.h"
#include <string>

using namespace std;

const int AGENT_WIDTH = 60;

class Agent
{
protected:
	glm::vec2 position;
	float speed;
	Color color;
	string imageURL;
public:
	Agent();
	glm::vec2 getPosition() const { return position; };
	virtual void update() = 0;
	void draw(SpriteBacth& spritebatch);
	virtual ~Agent();
};

