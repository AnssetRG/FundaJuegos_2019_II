#pragma once
#include <GL\glew.h>
#include <string>
#include "GLTexture.h"
#include "SpriteBacth.h"

using namespace std;

const int SPRITE_WIDTH = 60;

class Sprite
{
private:
	glm::vec2 position;
	float _x;
	float _y;
	int _width;
	int _height;
	float vertexData;
	GLuint _vobID;
	GLTexture _texture;
	Color color;
	string _texturePath;
public:
	Sprite();
	~Sprite();
	void init(float x, float y, glm::vec2 _position, int width, int height, string texturePath);
	//void draw();
	void draw(SpriteBacth& spritebatch);

	
};

