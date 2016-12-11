#include "stdafx.h"
#include "undoManager.h"


undoManager::undoManager()
{
	start = 0;
	size = 0;
	next = 0;
	duringUndo = false;
}


undoManager::~undoManager()
{
}

bool undoManager::undo()
{
	return undoTo(1);
}

bool undoManager::redo()
{
	return redoTo(1);
}


bool undoManager::undoTo(int Size)
{
	if (Size > getUndoSize())
		return false;
	else
	{
		for (int j = 0; j < Size; ++j)
		{
			if (--next < 0)
				next = MAX_UNDO - 1;
			edits[next]->undo();
		}
	}
	duringUndo = true;
	return true;
}


bool undoManager::redoTo(int Size)
{
	int redoSize = getRedoSize();
	if (Size > redoSize)
		return false;
	else
	{
		for (int j = 0; j < Size; ++j)
		{
			edits[next]->redo();
			if (++next >= MAX_UNDO)
				next = 0;
		}
	}
	duringUndo = false;
	return true;
}


void undoManager::printUndoList()
{
	int i = next;
	int undoSize = getUndoSize();
	cout << "The undo list is:" << endl;
	if (undoSize == 0)
		cout << "NULL" << endl;
	for (int j = 1; j <= undoSize; ++j)
	{
		if (--i < 0)
			i = MAX_UNDO - 1;
		cout << j << ": " << edits[i]->getPresentationName() << endl;
	}
}


void undoManager::printRedoList()
{
	int i = next;
	int redoSize = getRedoSize();
	cout << "The Redo list is:" << endl;
	if (redoSize == 0)
		cout << "NULL" << endl;
	for (int j = 1; j <= redoSize; ++j)
	{
		cout << j << ": " << edits[i]->getPresentationName() << endl;
		if (++i >= MAX_UNDO)
			i = 0;
	}
}

void undoManager::undoableEditHappened(undoEdit* anEdit)
{
	int redoSize = getRedoSize();

	//原本可以redo的操作现在失效
	int i = next;
	for (int j = 0; j < redoSize; ++j)
	{
		delete edits[i];
		if (++i >= MAX_UNDO)
			i = 0;
	}

	//重新调整大小
	size = size - redoSize + 1;

	//检测是否超出undoManager允许保存的操作数量，只保留最新的操作
	if (size == MAX_UNDO + 1)
	{
		if (start != next)
			delete edits[start];
		if (++start == MAX_UNDO)
			start = 0;
		--size;
	}

	//插入新操作
	edits[next++] = anEdit;
	if (next >= MAX_UNDO)
		next = 0;
	duringUndo = false;
}

int undoManager::getRedoSize()
{
	return size - getUndoSize();
}

int undoManager::getUndoSize()
{
	int Size = next - start;
	if (Size < 0 )
		Size += MAX_UNDO;
	if (!duringUndo && (Size == 0) && (size == MAX_UNDO))
		Size = MAX_UNDO;
	return Size;
}
