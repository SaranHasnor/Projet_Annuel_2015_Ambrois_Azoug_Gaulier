#ifdef __cplusplus
extern "C" {
#endif

void initEngine();
void updateEngine(float deltaTime);
void renderEngine(float viewMatrix[16]);

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

typedef enum {
	EMIT_ATTR_PARTICLE_NAME,
	EMIT_ATTR_POS_X,
	EMIT_ATTR_POS_Y,
	EMIT_ATTR_POS_Z,
	EMIT_ATTR_VEL_X,
	EMIT_ATTR_VEL_Y,
	EMIT_ATTR_VEL_Z,
	EMIT_ATTR_PITCH,
	EMIT_ATTR_YAW,
	EMIT_ATTR_ROLL,
	EMIT_ATTR_SPAWN_INTERVAL,
	EMIT_ATTR_RANDOM_DIR
} emitter_attr_t;

void *particleAttribute(char *particleName, particle_attr_t attribute);
void *emitterAttribute(int emitterID, emitter_attr_t attribute);

int getActiveParticleCount();
int getParticleModelCount();
int getEmitterCount();
int getShaderCount();

#ifdef __cplusplus
}
#endif