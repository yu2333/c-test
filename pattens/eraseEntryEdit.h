#pragma once
#include "compoundEdit.h"
#include "entry.h"
#include "entryContainer.h"
class eraseEntryEdit :
	public compoundEdit
{
public:
	eraseEntryEdit(entryContainer*, entry*);
	~eraseEntryEdit();

	void _undo();
	void _redo();
private:
	entryContainer* _container;
	entry* _entry;
};

