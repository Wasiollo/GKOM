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
#include "Generate.h"

//window size
GLuint screenWidth = 1366, screenHeight = 768;
// Camera
Camera camera(glm::vec3(0.0f, 10.0f, 60.0f), screenWidth, screenHeight);
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
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

GLuint LoadMipmapTexture(GLuint texId, const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

ostream& operator<<(ostream& os, const glm::mat4& mx)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
			cout << mx[row][col] << ' ';
		cout << endl;
	}
	return os;
}

void convVtT( std::vector<GLfloat> vector, GLfloat* tab )
{
	for (int i = 0; i < vector.size(); ++i)
	{
		tab[i] = vector.at(i);
	}

}
void convItT(std::vector<GLuint> vector, GLuint* tab) 
{
	for (int i = 0; i < vector.size(); ++i)
	{
		tab[i] = vector.at(i);
	}
}
int main()
{
	{
		glm::mat4 trans;
		cout << trans << endl;
		trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		cout << trans << endl;
	}
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 05", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);
		glEnable(GL_DEPTH_TEST);

		// Let's check what are maximum parameters counts
		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;

		// Build, compile and link shader program
		ShaderProgram theProgram("gl_05.vert", "gl_05.frag");

		Generate generator = Generate();
		
		float colorTemp[] = { 1.0, 0.0, 0.0, 40.0, 40.0 };
		float textureTemp[] = { 0.0, 0.0 };
		vector<GLfloat> vertices = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
		vector<GLfloat> vTemp = generator.generateNOctangulars(9, 0.5, 0.4, colorTemp);
		vertices.insert(vertices.end(), vTemp.begin(), vTemp.end());
		

		int verticSize = vertices.size();
		
		GLfloat *tab = new GLfloat[verticSize]{};
		convVtT(vertices, tab);
		
		int sizeOfVerticles = sizeof(tab)*vertices.size();
		int bitsOfOneVertice = 8;
		std::cout << (vertices.size() / bitsOfOneVertice )<< std::endl;

		std::vector<GLuint> indice = {
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 5,
			0, 5, 6,
			0, 6, 7,
			0, 7, 8,
			0, 8, 1,
		};
		std::vector<GLuint> indTemp;
		indTemp = generator.generateConnections(1, 8);
		indice.insert(indice.end(), indTemp.begin(), indTemp.end());
		indTemp = generator.generateConnections(9, 8);
		indice.insert(indice.end(), indTemp.begin(), indTemp.end());
		indTemp = generator.generateConnections(17, 8);
		indice.insert(indice.end(), indTemp.begin(), indTemp.end());
		indTemp = generator.generateConnections(25, 8);
		indice.insert(indice.end(), indTemp.begin(), indTemp.end());
		indTemp = generator.generateConnections(33, 8);
		indice.insert(indice.end(), indTemp.begin(), indTemp.end());
		indTemp = generator.generateConnections(41, 8);
		indice.insert(indice.end(), indTemp.begin(), indTemp.end());
		indTemp = generator.generateConnections(49, 8);
		indice.insert(indice.end(), indTemp.begin(), indTemp.end());

		GLuint* indices = new GLuint[indice.size()];

		convItT(indice, indices);
		/*GLuint indices[] = {
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 5,
			0, 5, 6,
			0, 6, 7,
			0, 7, 8,
			0, 8, 1,
			1, 2, 9,
			2, 9, 10,
			2, 3, 10,
			3, 10, 11,
			3, 4, 11,
			4, 11, 12,
			4, 5, 12,
			5, 12, 13,
			5, 6, 13,
			6, 13, 14,
			6, 7, 14,
			7, 14, 15,
			7, 8, 15,
			8, 15, 16,
			8, 1, 16,
			1, 16, 9,
			
		};*/

		GLuint VBO, EBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeOfVerticles*4, tab, GL_STATIC_DRAW); // mam 17 wierzcho³ków -> 34 przypadek nie s¹dzê 

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice.size()*100, indices, GL_STATIC_DRAW); // important chancged to indice.size*8

		// vertex geometry data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// vertex color data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// vertex texture coordinates
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

							  // Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// prepare textures
		GLuint texture0 = LoadMipmapTexture(GL_TEXTURE0, "wood.png");
		GLuint texture1 = LoadMipmapTexture(GL_TEXTURE1, "wood.png");

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Bind Textures using texture units
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture0);
			glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture0"), 0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture1);
			glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture1"), 1);

			
			

			glm::mat4 trans;
			static GLfloat rot_angle = 0.0f;
			trans = glm::rotate(trans, -glm::radians(rot_angle), glm::vec3(0.0f, 1.0f, 1.0f));
			rot_angle += 0.01f;
			if (rot_angle >= 360.0f)
				rot_angle -= 360.0f;

			glm::mat4 camRot;
			camRot = glm::rotate(camRot, glm::radians(rot_angle), glm::vec3(0.0f, 1.0f, .0f));
			glm::vec3 cameraPos = glm::vec3(camRot * glm::vec4(0.0f, 0.0f, -3.0f, 1.0f));


			glm::mat4 view;
			glm::mat4 projection;
			//view = glm::translate(view, glm::vec3(1.0f, 1.0f, -4.0f));
			view = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.f); // wczeœniej pierwszy parametr = 45.0f

			GLint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
			GLint projectionLoc = glGetUniformLocation(theProgram.get_programID(), "projection");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

			GLuint transformLoc = glGetUniformLocation(theProgram.get_programID(), "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

			// Draw our first triangle
			theProgram.Use();

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indice.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}
