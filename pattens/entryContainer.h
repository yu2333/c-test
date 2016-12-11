#pragma once
#include <map>
#include <string>
#include "entry.h"
#include "undoSupport.h"
#include "observable.h"
#include "observer.h"
#include "undoManager.h"
class entryContainer:
	public undoSupport
{
public:
	entryContainer();
	~entryContainer();

	void display();
	
	bool createObserver(string, string);
	bool createObservable(string, string);
	bool createEntry(entry*);
	bool eraseEntry(string);

	entry* find(string);

private:
	map<string, entry*> _container;
};

