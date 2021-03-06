#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <omp.h>

#include "shader.h"
#include "arrayBuffer.h"
#include "vertexArray.h"
#include "gameloop.h"
#include "tools/textureloader.h"
#include "tools/random.h"
#include "tools/clock.h"

#define WIDTH 1920
#define HEIGHT 1080
#define ASPECT 2.0f
#define CPU_RENDER true
#define FULLSCREEN

double zoom = 1;
glm::dvec2 offset = glm::dvec2(0.0);
short iterations = 148;

double speed = 0.02;

GLFWwindow *window;
VertexArray *vaoMandel;
VertexArray* vaoJulia;
Shader *shader;
logic::GameLoop *loop;
int upcount = 0;

GLubyte texels[WIDTH * HEIGHT * 4];
GLuint texture;

bool keys[2048];
void key(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) keys[key] = true;
	else if (action == GLFW_RELEASE) keys[key] = false;
	loop->forceUpdate();
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);

	shader->setUniform1i("rendering_mandelbrot", 1);
	vaoMandel->bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	shader->setUniform1i("rendering_mandelbrot", 0);
	vaoJulia->bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void update() {
	if (glfwWindowShouldClose(window)) loop->stop();

	if (keys[GLFW_KEY_LEFT_CONTROL]) speed = 0.002;
	if (keys[GLFW_KEY_S]) offset.y -= speed * zoom;
	if (keys[GLFW_KEY_W]) offset.y += speed * zoom;
	if (keys[GLFW_KEY_A]) offset.x -= speed * zoom;
	if (keys[GLFW_KEY_D]) offset.x += speed * zoom;
	speed = 0.02;
	
	if (keys[GLFW_KEY_Q]) zoom *= 1.01;
	if (keys[GLFW_KEY_E]) zoom *= 0.99;
	
	int itspeed = 1;
	if (keys[GLFW_KEY_LEFT_SHIFT]) itspeed = 10;
	if (keys[GLFW_KEY_R]) { iterations += itspeed; if (iterations < 0) iterations = 0; std::cout << "Iterations: " << iterations << std::endl; }
	if (keys[GLFW_KEY_F]) { iterations -= itspeed; if (iterations < 0) iterations = 0; std::cout << "Iterations: " << iterations << std::endl; }
	if (keys[GLFW_KEY_ESCAPE]) { glfwDestroyWindow(window); glfwTerminate(); exit(0); }
	if (keys[GLFW_KEY_TAB]) { iterations = 127; offset = glm::dvec2(0.0); zoom = 1; }

	upcount++;
	if (upcount > 100) {
		std::cout << "FPS: " << loop->getFPS() << "\nUPS: " << loop->getUPS() << std::endl;
		std::cout << "Zoom: " << zoom << std::endl;
		std::cout << "Offset real: " << offset.x << std::endl;
		std::cout << "Offset imaginary: " << offset.y << std::endl;
		std::cout << "Iterations: " << iterations << "\n";

		upcount = 0;
	}
	
	shader->setUniform1d("unif_zoom", zoom);
	shader->setUniform2d("unif_offset", offset);
	shader->setUniform1i("unif_iterations", iterations);
}

int main()
{
	//#pragma omp parallel for
	for (int i = 0; i < 2048; i++) keys[i] = false;

	if (!glfwInit()) { return -1; }
	window = glfwCreateWindow(
		WIDTH, 
		HEIGHT, 
		"Mandelbrot set", 
#ifdef FULLSCREEN
		glfwGetPrimaryMonitor(), 
#else
		NULL,
#endif
		NULL
	);
	if (!window) { glfwTerminate(); return -2; }
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { glfwTerminate(); return -3; }
	glfwSetKeyCallback(window, key);
	glfwSwapInterval(1);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	shader = new Shader("shaders/basic.vert.glsl", "shaders/basic.frag.glsl");
	glm::mat4 orthographic = glm::ortho(-ASPECT, ASPECT, -1.0f, 1.0f);
	shader->enable(); shader->setUniformMat4("pr_matrix", orthographic);
	tools::TextureLoader::loadTexture("colorline.jpeg", GL_RGBA);



	GLfloat vertices[] = {
		-ASPECT, -1.0,
		-ASPECT, 1.0,
		0.0, 1.0,
		-ASPECT, -1.0,
		0.0, 1.0,
		0.0, -1.0
	};

	vaoJulia = new VertexArray();
	ArrayBuffer *vbo = new ArrayBuffer(vertices, 12, 2);
	vaoJulia->addBuffer(vbo, 0);

	GLfloat vertices2[] = {
		0.0, -1.0,
		0.0, 1.0,
		ASPECT, 1.0,
		0.0, -1.0,
		ASPECT, 1.0,
		ASPECT, -1.0
	};

	vaoMandel = new VertexArray();
	vbo = new ArrayBuffer(vertices2, 12, 2);
	vaoMandel->addBuffer(vbo, 0);

	loop = new logic::GameLoop(render, update, 10000);
	loop->start();
	return 0;
}