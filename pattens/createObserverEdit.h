#pragma once
#include "undoEdit.h"
#include "entry.h"
#include "entryContainer.h"
class createObserverEdit :
	public undoEdit
{
public:
	createObserverEdit(entryContainer*,entry*);
	~createObserverEdit();

	void _undo();
	void _redo();
private:
	entryContainer* _container;
	entry* _entry;
};

