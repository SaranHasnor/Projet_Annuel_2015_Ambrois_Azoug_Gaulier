#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	PART_ATTR_NAME,
	PART_ATTR_POS_X,
	PART_ATTR_POS_Y,
	PART_ATTR_POS_Z,
	PART_ATTR_VEL_X,
	PART_ATTR_VEL_Y,
	PART_ATTR_VEL_Z,
	PART_ATTR_ACCEL_X,
	PART_ATTR_ACCEL_Y,
	PART_ATTR_ACCEL_Z,
	PART_ATTR_LIFETIME,
	PART_ATTR_START_RED,
	PART_ATTR_START_GREEN,
	PART_ATTR_START_BLUE,
	PART_ATTR_START_ALPHA,
	PART_ATTR_START_SCALE
} particle_attr_t;

void initEngine();
void updateEngine(float deltaTime);
void renderEngine();
void *particleAttribute(char *particleName, particle_attr_t attribute);

#ifdef __cplusplus
}
#endif