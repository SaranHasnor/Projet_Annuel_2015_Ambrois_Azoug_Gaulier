#include <Utils/public.h>
#include <Utils/mem_libs.h>
#include "interface.h"
#include "scene.h"
#include <Utils/utils.h>
#include "window.h"
#include <Engine/engine_wrapper.h>
#include <Utils/cstring.h>

/*
interface_init.c

- Interface creation
*/

// Interface variables

int emitterPickerMenu;
int emitterPickerList;
int emitterPickerPath;
char *emitterSavePath;

int particlePickerMenu;
int particlePickerList;
int particlePickerPath;
char *particleSavePath;

int shaderPickerMenu, shaderPickerList;

int emitterEditorMenu;
int emitterEditor_posX, emitterEditor_posY, emitterEditor_posZ;
int emitterEditor_randomAngle;
int emitterEditor_pitch, emitterEditor_yaw, emitterEditor_roll;
int emitterEditor_velX, emitterEditor_velY, emitterEditor_velZ;
int emitterEditor_particleName;
int emitterEditor_spawnInterval;

int particleEditorMenu;
int particleEditor_particleName;
int particleEditor_red, particleEditor_green, particleEditor_blue, particleEditor_alpha, particleEditor_scale;
int particleEditor_lifetime;
int particleEditor_red2, particleEditor_green2, particleEditor_blue2, particleEditor_alpha2, particleEditor_scale2;
int particleEditor_shaderName;
int particleEditor_texturePath;

int shaderEditorMenu;
int shaderEditor_shaderName;
int shaderEditor_shaderPath;

// End of interface variables

// Interface functions

// Data

void updateEmitterPicker()
{
	int i;
	int count = getEmitterCount();

	saveListSelectedIndex(emitterPickerMenu, emitterPickerList);

	clearList(emitterPickerMenu, emitterPickerList);

	for (i = 0; i < count; i++)
	{
		addListEntry(emitterPickerMenu, emitterPickerList, "Emitter");
	}

	loadListSelectedIndex(emitterPickerMenu, emitterPickerList);
}

void updateEmitterEditor()
{
	uint emitterID = getListSelectedIndex(emitterPickerMenu, emitterPickerList);

	setTextFieldValue(emitterEditorMenu, emitterEditor_posX, -1000.0f, 1000.0f, emitterAttribute(emitterID, EMIT_ATTR_POS_X), 1);
	setTextFieldValue(emitterEditorMenu, emitterEditor_posY, -1000.0f, 1000.0f, emitterAttribute(emitterID, EMIT_ATTR_POS_Y), 1);
	setTextFieldValue(emitterEditorMenu, emitterEditor_posZ, -1000.0f, 1000.0f, emitterAttribute(emitterID, EMIT_ATTR_POS_Z), 1);

	setCheckBoxValue(emitterEditorMenu, emitterEditor_randomAngle, (short*)emitterAttribute(emitterID, EMIT_ATTR_RANDOM_DIR));

	setTextFieldValue(emitterEditorMenu, emitterEditor_pitch, -360.0f, 360.0f, emitterAttribute(emitterID, EMIT_ATTR_PITCH), 1);
	setTextFieldValue(emitterEditorMenu, emitterEditor_yaw, -360.0f, 360.0f, emitterAttribute(emitterID, EMIT_ATTR_YAW), 1);
	setTextFieldValue(emitterEditorMenu, emitterEditor_roll, -360.0f, 360.0f, emitterAttribute(emitterID, EMIT_ATTR_ROLL), 1);

	setTextFieldValue(emitterEditorMenu, emitterEditor_velX, -1000.0f, 1000.0f, emitterAttribute(emitterID, EMIT_ATTR_VEL_X), 1);
	setTextFieldValue(emitterEditorMenu, emitterEditor_velY, -1000.0f, 1000.0f, emitterAttribute(emitterID, EMIT_ATTR_VEL_Y), 1);
	setTextFieldValue(emitterEditorMenu, emitterEditor_velZ, -1000.0f, 1000.0f, emitterAttribute(emitterID, EMIT_ATTR_VEL_Z), 1);

	setTextFieldCPPString(emitterEditorMenu, emitterEditor_particleName, 0.0f, 0.0f, emitterAttribute(emitterID, EMIT_ATTR_PARTICLE_NAME), 0);

	setTextFieldValue(emitterEditorMenu, emitterEditor_spawnInterval, 0.0f, 60000, emitterAttribute(emitterID, EMIT_ATTR_SPAWN_INTERVAL), 1);
}

void updateParticlePicker()
{
	int i;
	int count = getParticleModelCount();

	saveListSelectedIndex(particlePickerMenu, particlePickerList);

	clearList(particlePickerMenu, particlePickerList);

	for (i = 0; i < count; i++)
	{
		addListEntry(particlePickerMenu, particlePickerList, stringToCharArray(particleAttribute(i, PART_ATTR_NAME)));
	}

	loadListSelectedIndex(particlePickerMenu, particlePickerList);
}

void updateParticleEditor()
{
	uint particleID = getListSelectedIndex(particlePickerMenu, particlePickerList);

	setTextFieldCPPString(particleEditorMenu, particleEditor_particleName, 0.0f, 0.0f, particleAttribute(particleID, PART_ATTR_NAME), 1);

	setTextFieldValue(particleEditorMenu, particleEditor_red, 0.0f, 1.0f, particleAttribute(particleID, PART_ATTR_START_RED), 1);
	setTextFieldValue(particleEditorMenu, particleEditor_green, 0.0f, 1.0f, particleAttribute(particleID, PART_ATTR_START_GREEN), 1);
	setTextFieldValue(particleEditorMenu, particleEditor_blue, 0.0f, 1.0f, particleAttribute(particleID, PART_ATTR_START_BLUE), 1);
	setTextFieldValue(particleEditorMenu, particleEditor_alpha, 0.0f, 1.0f, particleAttribute(particleID, PART_ATTR_START_ALPHA), 1);
	setTextFieldValue(particleEditorMenu, particleEditor_scale, 0.0f, 100.0f, particleAttribute(particleID, PART_ATTR_START_SCALE), 1);

	setTextFieldValue(particleEditorMenu, particleEditor_lifetime, 0.0f, 60000.0f, particleAttribute(particleID, PART_ATTR_LIFETIME), 1);

	if (particleHasTransition(particleID))
	{
		setTextFieldValue(particleEditorMenu, particleEditor_red2, 0.0f, 1.0f, particleAttribute(particleID, PART_ATTR_END_RED), 1);
		setTextFieldValue(particleEditorMenu, particleEditor_green2, 0.0f, 1.0f, particleAttribute(particleID, PART_ATTR_END_GREEN), 1);
		setTextFieldValue(particleEditorMenu, particleEditor_blue2, 0.0f, 1.0f, particleAttribute(particleID, PART_ATTR_END_BLUE), 1);
		setTextFieldValue(particleEditorMenu, particleEditor_alpha2, 0.0f, 1.0f, particleAttribute(particleID, PART_ATTR_END_ALPHA), 1);
		setTextFieldValue(particleEditorMenu, particleEditor_scale2, 0.0f, 100.0f, particleAttribute(particleID, PART_ATTR_END_SCALE), 1);
	}
	else
	{
		setTextFieldValue(particleEditorMenu, particleEditor_red2, 0.0f, 1.0f, NULL, 0);
		setTextFieldValue(particleEditorMenu, particleEditor_green2, 0.0f, 1.0f, NULL, 0);
		setTextFieldValue(particleEditorMenu, particleEditor_blue2, 0.0f, 1.0f, NULL, 0);
		setTextFieldValue(particleEditorMenu, particleEditor_alpha2, 0.0f, 1.0f, NULL, 0);
		setTextFieldValue(particleEditorMenu, particleEditor_scale2, 0.0f, 100.0f, NULL, 0);
	}

	setTextFieldCPPString(particleEditorMenu, particleEditor_shaderName, 0.0f, 0.0f, particleAttribute(particleID, PART_ATTR_SHADER), 0);
	setTextFieldCPPString(particleEditorMenu, particleEditor_texturePath, 0.0f, 0.0f, particleAttribute(particleID, PART_ATTR_TEXTURE), 1);
}

void particleTransitionButton(void)
{
	uint particleID = getListSelectedIndex(particlePickerMenu, particlePickerList);

	toggleParticleTransition(particleID);
	updateParticleEditor();
}

void updateShaderPicker()
{
	int i;
	int count = getShaderCount();

	saveListSelectedIndex(shaderPickerMenu, shaderPickerList);

	clearList(shaderPickerMenu, shaderPickerList);

	for (i = 0; i < count; i++)
	{
		addListEntry(shaderPickerMenu, shaderPickerList, stringToCharArray(shaderName(i)));
	}

	loadListSelectedIndex(shaderPickerMenu, shaderPickerList);
}

void updateShaderEditor()
{
	uint shaderID = getListSelectedIndex(shaderPickerMenu, shaderPickerList);

	setTextFieldCPPString(shaderEditorMenu, shaderEditor_shaderName, 0.0f, 0.0f, shaderName(shaderID), 1);

	setTextFieldCPPString(shaderEditorMenu, shaderEditor_shaderPath, 0.0f, 0.0f, shaderPath(shaderID), 1);
}

// Navigation

void toMain(void)
{
	setMenu(0);
}

void toEmitterPicker(void)
{
	updateEmitterPicker();
	setMenu(1);
}

void toEmitterEditor(void)
{
	setMenu(2);
}

void toParticlePicker(void)
{
	updateParticlePicker();
	setMenu(3);
}

void toParticleEditor(void)
{
	setMenu(4);
}

void toShaderPicker(void)
{
	updateShaderPicker();
	setMenu(5);
}

void toShaderEditor(void)
{
	setMenu(6);
}

// Actions

void addEmitter(void)
{
	createEmitter();
	updateEmitterPicker();
}

void editEmitter(void)
{
	updateEmitterEditor();
	toEmitterEditor();
}

void delEmitter(void)
{
	destroyEmitter(getListSelectedIndex(emitterPickerMenu, emitterPickerList));
	updateEmitterPicker();
}

void setSelectedParticle(uint particleID)
{
	setEmitterParticle(getListSelectedIndex(emitterPickerMenu, emitterPickerList), particleID);
	updateEmitterEditor();
}

void addParticle(void)
{
	createParticle();
	updateParticlePicker();
}

void editParticle(void)
{
	updateParticleEditor();
	toParticleEditor();
}

void delParticle(void)
{
	uint id = getListSelectedIndex(particlePickerMenu, particlePickerList);
	if (id != 0)
	{
		destroyParticle(id);
		updateEmitterEditor();
		updateParticlePicker();
		updateParticleEditor();
	}
}

void setSelectedShader(uint shaderID)
{
	setParticleShader(getListSelectedIndex(particlePickerMenu, particlePickerList), shaderID);
	updateParticleEditor();
}

void addShader(void)
{
	createShader();
	updateShaderPicker();
}

void editShader(void)
{
	uint id = getListSelectedIndex(shaderPickerMenu, shaderPickerList);
	if (id != 0)
	{
		updateShaderEditor();
		toShaderEditor();
	}
}

void delShader(void)
{
	uint id = getListSelectedIndex(shaderPickerMenu, shaderPickerList);
	if (id != 0)
	{
		destroyShader(id);
		updateShaderPicker();
		updateShaderEditor();
		updateParticleEditor();
	}
}

void loadShader(void)
{
	uint id = getListSelectedIndex(shaderPickerMenu, shaderPickerList);
	reloadShader(id);
}

void loadTexture(void)
{
	uint particleID = getListSelectedIndex(particlePickerMenu, particlePickerList);
	reloadParticleTexture(particleID);
}

void interface_saveSession(void)
{
	saveCurrentSession();
}

void interface_loadSession(void)
{
	loadNewSession();
}

void interface_saveEmitters(void)
{
	exportEmitters(emitterSavePath);
}

void interface_loadEmitters(void)
{
	importEmitters(emitterSavePath);
	updateEmitterPicker();
}

void interface_saveParticles(void)
{
	exportParticles(particleSavePath);
}

void interface_loadParticles(void)
{
	importParticles(particleSavePath);
	updateParticlePicker();
}

// End of interface functions

void createInterface(int window)
{
	int curMenu, curObj;
	int baseY;
	initInterface(window);

	emitterSavePath = (char*)mem_alloc(sizeof(char) * 32);
	strcpy(emitterSavePath, "emitters.txt");

	particleSavePath = (char*)mem_alloc(sizeof(char) * 32);
	strcpy(particleSavePath, "particles.txt");
	
	// Menu 0: Main menu
	curMenu = newMenu(0, 0, NULL, NULL);
	
	newLabel(newString("Main menu"), curMenu, 5, 18);

	/*newLabel(newString("Particles:"), curMenu, 5, 40);
	curObj = newTextField(curMenu, 10, 55, 180, 20, FIELDTYPE_INT);
	setTextFieldValue(0, 2, 0, 0, scene.particleCount, 0);*/

	newLabel(newString("Draw emitters:"), curMenu, 10, 50);
	curObj = newCheckBox(curMenu, 170, 40, 15);
	setCheckBoxValue(curMenu, curObj, &scene.drawEmitters);

	newLabel(newString("Simulation running:"), curMenu, 10, 100);
	curObj = newCheckBox(curMenu, 170, 90, 15);
	setCheckBoxValue(curMenu, curObj, &scene.running);

	newButton(newString("Edit emitters"), curMenu, 10, 140, 180, 100, toEmitterPicker);

	/*newLabel(newString("Save/Load folder"), curMenu, 30, 260);
	curObj = newTextField(curMenu, 10, 265, 180, 20, FIELDTYPE_TEXT);
	setTextFieldValue(curMenu, curObj, 0.0f, 0.0f, "Chemin de sauvegarde", 0);*/

	newButton(newString("Save session"), curMenu, 10, 300, 180, 100, interface_saveSession);

	newButton(newString("Load session"), curMenu, 10, 420, 180, 100, interface_loadSession);

	newButton(newString("Exit"), curMenu, 10, DEFAULT_HEIGHT - 30, 180, 20, quit);

	// Menu 1: Emitter picker
	curMenu = newMenu(INTERFACE_WIDTH, 0, NULL, NULL);

	// Title
	newLabel(newString("Emitters"), curMenu, 5, 18);

	// List
	curObj = newList(curMenu, 10, 25, 180, 330, NULL);

	emitterPickerMenu = curMenu;
	emitterPickerList = curObj;

	// List buttons
	newButton(newString("Add"), curMenu, 10, 370, 55, 30, addEmitter);
	newButton(newString("Edit"), curMenu, 72, 370, 56, 30, editEmitter);
	newButton(newString("Delete"), curMenu, 135, 370, 55, 30, delEmitter);

	newLabel(newString("Import/Export folder"), curMenu, 20, 420);
	emitterPickerPath = newTextField(curMenu, 10, 425, 180, 20, FIELDTYPE_TEXT);
	setTextFieldValue(curMenu, emitterPickerPath, 0.0f, 0.0f, emitterSavePath, 1);

	newButton(newString("Export"), curMenu, 10, 455, 180, 45, interface_saveEmitters);
	newButton(newString("Import"), curMenu, 10, 510, 180, 45, interface_loadEmitters);

	newButton(newString("Done"), curMenu, 10, DEFAULT_HEIGHT - 30, 180, 20, toMain);

	// Menu 2: Emitter editor
	curMenu = newMenu(2 * INTERFACE_WIDTH, 0, NULL, NULL);

	emitterEditorMenu = curMenu;

	newLabel(newString("Emitter settings"), curMenu, 5, 18);

	baseY = 50;
	newLabel(newString("Position"), curMenu, 70, baseY);
	newLabel(newString("X"), curMenu, 10, baseY+24);
	emitterEditor_posX = newTextField(curMenu, 25, baseY+10, 165, 20, FIELDTYPE_FLOAT);
	newLabel(newString("Y"), curMenu, 10, baseY+49);
	emitterEditor_posY = newTextField(curMenu, 25, baseY+35, 165, 20, FIELDTYPE_FLOAT);
	newLabel(newString("Z"), curMenu, 10, baseY+74);
	emitterEditor_posZ = newTextField(curMenu, 25, baseY+60, 165, 20, FIELDTYPE_FLOAT);

	baseY = 170;
	newLabel(newString("Angle"), curMenu, 30, baseY);
	newLabel(newString("Random?"), curMenu, 110, baseY);
	emitterEditor_randomAngle = newCheckBox(curMenu, 170, baseY-12, 15);
	newLabel(newString("Pitch"), curMenu, 10, baseY+24);
	emitterEditor_pitch = newTextField(curMenu, 60, baseY+10, 130, 20, FIELDTYPE_FLOAT);
	newLabel(newString("Yaw"), curMenu, 10, baseY+49);
	emitterEditor_yaw = newTextField(curMenu, 60, baseY+35, 130, 20, FIELDTYPE_FLOAT);
	newLabel(newString("Roll"), curMenu, 10, baseY+74);
	emitterEditor_roll = newTextField(curMenu, 60, baseY+60, 130, 20, FIELDTYPE_FLOAT);

	baseY = 290;
	newLabel(newString("Particle velocity"), curMenu, 30, baseY);
	newLabel(newString("X"), curMenu, 10, baseY+24);
	emitterEditor_velX = newTextField(curMenu, 25, baseY+10, 165, 20, FIELDTYPE_FLOAT);
	newLabel(newString("Y"), curMenu, 10, baseY+49);
	emitterEditor_velY = newTextField(curMenu, 25, baseY+35, 165, 20, FIELDTYPE_FLOAT);
	newLabel(newString("Z"), curMenu, 10, baseY+74);
	emitterEditor_velZ = newTextField(curMenu, 25, baseY+60, 165, 20, FIELDTYPE_FLOAT);

	baseY = 410;
	newLabel(newString("Particle to spawn"), curMenu, 30, baseY);
	emitterEditor_particleName = newTextField(curMenu, 10, baseY+15, 110, 20, FIELDTYPE_TEXT);
	newButton(newString("Change"), curMenu, 130, baseY+10, 60, 30, toParticlePicker);

	newLabel(newString("Spawn interval (ms)"), curMenu, 30, baseY+70);
	emitterEditor_spawnInterval = newTextField(curMenu, 10, baseY+75, 180, 20, FIELDTYPE_INT);

	newButton(newString("Done"), curMenu, 10, DEFAULT_HEIGHT - 30, 180, 20, toEmitterPicker);

	// Menu 3: Particle picker
	curMenu = newMenu(3 * INTERFACE_WIDTH, 0, NULL, NULL);

	// Title
	newLabel(newString("Particles"), curMenu, 5, 18);

	// List
	curObj = newList(curMenu, 10, 25, 180, 330, setSelectedParticle);

	particlePickerMenu = curMenu;
	particlePickerList = curObj;

	// List buttons
	newButton(newString("Add"), curMenu, 10, 370, 55, 30, addParticle);
	newButton(newString("Edit"), curMenu, 72, 370, 56, 30, editParticle);
	newButton(newString("Delete"), curMenu, 135, 370, 55, 30, delParticle);

	newLabel(newString("Import/Export folder"), curMenu, 20, 420);
	particlePickerPath = newTextField(curMenu, 10, 425, 180, 20, FIELDTYPE_TEXT);
	setTextFieldValue(curMenu, particlePickerPath, 0.0f, 0.0f, particleSavePath, 1);

	newButton(newString("Export"), curMenu, 10, 455, 180, 45, interface_saveParticles);
	newButton(newString("Import"), curMenu, 10, 510, 180, 45, interface_loadParticles);

	newButton(newString("Done"), curMenu, 10, DEFAULT_HEIGHT - 30, 180, 20, toEmitterEditor);

	// Menu 4: Particle editor
	curMenu = newMenu(4 * INTERFACE_WIDTH, 0, NULL, NULL);

	particleEditorMenu = curMenu;

	newLabel(newString("Particle settings"), curMenu, 5, 18);

	baseY = 50;
	newLabel(newString("Particle name"), curMenu, 30, baseY);
	particleEditor_particleName = newTextField(curMenu, 10, baseY + 5, 180, 30, FIELDTYPE_TEXT);

	baseY = 110;
	newLabel(newString("Display options"), curMenu, 30, baseY);
	
	newLabel(newString("Red"), curMenu, 10, baseY+24);
	particleEditor_red = newTextField(curMenu, 55, baseY+10, 135, 20, FIELDTYPE_FLOAT);
	newLabel(newString("Green"), curMenu, 10, baseY+49);
	particleEditor_green = newTextField(curMenu, 55, baseY+35, 135, 20, FIELDTYPE_FLOAT);
	newLabel(newString("Blue"), curMenu, 10, baseY+74);
	particleEditor_blue = newTextField(curMenu, 55, baseY+60, 135, 20, FIELDTYPE_FLOAT);
	newLabel(newString("Alpha"), curMenu, 10, baseY+99);
	particleEditor_alpha = newTextField(curMenu, 55, baseY+85, 135, 20, FIELDTYPE_FLOAT);
	newLabel(newString("Scale"), curMenu, 10, baseY+124);
	particleEditor_scale = newTextField(curMenu, 55, baseY+110, 135, 20, FIELDTYPE_FLOAT);

	baseY = 260;
	newLabel(newString("Display time (ms)"), curMenu, 30, baseY);
	particleEditor_lifetime = newTextField(curMenu, 10, baseY+5, 180, 20, FIELDTYPE_INT);

	baseY = 310;
	newLabel(newString("Transition"), curMenu, 10, baseY);
	newButton(newString("Toggle"), curMenu, 100, baseY-14, 90, 20, particleTransitionButton);
	
	newLabel(newString("Red"), curMenu, 10, baseY+24);
	particleEditor_red2 = newTextField(curMenu, 55, baseY+10, 135, 20, FIELDTYPE_FLOAT);
	newLabel(newString("Green"), curMenu, 10, baseY+49);
	particleEditor_green2 = newTextField(curMenu, 55, baseY+35, 135, 20, FIELDTYPE_FLOAT);
	newLabel(newString("Blue"), curMenu, 10, baseY+74);
	particleEditor_blue2 = newTextField(curMenu, 55, baseY+60, 135, 20, FIELDTYPE_FLOAT);
	newLabel(newString("Alpha"), curMenu, 10, baseY+99);
	particleEditor_alpha2 = newTextField(curMenu, 55, baseY+85, 135, 20, FIELDTYPE_FLOAT);
	newLabel(newString("Scale"), curMenu, 10, baseY+124);
	particleEditor_scale2 = newTextField(curMenu, 55, baseY+110, 135, 20, FIELDTYPE_FLOAT);

	baseY = 460;
	newLabel(newString("Shader"), curMenu, 30, baseY);
	particleEditor_shaderName = newTextField(curMenu, 10, baseY+5, 110, 20, FIELDTYPE_TEXT);
	newButton(newString("Change"), curMenu, 130, baseY, 60, 30, toShaderPicker);

	baseY = 500;
	newLabel(newString("Texture path"), curMenu, 30, baseY);
	particleEditor_texturePath = newTextField(curMenu, 10, baseY+5, 180, 20, FIELDTYPE_TEXT);
	newButton(newString("Load texture"), curMenu, 10, baseY+30, 180, 20, loadTexture); 

	newButton(newString("Done"), curMenu, 10, DEFAULT_HEIGHT - 30, 180, 20, toParticlePicker);
	
	// Menu 5: Shader picker
	curMenu = newMenu(5 * INTERFACE_WIDTH, 0, NULL, NULL);

	// Title
	newLabel(newString("Shader"), curMenu, 5, 18);

	// List
	curObj = newList(curMenu, 10, 25, 180, 330, setSelectedShader);

	shaderPickerMenu = curMenu;
	shaderPickerList = curObj;

	// List buttons
	newButton(newString("Add"), curMenu, 10, 370, 55, 30, addShader);
	newButton(newString("Edit"), curMenu, 72, 370, 56, 30, editShader);
	newButton(newString("Delete"), curMenu, 135, 370, 55, 30, delShader);

	newButton(newString("Done"), curMenu, 10, DEFAULT_HEIGHT - 30, 180, 20, toParticleEditor);

	// Menu 6: Shader editor
	curMenu = newMenu(6 * INTERFACE_WIDTH, 0, NULL, NULL);
	shaderEditorMenu = curMenu;

	newLabel(newString("Shader compiler"), curMenu, 5, 18);

	baseY = 75;
	newLabel(newString("Shader name"), curMenu, 30, baseY);
	shaderEditor_shaderName = newTextField(curMenu, 10, baseY + 5, 180, 30, FIELDTYPE_TEXT);

	baseY = 150;
	newLabel(newString("Shader path"), curMenu, 30, baseY);
	shaderEditor_shaderPath = newTextField(curMenu, 10, baseY+5, 180, 20, FIELDTYPE_TEXT);

	newButton(newString("Load"), curMenu, 30, baseY + 50, 140, 20, loadShader);

	newButton(newString("Done"), curMenu, 10, DEFAULT_HEIGHT - 30, 180, 20, toShaderPicker);
}