#include <Utils/public.h>
#include <Utils/mem_libs.h>
#include "interface.h"
#include "scene.h"
#include <Utils/utils.h>
#include "window.h"

/*
interface_init.c

- Interface creation
*/

// Interface variables

int r = 0, g = 0, b = 0;
// Alternative, mieux ?
// int rgb[] = {0, 0, 0};
char* texture_path;
float particle_speed = 0;

// End of interface variables

void debug(void)
{
	printf("--------- Debug ---------\n");
	printf("R - G - B : %d - %d - %d\n", r, g, b);
	printf("Texture path : %s\n", texture_path);
	printf("Particle speed : %f\n", particle_speed);
	printf("------- Fin Debug -------\n");
}

void createInterface(int window)
{
	int menu_id;
	int textField_R, textField_G, textField_B, textField_texturePath, slider_particleSpeed;
	initInterface(window);

	texture_path = (char*)mem_alloc(255 * sizeof(char));
	texture_path[0] = '\0';
	
	// Menu 0: Main menu
	menu_id = newMenu(0, 0, NULL, NULL);
	
	// Color picking
	newLabel(newString("Color : "), menu_id, 5, 18);

	// Red
	newLabel(newString("R"), menu_id, 5, 42);
	textField_R = newTextField(menu_id, 20, 28, 40, 20, FIELDTYPE_INT);
	setTextFieldValue(menu_id, textField_R, 0, 255, &r, 1);

	// Green
	newLabel(newString("G"), menu_id, 70, 42);
	textField_G = newTextField(menu_id, 85, 28, 40, 20, FIELDTYPE_INT);
	setTextFieldValue(menu_id, textField_G, 0, 255, &g, 1);

	// Blue
	newLabel(newString("B"), menu_id, 135, 42);
	textField_B = newTextField(menu_id, 150, 28, 40, 20, FIELDTYPE_INT);
	setTextFieldValue(menu_id, textField_B, 0, 255, &b, 1);

	// Texture path
	newLabel(newString("Texture path : "), menu_id, 5, 72);
	textField_texturePath = newTextField(menu_id, 5, 82, 190, 20, FIELDTYPE_TEXT);
	setTextFieldValue(menu_id, textField_texturePath, 0, 0, texture_path, 1);

	// Particle speed
	newLabel(newString("Particle speed : "), menu_id, 5, 122);
	slider_particleSpeed = newSlider(menu_id, 5, 138, 190);
	setSliderValue(menu_id, slider_particleSpeed, 0, 255, &particle_speed);
	
	newButton(newString("Debug"), menu_id, 10, DEFAULT_HEIGHT - 60, 180, 20, debug);

	newButton(newString("Exit"), menu_id, 10, DEFAULT_HEIGHT - 30, 180, 20, quit);
}
