#include <stdio.h>
#include <stdlib.h>
// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <gl/glew.h>
#include <GL/GL.h>
#include <GLFW/glfw3.h>

#include "Color.h"
#include "TimeMeasure.h"
#include "RayCaster.h"
#include "LevelMap.h"
#include "Viewport.h"
#include "TextureAtlas.h"

const int screen_width = 1024;
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

	TextureAtlas texAtl("E:\\Voxels\\RayCasting\\git\\Simple-ray-casting\\images\\texture.png");

	LevelMap *map = new LevelMap(16, 16, &texAtl);
	const char level_map[] = 
		"0000222222220000"\
		"1              0"\
		"1     011111   0"\
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
	player->SetPosition(3.456, 2.345);

	Screen* scr = new Screen(screen_width, screen_height);

	Viewport* left_view = new Viewport(scr, 0, 0, 512, 512);
	Viewport* right_view = new Viewport(scr, 512, 0, 1024, 512);

	RayCaster caster(screen_width, screen_height, left_view, right_view);
	caster.SetLevelMap(map);
	caster.SetPlayer(player);

	Time::TimeMeasure diff;

	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	float moveSpeed = 0.05f;
	float rotationSpeed = 0.05f;

	do {
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClearColor(0, 0,0,0);
		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			caster.GetPlayer()->SetViewDir(caster.GetPlayer()->GetViewDir() + rotationSpeed);
		}
		else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			caster.GetPlayer()->SetViewDir(caster.GetPlayer()->GetViewDir() - rotationSpeed);
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			caster.GetPlayer()->SetPositionY(caster.GetPlayer()->GetPositionY() + moveSpeed);
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			caster.GetPlayer()->SetPositionY(caster.GetPlayer()->GetPositionY() - moveSpeed);
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			caster.GetPlayer()->SetPositionX(caster.GetPlayer()->GetPositionX() - moveSpeed);
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			caster.GetPlayer()->SetPositionX(caster.GetPlayer()->GetPositionX() + moveSpeed);
		}
		//diff.StartMeasure();

		scr->ClearScreen();
		caster.Draw();

		//diff.StopMeasure();

		glDrawPixels(screen_width, screen_height, GL_RGBA, GL_UNSIGNED_BYTE, scr->GetPixels());
		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	delete map;
	delete player;
	delete scr;
	delete left_view;
	delete right_view;

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