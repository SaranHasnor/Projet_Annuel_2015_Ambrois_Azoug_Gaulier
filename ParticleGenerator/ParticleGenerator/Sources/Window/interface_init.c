#include "public.h"
#include <Utils\mem_libs.h>
#include "interface.h"
#include "scene.h"
#include <Utils\utils.h>
#include "window.h"

/*
interface_init.c

- Interface creation
*/

// Interface variables


// End of interface variables


void createInterface(int window)
{
	initInterface(window);
	
	// Menu 0: Main menu
	newMenu(0, 0, NULL, NULL);
	
	newLabel(newString("Default"), 0, 5, 18);
	
	newButton(newString("Exit"), 0, 10, DEFAULT_HEIGHT - 30, 180, 20, quit);
}
