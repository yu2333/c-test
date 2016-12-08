#pragma once
#include "compoundEdit.h"
#include "entry.h"
class upDateEdit :
	public compoundEdit
{
public:
	upDateEdit(entry*, string);
	~upDateEdit();

	string getUndoPresentationName();
	string getRedoPresentationName();
	bool addEdit(undoEdit*);

	void _undo();
	void _redo();

private:
	entry* pen;
	string orignal;
	string after;
};

