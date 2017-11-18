#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL.h>
#include "Shader.hpp"
#include "Polygon.hpp"


class Base {
public:
	GLfloat height;
	GLfloat radius;
	Shader ourShader;
	Texture brickText;
	std::vector<Polygon> octangulars;
	std::vector<Polygon> bottomFloorWalls;
	//std::vector<Polygon> nextfloors;

	Base(GLfloat height_, GLfloat radius_, Texture& brickText_, Texture & oldWoodText_, Shader ourShader_) :
		height(height_),
		radius(radius_),
		brickText(brickText_),
		ourShader(ourShader_) {}
	void init() {
		octangulars.push_back(Polygon(8, brickText, 0.0f, ourShader));
		octangulars[0].init();

		octangulars[0].translate(glm::vec3(0, height, 0));
		octangulars[0].rotate(90, glm::vec3(1, 0, 0));
		octangulars[0].scale(glm::vec3(radius, radius, 1));
		
			for (unsigned i = 0; i < 3; ++i) {
				bottomFloorWalls.push_back(Polygon(4, brickText, 0.0f, ourShader));
				bottomFloorWalls[i].init();

				//bottomFloorWalls[i].translate(glm::vec3(20, 5.0f*i+5.0, 0));
				bottomFloorWalls[i].rotate(90 * (GLfloat)i, glm::vec3(0, 1, 0));
				bottomFloorWalls[i].translate(glm::vec3(2*radius, radius / 4*3 + height, 0));
				bottomFloorWalls[i].rotate(90, glm::vec3(0, 1, 0));
				bottomFloorWalls[i].scale(glm::vec3(radius, radius / 4 * 3, 1));
			}
			for (unsigned i = 3; i < 7; ++i) {
				bottomFloorWalls.push_back(Polygon(4, brickText, 0.0f, ourShader));
				bottomFloorWalls[i].init();

				//bottomFloorWalls[i].translate(glm::vec3(20, 5.0f*i+5.0, 0));
				bottomFloorWalls[i].rotate(45+90 * (GLfloat)i, glm::vec3(0, 1, 0));
				bottomFloorWalls[i].translate(glm::vec3(sqrt(2)*3/2*radius, radius / 4*3 + height, 0));
				bottomFloorWalls[i].rotate(90, glm::vec3(0, 1, 0));
				bottomFloorWalls[i].scale(glm::vec3(radius/2*sqrt(2), radius / 4 * 3, 1));
			}
			bottomFloorWalls.push_back(Polygon(4, brickText, 0.0f, ourShader));
			bottomFloorWalls[7].init();

			//bottomFloorWalls[i].translate(glm::vec3(20, 5.0f*i+5.0, 0));
			bottomFloorWalls[7].rotate(270, glm::vec3(0, 1, 0));
			bottomFloorWalls[7].translate(glm::vec3(2 * radius, radius / 4*3 + height, 0));
			bottomFloorWalls[7].rotate(90, glm::vec3(0, 1, 0));
			bottomFloorWalls[7].translate(glm::vec3(radius / 3 * 2, 0, 0));
			bottomFloorWalls[7].scale(glm::vec3(radius/3, radius / 4 * 3, 1));

			bottomFloorWalls.push_back(Polygon(4, brickText, 0.0f, ourShader));
			bottomFloorWalls[8].init();

			//bottomFloorWalls[i].translate(glm::vec3(20, 5.0f*i+5.0, 0));
			bottomFloorWalls[8].rotate(270, glm::vec3(0, 1, 0));
			bottomFloorWalls[8].translate(glm::vec3(2 * radius, radius /4*3 + height, 0));
			bottomFloorWalls[8].rotate(90, glm::vec3(0, 1, 0));
			bottomFloorWalls[8].translate(glm::vec3(-radius / 3 * 2, 0, 0));
			bottomFloorWalls[8].scale(glm::vec3(radius/3, radius / 4 * 3, 1));
		
	}
	

	void draw() {
		octangulars[0].draw();

		for (unsigned i = 0; i < 9; ++i) 
		{
			
			bottomFloorWalls[i].draw();
		}

	}
	
};


class NextFloor {
	GLfloat height;
	GLuint number;
	GLfloat radius;
	Shader ourShader;
	Texture oldWoodText;
	std::vector<Polygon> quadrangles;
public :
	NextFloor(GLfloat height_, GLuint number_, GLfloat radius_, Texture & oldWoodText_, Shader ourShader_) :
		height(height_),
		number(number_),
		radius(radius_),
		oldWoodText(oldWoodText_),
		ourShader(ourShader_) {}

	void init() {
		for (int i = 0; i < 8; i += 2)
		{
			quadrangles.push_back(Polygon(4, oldWoodText, 0.0f, ourShader));
			quadrangles[i].init();
			quadrangles[i].rotate(45 * (GLfloat)i, glm::vec3(0, 1, 0));
			quadrangles[i].translate(glm::vec3(2 * radius, radius * 9 / 4 + radius / 2 * 3 * number, 0));
			quadrangles[i].rotate(90, glm::vec3(0, 1, 0));
			quadrangles[i].scale(glm::vec3(radius, radius / 4 * 3, 1));

			quadrangles.push_back(Polygon(4, oldWoodText, 0.0f, ourShader));
			quadrangles[i + 1].init();
			quadrangles[i + 1].rotate(45 + 45 * (GLfloat)i, glm::vec3(0, 1, 0));
			quadrangles[i + 1].translate(glm::vec3(sqrt(2) * 3 / 2 * radius, radius * 9 / 4 + radius / 2 * 3 * number, 0));
			quadrangles[i + 1].rotate(90, glm::vec3(0, 1, 0));
			quadrangles[i + 1].scale(glm::vec3(radius / 2 * sqrt(2), radius / 4 * 3, 1));

		}
	}

	void draw() {
		for (unsigned i = 0; i < 8; ++i)
		{
			quadrangles[i].draw();
		}
	}
};


class WoodAround {
public:
	GLfloat number;
	GLfloat radius;
	Shader ourShader;
	Texture woodText;
	std::vector<Polygon> verticalBoard;
	std::vector<Polygon> horizontalBoard;

	WoodAround(GLfloat number_, GLfloat radius_, Texture & woodText_, Shader ourShader_) :
		number(number_),
		radius(radius_),
		woodText(woodText_),
		ourShader(ourShader_) {}

	void init() {
		for (unsigned i = 0; i < 8; i+=2) 
		{
			verticalBoard.push_back(Polygon(2, woodText, 0.0f, ourShader));
			verticalBoard[i].init();

			//bottomFloorWalls[i].translate(glm::vec3(20, 5.0f*i+5.0, 0));
			verticalBoard[i].rotate(90 * (i/2), glm::vec3(0, 1, 0));
			verticalBoard[i].translate(glm::vec3(2 * radius, radius / 4 * 3 + number * radius / 2 * 3, radius/4*3 ));
			verticalBoard[i].rotate(90, glm::vec3(0, 1, 0));
			verticalBoard[i].scale(glm::vec3(radius / 20, radius / 4 * 3, 1));
						
			verticalBoard.push_back(Polygon(2, woodText, 0.0f, ourShader));
			verticalBoard[i + 1].init();

			//bottomFloorWalls[i].translate(glm::vec3(20, 5.0f*i+5.0, 0));
			verticalBoard[i + 1].rotate(90 * (i/2), glm::vec3(0, 1, 0));
			verticalBoard[i + 1].translate(glm::vec3(2 * radius , radius / 4 * 3 + number * radius / 2 * 3, -radius/4*3));
			verticalBoard[i + 1].rotate(90, glm::vec3(0, 1, 0));
			verticalBoard[i + 1].scale(glm::vec3(radius / 20, radius / 4 * 3, 1));
		}

		for (unsigned i = 0; i < 8; i += 2)
		{
			horizontalBoard.push_back(Polygon(2, woodText, 0.0f, ourShader));
			horizontalBoard[i].init();

			//bottomFloorWalls[i].translate(glm::vec3(20, 5.0f*i+5.0, 0));
			horizontalBoard[i].rotate(45 * i, glm::vec3(0, 1, 0));
			horizontalBoard[i].translate(glm::vec3(2 * radius , radius * 6 / 4 + radius / 2 * 3 * number, 0));
			horizontalBoard[i].rotate(90, glm::vec3(1, 0, 0));
			horizontalBoard[i].rotate(90, glm::vec3(0, 1, 0));
			horizontalBoard[i].scale(glm::vec3(radius/20, radius, 1));

			horizontalBoard.push_back(Polygon(2, woodText, 0.0f, ourShader));
			horizontalBoard[i + 1].init();

			horizontalBoard[i + 1].rotate(45 + 45 * i, glm::vec3(0, 1, 0));
			horizontalBoard[i + 1].translate(glm::vec3(sqrt(2) * 3 / 2 * radius, radius * 6 / 4 + radius / 2 * 3 * number, 0));
			horizontalBoard[i + 1].rotate(90, glm::vec3(1, 0, 0));
			horizontalBoard[i + 1].rotate(90, glm::vec3(0, 1, 0));
			horizontalBoard[i + 1].scale(glm::vec3(radius / 20, radius/sqrt(2), 1));
		}

	}


	void draw() {
		for (unsigned i = 0; i < 8; ++i)
		{

			verticalBoard[i].draw();
			horizontalBoard[i].draw();
		}
	}

};


class Roof {
public:
	GLfloat height;
	GLfloat radius;
	Shader ourShader;
	Texture roofWoodText;
	std::vector<Polygon> woodRoof;

	Roof(GLfloat height_, GLfloat radius_, Texture & roofWoodText_, Shader ourShader_) :
		height(height_),
		radius(radius_),
		roofWoodText(roofWoodText_),
		ourShader(ourShader_) {}

	void init() {
		woodRoof.push_back(Polygon(9, roofWoodText, 0.0f, ourShader));
		woodRoof[0].init();

		woodRoof[0].translate(glm::vec3(0, radius * 3 / 2 + radius / 2 * 3 * height, 0));
		woodRoof[0].rotate(-90, glm::vec3(1, 0, 0));
		woodRoof[0].scale(glm::vec3(radius, radius, radius*2.5));
	}

	void draw() {
			woodRoof[0].draw();
	}
};

class Shovel {
public:
	GLfloat height;
	GLfloat radius;
	GLfloat width;
	Shader ourShader;
	Texture roofWoodText;
	std::vector<Polygon> shovel;

	Shovel(GLfloat height_, GLfloat radius_,GLfloat width_,  Texture & roofWoodText_, Shader ourShader_) :
		height(height_),
		width(width_),
		radius(radius_),
		roofWoodText(roofWoodText_),
		ourShader(ourShader_) {}

	void init() {
		shovel.push_back(Polygon(4, roofWoodText, 0.0f, ourShader));
		shovel[0].init();
		
		shovel[0].translate(glm::vec3(0, radius / 2 * 3 * height, radius*2.2+width));
		shovel[0].rotate(45, glm::vec3(0, 0, 1));
		shovel[0].scale(glm::vec3(radius * 4, radius / 3, 1));

		shovel.push_back(Polygon(4, roofWoodText, 0.0f, ourShader));
		shovel[1].init();

		shovel[1].translate(glm::vec3(0, radius / 2 * 3 * height, radius*2.21+width));
		shovel[1].rotate(-45, glm::vec3(0, 0, 1));
		shovel[1].scale(glm::vec3(radius * 4, radius / 3, 1));
	}

	void rotate(float angle) {
		double temp1 = radius * 4;
		double temp2 = 1 / (radius * 4);
		double temp3 = radius / 3;
		double temp4 = 1 / (radius / 3);
		shovel[0].scale(glm::vec3(temp2, temp4, 1));
		shovel[1].scale(glm::vec3(temp2,  temp4, 1));
		shovel[0].rotate(angle, glm::vec3(0, 0, 1));
		shovel[1].rotate(angle, glm::vec3(0, 0, 1));
		shovel[0].scale(glm::vec3(temp1, temp3, 1));
		shovel[1].scale(glm::vec3(temp1, temp3, 1));
	}

	void draw() {
		shovel[0].draw();
		shovel[1].draw();
	}
};



class WalkPath
{
public:
	
	GLfloat radius;
	Shader ourShader;
	Texture sandText;
	std::vector<Polygon> walkBox;

	WalkPath( GLfloat radius_, Texture & sandText_, Shader ourShader_) :
		radius(radius_),
		sandText(sandText_),
		ourShader(ourShader_) {}

	void init() {
		for (unsigned i = 0; i < 4; ++i)
		{
			walkBox.push_back(Polygon(4, sandText, 0.1f, ourShader));
			walkBox[i].init();

			walkBox[i].rotate(-90, glm::vec3(0, 1, 0));

			walkBox[i].translate(glm::vec3(3* radius + 2*radius*i ,0.1, 0));
			walkBox[i].rotate(90, glm::vec3(1, 0, 0));
			walkBox[i].rotate(90, glm::vec3(0, 0, 1));

			walkBox[i].scale(glm::vec3(radius, radius, 1));
		}
	}

	void draw()
	{
		for (unsigned i = 0; i < 4; ++i)
		{
			walkBox[i].draw();
		}
	}
};


class Quern {
public:
	GLfloat radius;
	GLfloat height;
	Shader ourShader;
	Texture stoneText;
	std::vector<Polygon> quernOct;
	std::vector<Polygon> quernQuad;
	Quern(GLfloat height_,GLfloat radius_, Texture & stoneText_, Shader ourShader_) :
		height(height_),
		radius(radius_),
		stoneText(stoneText_),
		ourShader(ourShader_) {}

	void init() {
		
			quernOct.push_back(Polygon(8, stoneText, 0.1f, ourShader));
			quernOct[0].init();
			quernOct[0].rotate(-90, glm::vec3(1, 0, 0));
			quernOct[0].translate(glm::vec3(0, 0, height+radius));

			quernOct[0].scale(glm::vec3(radius , radius , 1));
		
			quernOct.push_back(Polygon(8, stoneText, 0.1f, ourShader));
			quernOct[1].init();
			quernOct[1].rotate(-90, glm::vec3(1, 0, 0));
			quernOct[1].translate(glm::vec3(0, 0, height));

			quernOct[1].scale(glm::vec3(radius , radius , 1));

			for (unsigned i = 0; i < 8; i+=2)
			{
				quernQuad.push_back(Polygon(4, stoneText, 0.0f, ourShader));
				quernQuad[i].init();
				quernQuad[i].rotate(45 * (GLfloat)i, glm::vec3(0, 1, 0));
				quernQuad[i].translate(glm::vec3(2 * radius, height+radius/2, 0));
				quernQuad[i].rotate(90, glm::vec3(0, 1, 0));
				quernQuad[i].scale(glm::vec3(radius, radius / 2, 1));

				quernQuad.push_back(Polygon(4, stoneText, 0.0f, ourShader));
				quernQuad[i + 1].init();
				quernQuad[i + 1].rotate(45 + 45 * (GLfloat)i, glm::vec3(0, 1, 0));
				quernQuad[i + 1].translate(glm::vec3(sqrt(2) * 3 / 2 * radius, height + radius /2 , 0));
				quernQuad[i + 1].rotate(90, glm::vec3(0, 1, 0));
				quernQuad[i + 1].scale(glm::vec3(radius / 2 * sqrt(2), radius / 2, 1));
			}

	}

	void rotate(float angle)
	{
		quernOct[0].scale(glm::vec3(1/radius, 1/radius, 1));
		quernOct[1].scale(glm::vec3(1/radius, 1/radius, 1));
		quernOct[0].rotate(angle, glm::vec3(0, 0, 1));
		quernOct[1].rotate(angle, glm::vec3(0, 0, 1));
		quernOct[0].scale(glm::vec3( radius, radius, 1));
		quernOct[1].scale(glm::vec3(radius, radius, 1));

		for (unsigned i = 0; i < 8; i += 2)
		{
			quernQuad[i].scale(glm::vec3(1/radius, 1/( radius / 2), 1));
			quernQuad[i].rotate(-90, glm::vec3(0, 1, 0));
			quernQuad[i].translate(glm::vec3(-2 * radius,-( height + radius / 2), 0));
			quernQuad[i].rotate(angle, glm::vec3(0, 1, 0));

			quernQuad[i].translate(glm::vec3(2 * radius, height + radius / 2, 0));
			quernQuad[i].rotate(90, glm::vec3(0, 1, 0));
			quernQuad[i].scale(glm::vec3(radius, radius / 2, 1));

			quernQuad[i + 1].scale(glm::vec3(1/(radius / 2 * sqrt(2)),1/( radius / 2), 1));
			quernQuad[i + 1].rotate(-90, glm::vec3(0, 1, 0));
			quernQuad[i + 1].translate(glm::vec3(-(sqrt(2) * 3 / 2 * radius),-( height + radius / 2), 0));
			quernQuad[i+1].rotate(angle, glm::vec3(0, 1, 0));

			quernQuad[i + 1].translate(glm::vec3(sqrt(2) * 3 / 2 * radius, height + radius / 2, 0));
			quernQuad[i + 1].rotate(90, glm::vec3(0, 1, 0));
			quernQuad[i + 1].scale(glm::vec3(radius / 2 * sqrt(2), radius / 2, 1));
		}

	}

	void draw()
	{
			quernOct[0].draw();
			quernOct[1].draw();
			for (unsigned i = 0; i < 8;++i)
				quernQuad[i].draw();
		
	}
};



class WoodQuern {
public:
	GLfloat radius;
	GLfloat height;
	Shader ourShader;
	Texture woodText;
	std::vector<Polygon> quernQuad;
	WoodQuern(GLfloat height_, GLfloat radius_, Texture & woodText_, Shader ourShader_) :
		height(height_),
		radius(radius_),
		woodText(woodText_),
		ourShader(ourShader_) {}

	void init() {

		
		for (unsigned i = 0; i < 4; ++i)
		{
			quernQuad.push_back(Polygon(4, woodText, 0.0f, ourShader));
			quernQuad[i].init();
			quernQuad[i].rotate(90 * (GLfloat)i, glm::vec3(0, 1, 0));
			quernQuad[i].translate(glm::vec3(radius / 10, height + radius * 10, 0));
			quernQuad[i].rotate(90, glm::vec3(0, 1, 0));
			quernQuad[i].scale(glm::vec3(radius / 10, radius * 10, 1));

		}

		for (unsigned i = 4; i < 8; ++i)
		{
			quernQuad.push_back(Polygon(4, woodText, 0.0f, ourShader));
			quernQuad[i].init();
			quernQuad[i].rotate(90, glm::vec3(0, 0, 1));
			quernQuad[i].translate(glm::vec3(height + radius * 20, 0, radius*4));
			quernQuad[i].rotate(90, glm::vec3(1, 0, 0));
			
			quernQuad[i].rotate(90 * (GLfloat)i, glm::vec3(0, 1, 0));
			
			quernQuad[i].translate(glm::vec3(0, 0, radius/10));

			quernQuad[i].scale(glm::vec3(radius / 10, radius * 4.5, 1));

		}

		quernQuad.push_back(Polygon(4, woodText, 0.0f, ourShader));
		quernQuad[8].init();
		quernQuad[8].translate(glm::vec3(0, height + radius * 20, 0));
		quernQuad[8].rotate(90, glm::vec3(1, 0, 0));
		quernQuad[8].scale(glm::vec3(radius / 10, radius /10, 1));
		quernQuad.push_back(Polygon(4, woodText, 0.0f, ourShader));
		quernQuad[9].init();
		quernQuad[9].translate(glm::vec3(0, height + radius * 20, -radius/2));
		quernQuad[9].scale(glm::vec3(radius / 10, radius / 10, 1));
		quernQuad.push_back(Polygon(4, woodText, 0.0f, ourShader));
		quernQuad[10].init();
		quernQuad[10].translate(glm::vec3(0, height + radius * 20, radius*8.5));
		quernQuad[10].scale(glm::vec3(radius / 10, radius / 10, 1));

	}

	void rotate(float angle)
	{

		for (unsigned i = 0; i < 4; ++i)
		{
			quernQuad[i].scale(glm::vec3(1 / (radius/10), 1 / (radius * 10), 1));
			quernQuad[i].rotate(-90, glm::vec3(0, 1, 0));
			quernQuad[i].translate(glm::vec3(-radius/10, -(height + radius *10), 0));
			quernQuad[i].rotate(angle, glm::vec3(0, 1, 0));
			quernQuad[i].translate(glm::vec3(radius/10, height + radius * 10, 0));
			quernQuad[i].rotate(90, glm::vec3(0, 1, 0));
			quernQuad[i].scale(glm::vec3(radius/10, radius * 10, 1));
		}
		
		for (unsigned i = 4; i < 8; ++i)
		{
		
		quernQuad[i].scale(glm::vec3(1/(radius / 10), 1/(radius * 5), 1));


		quernQuad[i].translate(glm::vec3(0, 0, -radius/10));

		quernQuad[i].rotate(angle, glm::vec3(0, 1, 0));

		quernQuad[i].translate(glm::vec3(0, 0, radius/10));
			
			quernQuad[i].scale(glm::vec3(radius / 10, radius * 5, 1));


		}



		quernQuad[8].scale(glm::vec3(1/(radius / 10), 1/(radius / 10), 1));

		quernQuad[8].rotate(-angle, glm::vec3(0, 0, 1));
		quernQuad[8].scale(glm::vec3(radius / 10, radius / 10, 1));
		quernQuad[9].scale(glm::vec3(1 / (radius / 10), 1 / (radius / 10), 1));

		quernQuad[9].rotate(angle, glm::vec3(0, 0, 1));
		quernQuad[9].scale(glm::vec3(radius / 10, radius / 10, 1));
		quernQuad[10].scale(glm::vec3(1 / (radius / 10), 1 / (radius / 10), 1));

		quernQuad[10].rotate(angle, glm::vec3(0, 0, 1));
		quernQuad[10].scale(glm::vec3(radius / 10, radius / 10, 1));



	}
	void draw() {
		for (unsigned i = 0; i < 11; ++i)
		{
			quernQuad[i].draw();
		}
	}
};



class Gate
{
public:
	GLfloat height;
	GLfloat radius;
	Shader ourShader;
	Texture brickText;
	Texture woodText;
	
	std::vector<Polygon> Walls;

	Gate(GLfloat height_, GLfloat radius_, Texture& brickText_, Texture & woodText_, Shader ourShader_) :
		height(height_),
		radius(radius_),
		woodText(woodText_),
		brickText(brickText_),
		ourShader(ourShader_) {}
	void init() {
		
		Walls.push_back(Polygon(4, brickText, 0.0f, ourShader));
		Walls[0].init();

		Walls[0].rotate(270, glm::vec3(0, 1, 0));
		Walls[0].translate(glm::vec3(2 * radius, radius / 4 * 3 + height, 0));
		Walls[0].translate(glm::vec3(0, 0, radius / 3 * 1));
		Walls[0].rotate(-9, glm::vec3(0, 1, 0));
		Walls[0].scale(glm::vec3(radius / 14, radius / 4 * 3, 1));

		Walls.push_back(Polygon(4, brickText, 0.0f, ourShader));
		Walls[1].init();

		Walls[1].rotate(270, glm::vec3(0, 1, 0));
		Walls[1].translate(glm::vec3(2 * radius, radius / 4 * 3 + height, 0));
		Walls[1].translate(glm::vec3(0, 0, -radius / 3 * 1));
		Walls[1].rotate(9, glm::vec3(0, 1, 0));
		Walls[1].scale(glm::vec3(radius / 14, radius / 4 * 3, 1));
		
		Walls.push_back(Polygon(4, woodText, 0.0f, ourShader));
		Walls[2].init();

		Walls[2].rotate(270, glm::vec3(0, 1, 0));
		Walls[2].translate(glm::vec3(2 * radius, radius / 2 * 3 + height, 0));
		Walls[2].rotate(90, glm::vec3(1, 0, 0));
		Walls[2].scale(glm::vec3(radius / 14, radius / 4 * 3, 1));
	}


	void draw() {

		for (unsigned i = 0; i < 3; ++i)
		{

			Walls[i].draw();
		}

	}

};


class Door {
public:
	GLfloat height;
	GLfloat radius;
	Shader ourShader;
	Texture doorText;

	std::vector<Polygon> door;

	Door(GLfloat height_, GLfloat radius_, Texture & doorText_, Shader ourShader_) :
		height(height_),
		radius(radius_),
		doorText(doorText_),
		ourShader(ourShader_) {}
	void init() {
		door.push_back(Polygon(4, doorText, 0.0f, ourShader));
		door[0].init();

		door[0].rotate(270, glm::vec3(0, 1, 0));
		door[0].translate(glm::vec3(2 * radius+radius/6*sqrt(2), radius / 4 * 3, 0));
		door[0].rotate(90, glm::vec3(0, 1, 0));
		door[0].translate(glm::vec3(-radius / 6, 0, 0));
		door[0].rotate(-45, glm::vec3(0, 1, 0));
		door[0].scale(glm::vec3(radius / 3, radius / 4 * 3, 1));
	}


	void draw() {
			door[0].draw();
	}
};


class Window {
public:
	GLfloat height;
	GLfloat radius;
	Shader ourShader;
	Texture windowText;

	std::vector<Polygon> windows;

	Window(GLfloat height_, GLfloat radius_, Texture & windowText_, Shader ourShader_) :
		height(height_),
		radius(radius_),
		windowText(windowText_),
		ourShader(ourShader_) {}
	void init() {
		windows.push_back(Polygon(4, windowText, 0.0f, ourShader));
		windows[0].init();

		windows[0].rotate(270, glm::vec3(0, 1, 0));
		windows[0].translate(glm::vec3(2 * radius, radius / 2 * 1+2*radius/2*3, 0));
		windows[0].rotate(90, glm::vec3(0, 1, 0));
		windows[0].translate(glm::vec3(-radius / 3, 0, 0));
		
		windows[0].scale(glm::vec3(radius / 5, radius / 8 * 3, 1));


		windows.push_back(Polygon(4, windowText, 0.0f, ourShader));
		windows[1].init();

		windows[1].rotate(315, glm::vec3(0, 1, 0));
		windows[1].translate(glm::vec3(sqrt(2) * 3 / 2 * radius, radius / 2 * 1 + radius / 2 * 3, 0));
		windows[1].rotate(90, glm::vec3(0, 1, 0));
		windows[1].translate(glm::vec3(-radius / 3, 0, 0));

		windows[1].scale(glm::vec3(radius / 5, radius / 8 * 3, 1));

		windows.push_back(Polygon(4, windowText, 0.0f, ourShader));
		windows[2].init();

		
		windows[2].rotate(315, glm::vec3(0, 1, 0));
		windows[2].translate(glm::vec3(sqrt(2) * 3 / 2 * radius, radius / 2 * 1 + 3 * radius / 2 * 3, 0));
		windows[2].rotate(90, glm::vec3(0, 1, 0));
		windows[2].translate(glm::vec3(radius / 3, 0, 0));

		windows[2].scale(glm::vec3(radius / 5, radius / 8 * 3, 1));

		windows.push_back(Polygon(4, windowText, 0.0f, ourShader));
		windows[3].init();

		
		windows[3].rotate(225, glm::vec3(0, 1, 0));
		windows[3].translate(glm::vec3(sqrt(2) * 3 / 2 * radius, radius / 2 * 1 + 4 * radius / 2 * 3, 0));
		windows[3].rotate(90, glm::vec3(0, 1, 0));
		windows[3].translate(glm::vec3(radius / 6, 0, 0));

		windows[3].scale(glm::vec3(radius / 5, radius / 8 * 3, 1));
			}


	void draw() {
		windows[0].draw();
		windows[1].draw();
		windows[2].draw();
		windows[3].draw();
	}
};