#include <Utils/public.h>
#include <Utils/mem_libs.h>
#include "interface.h"
#include "scene.h"
#include <Utils/utils.h>
#include "window.h"
#include <Engine/engine_wrapper.h>

/*
interface_init.c

- Interface creation
*/

// Interface variables

int r = 0, g = 0, b = 0;
char* texture_path;
float particle_speed = 0;

// End of interface variables

// Interface functions

// Navigation

void toMain(void)
{
	setMenu(0);
}

void toEmitterPicker(void)
{
	setMenu(1);
}

void toEmitterEditor(void)
{
	setMenu(2);
}

void toParticlePicker(void)
{
	setMenu(3);
}

void toParticleEditor(void)
{
	setMenu(4);
}

void toShaderPicker(void)
{
	setMenu(5);
}

void toShaderEditor(void)
{
	setMenu(6);
}

// Actions

void addEmitter(void)
{

}

void editEmitter(void)
{
	// TODO: Update the data we use
	toEmitterEditor();
}

void delEmitter(void)
{

}

void addParticle(void)
{

}

void editParticle(void)
{
	// TODO: Update the data we use
	toParticleEditor();
}

void delParticle(void)
{

}

void addShader(void)
{

}

void editShader(void)
{
	// TODO: Update the data we use
	toShaderEditor();
}

void delShader(void)
{

}

// End of interface functions

void createInterface(int window)
{
	int curMenu, curObj;
	initInterface(window);

	texture_path = (char*)mem_alloc(255 * sizeof(char));
	texture_path[0] = '\0';
	
	// Menu 0: Main menu
	curMenu = newMenu(0, 0, NULL, NULL);
	
	newLabel(newString("Main menu"), curMenu, 5, 18);

	newLabel(newString("Particles:"), curMenu, 5, 40);
	curObj = newTextField(curMenu, 10, 55, 180, 20, FIELDTYPE_INT);
	//setTextFieldValue(0, 2, 0, 0, scene.particleCount, 0);

	newLabel(newString("Simulation running:"), curMenu, 10, 100);
	curObj = newCheckBox(curMenu, 170, 90, 15);
	setCheckBoxValue(curMenu, curObj, &scene.running);

	newButton(newString("Edit emitters"), curMenu, 10, 140, 180, 100, toEmitterPicker);



	newButton(newString("Exit"), curMenu, 10, DEFAULT_HEIGHT - 30, 180, 20, quit);

	// Menu 1: Emitter picker
	curMenu = newMenu(INTERFACE_WIDTH, 0, NULL, NULL);

	// Title
	newLabel(newString("Emitters"), curMenu, 5, 18);

	// List
	curObj = newList(curMenu, 10, 25, 180, 330, NULL);

	// List buttons
	newButton(newString("Add"), curMenu, 10, 370, 55, 30, addEmitter);
	newButton(newString("Edit"), curMenu, 72, 370, 56, 30, editEmitter);
	newButton(newString("Delete"), curMenu, 135, 370, 55, 30, delEmitter);

	newButton(newString("Done"), curMenu, 10, DEFAULT_HEIGHT - 30, 180, 20, toMain);

	// Menu 2: Emitter editor
	curMenu = newMenu(2 * INTERFACE_WIDTH, 0, NULL, NULL);

	newLabel(newString("Emitter settings"), curMenu, 5, 18);
	
	// TODO:
	// Position
	// Angle (or random)
	// Particle
	// Velocity
	// Spawn interval

	newButton(newString("Done"), curMenu, 10, DEFAULT_HEIGHT - 30, 180, 20, toEmitterPicker);

	// Menu 3: Particle picker
	curMenu = newMenu(3 * INTERFACE_WIDTH, 0, NULL, NULL);

	// Title
	newLabel(newString("Particles"), curMenu, 5, 18);

	// List
	curObj = newList(curMenu, 10, 25, 180, 330, NULL);

	// List buttons
	newButton(newString("Add"), curMenu, 10, 370, 55, 30, addParticle);
	newButton(newString("Edit"), curMenu, 72, 370, 56, 30, editParticle);
	newButton(newString("Delete"), curMenu, 135, 370, 55, 30, delParticle);

	newButton(newString("Pick"), curMenu, 10, DEFAULT_HEIGHT - 30, 180, 20, toEmitterEditor);

	// Menu 4: Particle editor
	curMenu = newMenu(4 * INTERFACE_WIDTH, 0, NULL, NULL);

	newLabel(newString("Particle settings"), curMenu, 5, 18);

	// TODO:
	// Name
	// Position
	// Velocity
	// Lifetime
	// Shader
	
	// Menu 5: Shader picker
	curMenu = newMenu(5 * INTERFACE_WIDTH, 0, NULL, NULL);

	// Title
	newLabel(newString("Shader"), curMenu, 5, 18);

	// List
	curObj = newList(curMenu, 10, 25, 180, 330, NULL);

	// List buttons
	newButton(newString("Add"), curMenu, 10, 370, 55, 30, addShader);
	newButton(newString("Edit"), curMenu, 72, 370, 56, 30, editShader);
	newButton(newString("Delete"), curMenu, 135, 370, 55, 30, delShader);

	newButton(newString("Done"), curMenu, 10, DEFAULT_HEIGHT - 30, 180, 20, toParticleEditor);

	// Menu 6: Shader editor
	curMenu = newMenu(6 * INTERFACE_WIDTH, 0, NULL, NULL);

	newLabel(newString("Shader compiler"), curMenu, 5, 18);

	// TODO: Shader text field

	newButton(newString("Compile & Save"), curMenu, 10, DEFAULT_HEIGHT - 30, 180, 20, toShaderPicker);
}