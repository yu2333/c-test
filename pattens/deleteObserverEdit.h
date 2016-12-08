#pragma once
#include "undoEdit.h"
#include "observable.h"
class deleteObserverEdit :
	public undoEdit
{
public:
	deleteObserverEdit(observable*, entry*);
	~deleteObserverEdit();

	virtual void _undo();
	virtual void _redo();

private:
	observable* _observable;
	entry* _observer;
};

