#pragma once
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

