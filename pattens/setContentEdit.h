#pragma once
#include "undoEdit.h"
#include "entry.h"
class setContentEdit :
	public undoEdit
{
public:
	setContentEdit(entry*, string);
	~setContentEdit();

	string getUndoPresentationName();
	string getRedoPresentationName();

	void _undo();
	void _redo();

private:
	entry* pen;
	string orignal;
	string after;
};

