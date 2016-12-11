#include "stdafx.h"
#include "eraseEntryEdit.h"


eraseEntryEdit::eraseEntryEdit(entryContainer* container, entry* Entry)
{
	support = container;
	_container = container;
	_entry = Entry;
	redoName = undoName = "Delete the entry: " + Entry->getName();
}


eraseEntryEdit::~eraseEntryEdit()
{
	if (canUndo())
		delete _entry;
}


void eraseEntryEdit::_redo()
{
	compoundEdit::_redo();
	_container->eraseEntry(_entry->getName());
}

void eraseEntryEdit::_undo()
{
	_container->createEntry(_entry);
	compoundEdit::_undo();
}