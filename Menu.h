//Multiple Inclusion Protection
#ifndef MENU_H
#define MENU_H


#include "MenuEntry.h"
class Menu :
	public MenuEntry
{
public:
	Menu();
	~Menu();
};

#endif//MENU_H