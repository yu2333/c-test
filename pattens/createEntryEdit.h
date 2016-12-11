#pragma once
#include "undoEdit.h"
#include "entry.h"
#include "entryContainer.h"
class createEntryEdit :
	public undoEdit
{
public:
	createEntryEdit(entryContainer*, entry*);
	~createEntryEdit();

	void _undo();
	void _redo();
private:
	entryContainer* _container;
	entry* _entry;
};

