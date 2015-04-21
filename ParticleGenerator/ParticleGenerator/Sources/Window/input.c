#include "public.h"
#include <GL\glut.h>
#include "scene.h"
#include "input.h"
#include <Utils/utils.h>

/*
input.c

- Input events
- Hotkey management
*/

#define MOUSELEFT	(1 << GLUT_LEFT_BUTTON)
#define MOUSEMIDDLE	(1 << GLUT_MIDDLE_BUTTON)
#define MOUSERIGHT	(1 << GLUT_RIGHT_BUTTON)

float moveDir[3];
uint mouseButtons;
int mousePos[2];

#if USE_NEW_INPUT_SYSTEM

typedef struct key_s {
	unsigned char	key;
	short			isHeld;
	float			timeHeld;
	
	// Events go here
	void			(*onKeyDown)(void);
	void			(*onKeyUp)(void);
	void			(*onKeyHeld)(void);
} key_t;

key_t *keys;

#endif

void motion(int x, int y)
{
	if (!mouseButtons)
	{ // This shouldn't happen
		return;
	}

	if (mouseButtons & MOUSELEFT)
	{
		camAngle[0] += y-mousePos[1];
		camAngle[1] -= x-mousePos[0];

		if (camAngle[0] < -85)
			camAngle[0] = -85;
		if (camAngle[0] > 85)
			camAngle[0] = 85;

		if (camAngle[1] < -180)
			camAngle[1] += 360;
		if (camAngle[1] > 180)
			camAngle[1] -= 360;
	}
	else if (mouseButtons & MOUSERIGHT)
	{
		//int i;

		//camPosCalc[0] += (float)(x-prevX)/50.0;
		//camPosCalc[2] -= (float)(y-prevY)/50.0;

		/*for (i=0; i<3; i++)
		{
			if (camPosCalc[i] < -10)
				camPosCalc[i] = -10;
			if (camPosCalc[i] > 10)
				camPosCalc[i] = 10;
		}*/
	}

	mousePos[0] = x;
	mousePos[1] = y;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		mouseButtons |= (1 << button);
	}
	else
	{
		mouseButtons &= ~(1 << button);
	}

	mousePos[0] = x;
	mousePos[1] = y;
}

void keyboard(unsigned char key, int x, int y)
{
#if USE_NEW_INPUT_SYSTEM

	if (!keys[key].isHeld)
	{
		keys[key].isHeld = 1;
		keys[key].timeHeld = 0;
		if (keys[key].onKeyDown) keys[key].onKeyDown();
	}

#else

	switch (key) {
		case 'C':
		case 'c':
			vectorSet(camAngle, DEFAULT_CAMERA_ANGLE);
			vectorSet(camPos, DEFAULT_CAMERA_POSITION);
			break;
		case 'Z':
		case 'z':
			moveDir[0] = 1.0f;
			break;
		case 'Q':
		case 'q':
			moveDir[1] = -1.0f;
			break;
		case 'S':
		case 's':
			moveDir[0] = -1.0f;
			break;
		case 'D':
		case 'd':
			moveDir[1] = 1.0f;
			break;
		case ' ':
			moveDir[2] = 1.0f;
			break;
		case 'x':
		case 'X':
			moveDir[2] = -1.0f;
			break;
		case 27: // Escape
			quit();
		default:
			break;
	}

#endif

	glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
#if USE_NEW_INPUT_SYSTEM

	keys[key].isHeld = 0;
	if (keys[key].onKeyUp) keys[key].onKeyUp();

	glutPostRedisplay();

#endif
}

void initInput()
{
#if USE_NEW_INPUT_SYSTEM
	unsigned char i;
	keys = (key_t*)mem_alloc(sizeof(key_t) * 255);

	for (i = 0; i < length; i++)
	{
		keys[i].key = i;
		keys[i].isHeld = 0;
		keys[i].timeHeld = 0;
		keys[i].onKeyDown = NULL;
		keys[i].onKeyUp = NULL;
		keys[i].onKeyHeld = NULL;
	}
#endif

	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
}