#include "stdafx.h"
#include "createObserverEdit.h"


createObserverEdit::createObserverEdit(entryContainer* container,entry* Entry)
{
	support = container;
	_container = container;
	_entry = Entry;
}


createObserverEdit::~createObserverEdit()
{	
}

void createObserverEdit::_undo()
{
	_container->stopUpdate();
	_container->eraseEntry(_entry->getName());
	_container->startUpdate();
}

void createObserverEdit::_redo()
{
	_container->stopUpdate();
	_container->createEntry(_entry);
	_container->startUpdate();
}