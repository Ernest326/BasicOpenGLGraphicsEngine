#pragma once

#include <iostream>
#include <vector>

#include <GL\glew.h>

#include <stb_image.h>

class Cubemap
{
private:

	unsigned int m_textureID;

public:

	Cubemap(char* right, char* left, char* top, char* bottom, char* front, char* back, bool linear);

	int getCubemap() { return m_textureID; }


};

