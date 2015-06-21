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
	gluPerspective(fov, aspect, near, far);
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
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setPerspective(60.0f, (float)w, (float)h, 1.0f, 200.0f);
}

void display(void)
{
	float forward[3], right[3], camLookPos[3];

	// Frame initialization
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Calculate the camera's facing direction
	AngleVectors(camAngle, forward, right, NULL);
	vectorScale(forward, 10, forward);
	vectorAdd(camLookPos, forward, camPos);

	// Set the camera (I want to put this out of the loop and move/rotate the world instead)
	gluLookAt((double)camPos[0], (double)camPos[1], (double)camPos[2],
		(double)camLookPos[0], (double)camLookPos[1], (double)camLookPos[2],
		(double)axis[2][0], (double)axis[2][1], (double)axis[2][2]);

	// Draw the scene
	drawScene();

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
	vectorMA(movement, movement, moveDir[0], forward);
	vectorMA(movement, movement, moveDir[1], right);
	
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