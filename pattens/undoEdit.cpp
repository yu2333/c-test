#include "stdafx.h"
#include "undoEdit.h"


undoEdit::undoEdit()
{
	alive = true;
	hasBeenUndo = false;
	support = NULL;
}


undoEdit::~undoEdit()
{

}

bool undoEdit::canUndo()
{
	return alive && (!hasBeenUndo);
}

bool undoEdit::canRedo()
{
	return alive && hasBeenUndo;
}

string undoEdit::getPresentationName()
{
	if (hasBeenUndo)
		return getRedoPresentationName();
	else
		return getUndoPresentationName();
}

void undoEdit::die()
{
	alive = false;
}

void undoEdit::undo()
{
	if (!canUndo())
	{
		cout << endl << getUndoPresentationName() << " can't be undone." << endl;
	}
	hasBeenUndo = true;
	
	if (support != NULL)
		support->stopUpdate();
	_undo();
	if (support != NULL)
		support->startUpdate();
	cout << "Edit( " << getRedoPresentationName() << " ) has been undone." << endl;
}

void undoEdit::redo()
{
	if (!canRedo())
	{
		cout << endl << getRedoPresentationName() << " can't be redone." << endl;
	}
	hasBeenUndo = false;
	if (support != NULL)
		support->stopUpdate();
	_redo();
	if (support != NULL)
		support->startUpdate();
	cout << "Edit( " << getRedoPresentationName() << " ) has been redone." << endl;
}