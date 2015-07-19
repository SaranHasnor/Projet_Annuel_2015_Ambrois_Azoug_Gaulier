#ifndef SCENE_H_DEFINED
#define SCENE_H_DEFINED

#define DEFAULT_CAMERA_POSITION 0.0f,-10.0f,0.0f
#define DEFAULT_CAMERA_ANGLE 0.0f,90.0f,0.0f

#define USE_NEW_CAMERA_MOVEMENT 0

typedef struct scene_s {
	short running;
	short drawEmitters;
} scene_t;

extern scene_t scene;

extern float camPos[3];
extern float camAngle[3];

void initScene();
void updateScene(float deltaTime);
void drawScene(float viewProjMatrix[16]);


#endif