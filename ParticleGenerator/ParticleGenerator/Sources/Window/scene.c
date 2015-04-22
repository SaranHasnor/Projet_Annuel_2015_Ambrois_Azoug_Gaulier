#include <Utils/public.h>
#include <GL/glut.h>
#include "scene.h"
#include <Utils/render_utils.h>
#include "input.h"
#include <Utils/utils.h>

#include <Engine/engine_wrapper.h>

/*
scene.c

- Scene and object rendering
*/

scene_t scene;

float camPos[3] = {DEFAULT_CAMERA_POSITION};
float camAngle[3] = {DEFAULT_CAMERA_ANGLE};

// Scene data


void initScene()
{
	initEngine();
}

void updateScene(float deltaTime)
{
	updateEngine(deltaTime);
	
	glutPostRedisplay();
}

void drawScene()
{
	renderEngine();
}