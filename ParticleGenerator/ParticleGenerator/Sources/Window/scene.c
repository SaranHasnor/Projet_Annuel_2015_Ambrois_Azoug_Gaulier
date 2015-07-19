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

void drawScene(float viewProjMatrix[16])
{
	renderEngine(viewProjMatrix);

	if (scene.drawEmitters)
	{
		int emitterCount = getEmitterCount();
		int i;

		for (i = 0; i < emitterCount; i++)
		{
			float x, y, z, pitch, yaw, roll;

			x = *(float*)emitterAttribute(i, EMIT_ATTR_POS_X);
			y = *(float*)emitterAttribute(i, EMIT_ATTR_POS_Y);
			z = *(float*)emitterAttribute(i, EMIT_ATTR_POS_Z);
			pitch = *(float*)emitterAttribute(i, EMIT_ATTR_PITCH);
			yaw = *(float*)emitterAttribute(i, EMIT_ATTR_YAW);
			roll = *(float*)emitterAttribute(i, EMIT_ATTR_ROLL);

			glPushMatrix();
			glTranslatef(x, y, z);
			glRotatef(pitch, 1.0f, 0.0f, 0.0f);
			glRotatef(roll, 0.0f, 1.0f, 0.0f);
			glRotatef(yaw, 0.0f, 0.0f, 1.0f);
			drawAxis();
			glPopMatrix();
		}
	}
}