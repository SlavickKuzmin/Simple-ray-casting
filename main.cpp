#include <stdio.h>
#include <stdlib.h>
// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <gl/glew.h>
#include <GL/GL.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Color.h"
#include "TimeMeasure.h"
#include "RayCaster.h"
#include "LevelMap.h"

const int screen_width = 512;
const int screen_height = 512;

void initGLEW();

int main(int argc, char **argv)
{
	initGLEW();

	// Open a window and create its OpenGL context
	GLFWwindow* window;
	window = glfwCreateWindow(screen_width, screen_height, "Simple ray casting", nullptr, nullptr);
	if (window == nullptr)
	{
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	LevelMap *map = new LevelMap(16, 16);
	const char level_map[] = 
		"0000222222220000"\
		"1              0"\
		"1      11111   0"\
		"1     0        0"\
		"0     0  1110000"\
		"0     3        0"\
		"0   10000      0"\
		"0   0   11100  0"\
		"0   0   0      0"\
		"0   0   1  00000"\
		"0       1      0"\
		"2       1      0"\
		"0       0      0"\
		"0 0000000      0"\
		"0              0"\
		"0002222222200000";
	map->SetLevelMap(level_map);

	Player *player = new Player();
	player->SetPosition(50, 50);

	RayCaster caster(screen_width, screen_height);
	caster.SetLevelMap(map);
	caster.SetPlayer(player);

	caster.Draw();

	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClearColor(0, 0,0,0);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawPixels(screen_width, screen_height, GL_RGBA, GL_UNSIGNED_BYTE, caster.GetScreen().GetPixels());
		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	delete map;
	delete player;

	return 0;
}

/*!
 Initialize a GLSW library.
*/
void initGLEW()
{
	glewExperimental = GL_TRUE;
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		abort();
	}
}