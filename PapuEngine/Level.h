#pragma once
#include <string>
#include <vector>
#include "SpriteBacth.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

const int TILE_WIDTH = 64;

class Level
{
private:
	vector<string> levelData;
	int numHumans;
	void parseLevel();
	vector<glm::vec2> freeSpaces;
public:
	Level(const string& filename);
	glm::vec2 playerPosition;
	vector<glm::vec2> zombiesPosition;
	glm::vec2 getPlayerPosition() const {
		return playerPosition;
	}
	vector<glm::vec2> getZombiesPosition()const {
		return zombiesPosition;
	}
	glm::vec2 getRandomFreePosition();
	void draw();
	SpriteBacth spritebatch;
	~Level();
};

