#pragma once
#include "entry.h"
#include "observable.h"
class observer :
	public entry
{
public:
	observer(string Name, string Content);
	~observer();

	virtual bool hasSame(entry *pe);
	virtual void onUpdate(entry* pe);
	virtual void display();
	virtual void display(string s);
};

