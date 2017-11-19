#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Polygon.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Generator.hpp"

//window size
GLuint screenWidth = 1920, screenHeight = 1080;
// Camera
Camera camera(glm::vec3(18.0f, 21.0f, 66.0f), screenWidth, screenHeight);
//pressed keys array
bool keys[1024];
//mouse position in last iteration
GLfloat lastX = (GLfloat)screenHeight / 2, lastY = (GLfloat)screenWidth / 2;
//indicate if it is first mouse move
bool firstMouse = true;
//height and widht of the scene
GLfloat sceneHeight = 1000.0;
GLfloat sceneWidht = 5000.0;

// init GLFW window
GLFWwindow* initWindow(int antiAliasLevel, GLFWkeyfun key_callback, GLFWcursorposfun mouse_callback) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, antiAliasLevel);
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "WasiolloGKOM", nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(window);
	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	// Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();
	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);
	//anti alias
	glEnable(GL_MULTISAMPLE);
	return window;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

//call when mouse is moved
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = (GLfloat)xpos;
		lastY = (GLfloat)ypos;
		firstMouse = false;
	}
	GLfloat xoffset = GLfloat(xpos - lastX);
	GLfloat yoffset = GLfloat(lastY - ypos);  // Reversed since y-coordinates go from bottom to left
	lastX = (GLfloat)xpos;
	lastY = (GLfloat)ypos;
	camera.rotate(xoffset, yoffset);
}


int main()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Init GLFW
	GLFWwindow* window = initWindow(8, key_callback, mouse_callback);
	// Setup and compile our shaders
	Shader ourShader("vertex.shd", "fragment.shd");
	//define objects on the scene
	//vertices
	GLfloat grassVs[] = { 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,1500.0f,  0.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,1500.0f,1500.0f,
		-1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   0.0f,   0.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   0.0f,1500.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,1500.0f,1500.0f,
		-1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   0.0f,   0.0f,
	};
	GLfloat cloudsVs[] = { 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	};

	

	//textures
	Texture grassText("grass.png");
	Texture cloudsText("clouds2.png");
	Texture skyText("sky2.png");
	Texture brickText("brick.png");
	Texture oldWoodText("oldWood.png");
	Texture woodBoardText("oldWoodBoard2.png");
	Texture woodRoofText("wood_roof_texture.png");
	Texture windBladeText("windBlade.png");
	Texture sandText("sand.png");
	Texture stoneText("stoneText.png");
	Texture pathText("path.png");
	Texture doorText("door3.png");
	Texture windowText("window.png");
	Texture ledderText("ledder.png");
	//create grass
	Polygon grass(grassVs, 6, grassText, 0.2f, ourShader);
	grass.init();
	grass.rotate(90, glm::vec3(1, 0, 0));
	grass.scale(glm::vec3(sceneWidht, sceneWidht, 1.0));
	//create clouds and sky
	
	//Base base(glm::vec3(10, 0.1, 0), 90, glm::vec3(1, 0, 0), glm::vec3(10, 10, 1));

	Base base(0.1,7,brickText, oldWoodText, ourShader);
	base.init();
	NextFloor firstFloor(5, 0, 7, oldWoodText, ourShader);
	firstFloor.init();
	NextFloor secFloor(5, 1, 7, oldWoodText, ourShader);
	secFloor.init();
	NextFloor thirFloor(5, 2, 7, oldWoodText, ourShader);
	thirFloor.init();
	NextFloor fourFloor(5, 3, 7, oldWoodText, ourShader);
	fourFloor.init();
	
	WoodAround woodInside1(0, 6.99, woodBoardText, ourShader);
	woodInside1.init();
	WoodAround woodInside2(1, 6.99, woodBoardText, ourShader);
	woodInside2.init();
	WoodAround woodInside3(2, 6.99, woodBoardText, ourShader);
	woodInside3.init();
	WoodAround woodInside4(3, 6.99, woodBoardText, ourShader);
	woodInside4.init();
	WoodAround woodInside5(4, 6.99, woodBoardText, ourShader);
	woodInside5.init();

	Shovel shovel(4, 7, 1, windBladeText, ourShader);
	shovel.init();

	Roof roof(4, 7, woodRoofText, ourShader);
	roof.init();

	Floor floor(5, 7, oldWoodText,ledderText, ourShader);
	floor.init();


	//added

	Base base1(0.11, 7.5, brickText, oldWoodText, ourShader);
	base1.init();
	NextFloor firstFloor1(5, 0, 7.5, oldWoodText, ourShader);
	firstFloor1.init();
	NextFloor secFloor1(5, 1, 7.5, oldWoodText, ourShader);
	secFloor1.init();
	NextFloor thirFloor1(5, 2, 7.5, oldWoodText, ourShader);
	thirFloor1.init();
	NextFloor fourFloor1(5, 3, 7.5, oldWoodText, ourShader);
	fourFloor1.init();
	WoodAround woodAround1(0, 7.51, woodBoardText, ourShader);
	woodAround1.init();
	WoodAround woodAround2(1, 7.51, woodBoardText, ourShader);
	woodAround2.init();
	WoodAround woodAround3(2, 7.51, woodBoardText, ourShader);
	woodAround3.init();
	WoodAround woodAround4(3, 7.51, woodBoardText, ourShader);
	woodAround4.init();
	WoodAround woodAround5(4, 7.51, woodBoardText, ourShader);
	woodAround5.init();

	//Shovel shovel1(4, 7, 0.5 ,windBladeText, ourShader);
	//shovel1.init();

	Roof roof1(4, 7.5, woodRoofText, ourShader);
	roof1.init();

	Door door(4, 7.5, doorText, ourShader);
	door.init();

	Window window1(2, 7.51, windowText, ourShader);
	window1.init();
	Window window2(2, 6.99, windowText, ourShader);
	window2.init();
	//added/

	Gate gate(0.11, 7.25, brickText, oldWoodText, ourShader);
	gate.init();



	WalkPath patt(7, pathText, ourShader);
	patt.init();

	Quern quern(0.1, 2, stoneText, ourShader);
	quern.init();

	Quern quer(2.1, 2, stoneText, ourShader);
	quer.init();
	
	WoodQuern woodquer(2.1, 2, oldWoodText, ourShader);
	woodquer.init();

	Polygon clouds(cloudsVs, 6, cloudsText, 0.2f, ourShader);

	Polygon cloud1(cloudsVs, 6, skyText, 0.2f, ourShader);
	Polygon cloud2(cloudsVs, 6, skyText, 0.2f, ourShader);
	Polygon cloud3(cloudsVs, 6, skyText, 0.2f, ourShader);
	Polygon cloud4(cloudsVs, 6, skyText, 0.2f, ourShader);

	

	clouds.init();
	clouds.translate(glm::vec3(0, sceneHeight, 0));
	clouds.rotate(90, glm::vec3(1, 0, 0));
	clouds.scale(glm::vec3(sceneWidht, sceneWidht, 1.0));

	cloud1.init();
	cloud1.translate(glm::vec3(0, sceneHeight / 2, 0));
	cloud1.translate(glm::vec3(0, 0, sceneWidht));
	cloud1.scale(glm::vec3(sceneWidht, sceneHeight / 2, 1.0));

	cloud2.init();
	cloud2.translate(glm::vec3(0, sceneHeight / 2, 0));
	cloud2.translate(glm::vec3(0, 0, -1 * sceneWidht));
	cloud2.scale(glm::vec3(sceneWidht, sceneHeight / 2, 1.0));

	cloud3.init();
	cloud3.translate(glm::vec3(0, sceneHeight / 2, 0));
	cloud3.translate(glm::vec3(sceneWidht, 0, 0));
	cloud3.rotate(90, glm::vec3(0, 1, 0));
	cloud3.scale(glm::vec3(sceneWidht, sceneHeight / 2, 1.0));

	cloud4.init();
	cloud4.translate(glm::vec3(0, sceneHeight / 2, 0));
	cloud4.translate(glm::vec3(-1 * sceneWidht, 0, 0));
	cloud4.rotate(90, glm::vec3(0, 1, 0));
	cloud4.scale(glm::vec3(sceneWidht, sceneHeight / 2, 1.0));
	

	//program loop
	GLfloat lastFrame = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		//set Z-buffer test and blending
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//set frame time
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		GLfloat deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//check and call events
		glfwPollEvents();
		if (keys[GLFW_KEY_W])
			camera.move(FORWARD, deltaTime);
		if (keys[GLFW_KEY_S])
			camera.move(BACKWARD, deltaTime);
		if (keys[GLFW_KEY_A])
			camera.move(LEFT, deltaTime);
		if (keys[GLFW_KEY_D])
			camera.move(RIGHT, deltaTime);
		//print current camera position
		system("cls");
		std::cout << "Camera: x = " << camera.position.x << ", y = " << camera.position.y << ", z = " << camera.position.z << "\nFPS = " << 1 / deltaTime << std::endl;
		//clear background color
		glClearColor(0.25f, 0.36f, 0.5f, 0.4f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//activate camera
		camera.passToShader(ourShader);
		//activate shader
		ourShader.Use();
		//draw objects
		grass.draw();
		clouds.draw();
		cloud1.draw();
		cloud2.draw();
		cloud3.draw();
		cloud4.draw();
		base.draw();
		firstFloor.draw();
		secFloor.draw();
		thirFloor.draw();
		fourFloor.draw();
		woodAround1.draw();
		woodAround2.draw();
		woodAround3.draw();
		woodAround4.draw();
		woodAround5.draw();
		woodInside1.draw();
		woodInside2.draw();
		woodInside3.draw();
		woodInside4.draw();
		woodInside5.draw();
		roof.draw();
		//added
		base1.draw();
		firstFloor1.draw();
		secFloor1.draw();
		thirFloor1.draw();
		fourFloor1.draw();
		roof1.draw();
		gate.draw();
		//added

		door.draw();
		window1.draw();
		window2.draw();
		floor.draw();

		woodquer.draw();
		woodquer.rotate(1);
		patt.draw();
		quern.draw();
		quer.draw();
		quer.rotate(1);
		shovel.rotate(1);
		shovel.draw();
		
		//swap buffers

		glfwSwapBuffers(window);
	}
	//terminate GLFW
	glfwTerminate();
	return 0;
}