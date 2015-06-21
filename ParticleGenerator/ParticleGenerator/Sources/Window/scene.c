#include <Utils/public.h>
#include <GL/glut.h>
#include "scene.h"
#include <Utils/render_utils.h>
#include "input.h"
#include <Utils/utils.h>
#include <Utils/vec3D.h>
#include <Utils/mat4.h>

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
	scene.running = 1;
}

void updateScene(float deltaTime)
{
	if (scene.running)
	{
		updateEngine(deltaTime);
	}
	
	glutPostRedisplay();
}

extern float projMatrix[16];

void drawScene()
{
	int i;
	float viewMatrix[16];
	float viewProjMatrix[16];
	float fwd[3], right[3], up[3];

	AngleVectors(camAngle, fwd, right, up);

	for (i = 0; i < 3; i++)
	{
		viewMatrix[4*i+0] = right[i];
		viewMatrix[4*i+1] = up[i];
		viewMatrix[4*i+2] = fwd[i];
		viewMatrix[4*i+3] = 0.0f;
	}

	viewMatrix[4*i+0] = -vectorDot(right, camPos);
	viewMatrix[4*i+1] = -vectorDot(up, camPos);
	viewMatrix[4*i+2] = vectorDot(fwd, camPos);
	viewMatrix[4*i+3] = 1.0f;

	mat_multiply(viewProjMatrix, projMatrix, viewMatrix);

	renderEngine(viewProjMatrix);
}