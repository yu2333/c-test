#pragma once
#include "undoEdit.h"
#include <vector>
class compoundEdit :
	public undoEdit
{
public:
	compoundEdit();
	~compoundEdit();

	bool isInProgress(){ return inProgress; };
	void end(){ inProgress = false; };

	virtual bool addEdit(undoEdit*);
	virtual void _undo();
	virtual void _redo();
protected:
	bool inProgress;
	vector<undoEdit*> edits;
};

