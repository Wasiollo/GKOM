#pragma once

#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
class Generate
{
public:
	Generate();
	~Generate();
	 std::vector<GLfloat> generateOctangular(float radius, float height, float* color);
	 std::vector<GLfloat> generateNOctangulars(int n, float radius, float height, float * color);
	 std::vector<GLuint> generateConnections(int begin, int count);
};

