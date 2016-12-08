#include "stdafx.h"
#include "addObserverEdit.h"



addObserverEdit::addObserverEdit(observable* theObservable, entry* theObserver)
{
	_observable = theObservable;
	_observer = theObserver;
	support = theObservable;
	redoName = undoName = "the observable " + _observable->getName()
		+ " adds the observer " + _observer->getName();
}


addObserverEdit::~addObserverEdit()
{
}

void addObserverEdit::_undo()
{
	_observable->deleteObserver(_observer);
}


void addObserverEdit::_redo()
{
	_observable->addObserver(_observer);
}