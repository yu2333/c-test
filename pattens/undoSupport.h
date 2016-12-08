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
	bool requireUndo();					//�����Ƿ���Ҫ����undo����

private:
	compoundEdit* _compoundEdit;
	undoManager* _undoManager;
};

