#include "stdafx.h"
#include "upDateEdit.h"

upDateEdit::upDateEdit(entry* Entry, string s)
{
	orignal = Entry->getContent();
	after = s;
	support = Entry;
	pen = Entry;

	redoName = undoName = "update the content of " + Entry->getName();
}


upDateEdit::~upDateEdit()
{
}

string upDateEdit::getRedoPresentationName()
{
	return redoName;
}

string upDateEdit::getUndoPresentationName()
{
	return undoName;
}

bool upDateEdit::addEdit(undoEdit* aEdit)
{
	if (compoundEdit::addEdit(aEdit))
	{
		return true;
	}
	return false;
}

void upDateEdit::_undo()
{
	compoundEdit::_undo();
	pen->setContent(orignal);
}

void upDateEdit::_redo()
{
	compoundEdit::_redo();
	pen->setContent(after);
}
