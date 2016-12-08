#include "stdafx.h"
#include "undoSupport.h"


undoSupport::undoSupport()
{
	_compoundEdit = NULL;
	_undoManager = NULL;
}


undoSupport::~undoSupport()
{
}

void undoSupport::setCompoundEdit(compoundEdit* CompoundEdit)
{
	_compoundEdit = CompoundEdit;
}

void undoSupport::setUndoManager(undoManager* UndoManager)
{
	_undoManager = UndoManager;
}

void undoSupport::postEdit(undoEdit* anEdit)
{
	if (!canUpdate() || anEdit == NULL)
		return;
	//此操作时复合操作的一部分时
	if (_compoundEdit != NULL)
	{
		_compoundEdit->addEdit(anEdit);
		_compoundEdit = NULL;
	}
	//此操作被undoManager管理时
	if (_undoManager != NULL)
		_undoManager->undoableEditHappened(anEdit);
}


void undoSupport::endCompoundEdit()
{
	if (_compoundEdit != NULL)
		_compoundEdit->end();
}

bool undoSupport::requireUndo()
{
	return ((_compoundEdit != NULL) || (_undoManager != NULL)) && canUpdate();
}