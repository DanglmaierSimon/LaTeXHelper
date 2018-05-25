//Multiple Inclusion Protection
#ifndef MENUENTRY_H
#define MENUENTRY_H


#include "Object.h"
class MenuEntry :
	public Object
{
public:
	MenuEntry();
	~MenuEntry();
	virtual void Print() = 0;
	virtual void Execute() = 0;
};

#endif//MENUENTRY_H