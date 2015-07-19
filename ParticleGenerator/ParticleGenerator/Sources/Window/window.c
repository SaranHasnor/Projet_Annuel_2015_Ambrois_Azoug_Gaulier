#include <Utils/public.h>
#include "window.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "scene.h"
#include "input.h"
#include <Utils/utils.h>
#include <Utils/vec3D.h>
#include <Utils/mat4.h>

/*
window.c

- Window creation and management
- Glut initialization
*/

extern void createInterface(int window);	// from interface_init.c

int window;
float projMatrix[16];

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glPointSize(1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	glDepthMask(GL_FALSE);
}

void setPerspective(float fov, float width, float height, float near, float far)
{
	float aspect = width / height;

	mat_perspective(projMatrix, fov, width, height, near, far);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(projMatrix);
}

void reshape(int w, int h)
{
	short fixW=0, fixH=0;

	if (w != DEFAULT_WIDTH || h != DEFAULT_HEIGHT)
	{ // For now, no resizing because it breaks everything
		glutReshapeWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT);
		return;
	}

	if (h != DEFAULT_HEIGHT)
	{ // Can't change that, or it breaks the interface
		fixH = 1;
	}

	if (w < INTERFACE_WIDTH)
	{ // Too small
		fixW = 1;
	}

	if (fixH || fixW)
	{
		glutReshapeWindow((fixW?INTERFACE_WIDTH:w), (fixH?DEFAULT_HEIGHT:h));
		return;
	}

	glViewport(0, 0,(GLsizei) w - INTERFACE_WIDTH, (GLsizei) h);
	setPerspective(60.0f, (float)(w - INTERFACE_WIDTH), (float)h, 1.0f, 200.0f);
}

void display(void)
{
	int i;
	float viewMatrix[16];
	float viewProjMatrix[16];
	float fwd[3], right[3], up[3];

	glDepthMask(GL_TRUE);

	// Frame initialization
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	// Projection setup
	AngleVectors(camAngle, fwd, right, up);

	for (i = 0; i < 3; i++)
	{
		viewMatrix[4*i+0] = right[i];
		viewMatrix[4*i+1] = up[i];
		viewMatrix[4*i+2] = -fwd[i];
		viewMatrix[4*i+3] = 0.0f;
	}

	viewMatrix[4*i+0] = -vectorDot(right, camPos);
	viewMatrix[4*i+1] = -vectorDot(up, camPos);
	viewMatrix[4*i+2] = vectorDot(fwd, camPos);
	viewMatrix[4*i+3] = 1.0f;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(viewMatrix);

	glDepthMask(GL_FALSE);

	// Draw the scene
	mat_multiply(viewProjMatrix, projMatrix, viewMatrix);
	drawScene(viewProjMatrix);

	// Frame saving and rendering
	glutSwapBuffers();
	glFlush();
}

void updateCamera(float deltaTime)
{
	float forward[3], right[3];
	float movement[3];
	AngleVectors(camAngle, forward, right, NULL);

	// Update the camera position (cheap method because math is hard)
	vectorScale(movement, moveDir[2], axis[2]);
	vectorMA(movement, movement, moveDir[1], forward);
	vectorMA(movement, movement, moveDir[0], right);
	
#if USE_NEW_CAMERA_MOVEMENT
	vectorScale(movement, deltaTime, movement);
	vectorAdd(camPos, camPos, movement);
	vectorScale(moveDir, 0.95f, moveDir); // Science
#else
	vectorAdd(camPos, camPos, movement);
	vectorSet(moveDir, 0.0f, 0.0f, 0.0f);
#endif
}

void update(int prevTime)
{
	const int curTime = glutGet(GLUT_ELAPSED_TIME);
	const int deltaTime = curTime - prevTime;
	const float deltaTimeSeconds = deltaTime / 1000.0f;

	//printf("FPS: %f\n", 1.0f / deltaTimeSeconds);
	
	glutSetWindow(window);
	updateCamera(deltaTimeSeconds);
	updateScene(deltaTimeSeconds);

	glutTimerFunc(10, update, curTime);
}

int main(int argc, char **argv)
{
	const int screenX = glutGet(GLUT_SCREEN_WIDTH);
	const int screenY = glutGet(GLUT_SCREEN_HEIGHT);

	// Initializing GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	glutInitWindowPosition(screenX/2-DEFAULT_WIDTH/2, screenY/2-DEFAULT_HEIGHT/2);
	window = glutCreateWindow("Particles");

	// Initializing GLEW
	glewInit();

	initRendering();

    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	// Initializing the user input events
	initInput();

	// Initializing the interface
	createInterface(window);
	glutSetWindow(window);

	// Init the scene and start updating it
	initScene();
	update(0);
	
	// Starting the main loop
    glutMainLoop();

    return 0;
}