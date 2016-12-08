#include "stdafx.h"
#include "setContentEdit.h"


setContentEdit::setContentEdit(entry* Entry, string s)
{
	orignal = Entry->getContent();
	after = s;
	support = Entry;

	undoName = "set the content of " + Entry->getName();
	redoName = "recover the content of " + Entry->getName();
}


setContentEdit::~setContentEdit()
{
}


string setContentEdit::getRedoPresentationName()
{
	return redoName;
}

string setContentEdit::getUndoPresentationName()
{
	return undoName;
}


void setContentEdit::_undo()
{
	pen->setContent(orignal);
}

void setContentEdit::_redo()
{
	pen->setContent(after);
}