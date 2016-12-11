#include "stdafx.h"
#include "createEntryEdit.h"


createEntryEdit::createEntryEdit(entryContainer* container, entry* Entry)
{
	support = container;
	_container = container;
	_entry = Entry;
	redoName = undoName = "creating " + Entry->getType() + ": " + Entry->getName();
}


createEntryEdit::~createEntryEdit()
{
	if (canRedo())
		delete _entry;
}


void createEntryEdit::_undo()
{
	_container->eraseEntry(_entry->getName());
}

void createEntryEdit::_redo()
{
	_container->createEntry(_entry);
}