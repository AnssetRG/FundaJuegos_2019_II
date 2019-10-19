#include "Zombie.h"



void Zombie::init(glm::vec2 _position, string im_url)
{
	position = _position;
	color.r = 240;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	imageURL = im_url;
}

void Zombie::update()
{
}

Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}
