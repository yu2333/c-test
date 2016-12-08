#pragma once
#include "undoEdit.h"
#include "observable.h"
class addObserverEdit :
	public undoEdit
{
public:
	addObserverEdit(observable*, entry*);
	~addObserverEdit();

	virtual void _undo();
	virtual void _redo();

private:
	observable* _observable;
	entry* _observer;
};

