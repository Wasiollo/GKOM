#include "Generate.h"



Generate::Generate()
{
}

std::vector<GLfloat> Generate::generateOctangular(float radius, float height, float* color)
{
	std::vector<GLfloat> result = { 
		
		radius*2.0f, radius*1.0f, height*1.0f, color[0] * 1.0f, color[1] * 1.0f, color[2] * 1.0f, 1.0f, 0.0f,
		radius*2.0f, radius*(-1.0f), height*1.0f, color[0] * 1.0f, color[1] * 1.0f, color[2] * 1.0f, 0.0f, 0.0f,
		radius*1.0f, radius*(-2.0f), height*1.0f, color[0] * 1.0f, color[1] * 1.0f, color[2] * 1.0f,  1.0f,0.0f,
		radius*(-1.0f), radius*(-2.0f), height*1.0f, color[0] * 1.0f, color[1] * 1.0f, color[2] * 1.0f, 0.0f, 0.0f,
		radius*(-2.0f), radius*(-1.0f), height*1.0f, color[0] * 1.0f, color[1] * 1.0f, color[2] * 1.0f, 1.0f, 0.0f,
		radius*(-2.0f), radius*1.0f, height*1.0f, color[0] * 1.0f, color[1] * 1.0f, color[2] * 1.0f, 0.0f,0.0f,
		radius*(-1.0f), radius*2.0f, height*1.0f, color[0] * 1.0f, color[1] * 1.0f, color[2] * 1.0f, 1.0f,0.0f,
		radius*1.0f, radius*2.0f, height*1.0f, color[0] * 1.0f, color[1] * 1.0f, color[2] * 1.0f, 1.0f, 0.0f,
	};
	std::cout <<

		radius*2.0f << " " << radius*1.0f << " " << height*1.0f << " " << color[0] << " " << color[1] << " " << color[2] << " " << color[3] << " " << color[4] << std::endl <<
		radius*2.0f << " " << radius*(-1.0f) << " " << height*1.0f << " " << color[0] << " " << color[1] << " " << color[2] << " " << color[3] << " " << color[4] << std::endl <<
		radius*1.0f << " " << radius*(-2.0f) << " " << height*1.0f << " " << color[0] << " " << color[1] << " " << color[2] << " " << color[3] << " " << color[4] << std::endl <<
		radius*(-1.0f) << " " << radius*(-2.0f) << " " << height*1.0f << " " << color[0] << " " << color[1] << " " << color[2] << " " << color[3] << " " << color[4] << std::endl <<
		radius*(-2.0f) << " " << radius*(-1.0f) << " " << height*1.0f << " " << color[0] << " " << color[1] << " " << color[2] << " " << color[3] << " " << color[4] << std::endl <<
		radius*(-2.0f) << " " << radius*1.0f << " " << height*1.0f << " " << color[0] << " " << color[1] << " " << color[2] << " " << color[3] << " " << color[4] << std::endl <<
		radius*(-1.0f) << " " << radius*2.0f << " " << height*1.0f << " " << color[0] << " " << color[1] << " " << color[2] << " " << color[3] << " " << color[4] << std::endl <<
		radius*1.0f << " " << radius*2.0f << " " << height*1.0f << " " << color[0] << " " << color[1] << " " << color[2] << " " << color[3] << " " << color[4] << std::endl;
	return result;
}
std::vector<GLfloat> Generate::generateNOctangulars(int n, float radius, float height, float* color)
{
	std::vector<GLfloat> result = generateOctangular(radius, height*0, color);
	for (int i = 1; i <= n; ++i)
	{
		std::vector<GLfloat> temp = generateOctangular(radius, height*i, color);
		result.insert(result.end(), temp.begin(), temp.end());
	}
	return result;
}
std::vector<GLuint> Generate::generateConnections(int begin, int count)
{
	std::vector<GLuint> result;
	for (int i = 0; i < count; ++i)
	{
		result.push_back(begin + i);
		result.push_back(begin + ( i + 1)%(count));
		result.push_back(begin + count + i);
	}
	for (int i = 0; i < count; ++i)
	{
		result.push_back(begin + (i + 1)%(count));
		result.push_back(begin + count + i);
		result.push_back(count + begin + (i + 1)%(count));
	}
	return result; 
}


Generate::~Generate()
{}
