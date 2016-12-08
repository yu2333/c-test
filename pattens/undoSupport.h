#pragma once

#include "abstractUndoSupport.h"
#include "compoundEdit.h"
#include "undoManager.h"
class undoSupport :
	public abstractUndoSupport
{
public:
	undoSupport();
	virtual ~undoSupport();

	void setCompoundEdit(compoundEdit*);
	void setUndoManager(undoManager*);
	undoManager* getUndoManager(){ return _undoManager; };

protected:
	void postEdit(undoEdit*);
	void endCompoundEdit();
	bool requireUndo();					//返回是否需要进行undo操作

private:
	compoundEdit* _compoundEdit;
	undoManager* _undoManager;
};

