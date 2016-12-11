#include "stdafx.h"
#include "compoundEdit.h"


compoundEdit::compoundEdit()
{
	inProgress = true;
}



compoundEdit::~compoundEdit()
{
	for (int i = edits.size() - 1; i >= 0; --i)
	{
		delete edits[i];
	}
}

bool compoundEdit::addEdit(undoEdit* anEdit)
{
	if (inProgress)
	{
		edits.push_back(anEdit);
		return true;
	}
	return false;
}


void compoundEdit::_undo()
{
	for (int i = edits.size() - 1; i >= 0; --i)
	{
		edits[i]->undo();
	}
}

void compoundEdit::_redo()
{
	for (unsigned i = 0; i <edits.size(); ++i)
	{
		edits[i]->redo();
	}
}