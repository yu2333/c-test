#include "stdafx.h"
#include "deleteObserverEdit.h"


deleteObserverEdit::deleteObserverEdit(observable* theObservable, entry* theObserver)
{
	_observable = theObservable;
	_observer = theObserver;
	support = theObservable;
	redoName = undoName = "the observable " + _observable->getName()
		+ " deletes the observer " + _observer->getName();
}


deleteObserverEdit::~deleteObserverEdit()
{
}


void deleteObserverEdit::_undo()
{
	_observable->addObserver(_observer);
}


void deleteObserverEdit::_redo()
{
	_observable->deleteObserver(_observer);
}