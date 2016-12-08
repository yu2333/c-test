#include "stdafx.h"
#include "undoManager.h"


undoManager::undoManager()
{
	start = 0;
	end = -1;
	next = 0;
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


bool undoManager::undoTo(int size)
{
	if (size > getRedoSize())
		return false;
	else
	{
		if (--next < 0)
			next = MAX_UNDO - 1;
		for (int j = 0; j < size; ++j)
		{
			edits[next]->undo();
			if (--next < 0)
				next = MAX_UNDO - 1;
		}
	}
	return true;
}


bool undoManager::redoTo(int size)
{
	if (size > getRedoSize())
		return false;
	else
	{
		for (int j = 0; j < size; ++j)
		{
			edits[next]->redo();
			if (++next >= MAX_UNDO)
				next = 0;
		}
	}
	return true;
}


void undoManager::printUndoList()
{
	int i = next;
	int j = 1;
	if (--i < 0)
		i = MAX_UNDO - 1;
	while (i != start)
	{
		cout << j << ': ' << edits[i]->getPresentationName() << endl;
		++j;
		if (--i < 0)
			i = MAX_UNDO - 1;
	}
	if (end != -1)
	{
		cout << j << ': ' << edits[i]->getPresentationName() << endl;
	}
}


void undoManager::printRedoList()
{
	int i = next;
	if (--i < 0)
		i = MAX_UNDO - 1;
	int j = 1;
	while (i != end && end != -1)
	{
		if (++i >= MAX_UNDO)
			i = 0;
		cout << j << ': ' << edits[i]->getPresentationName() << endl;
		++j;
	}
	if (end != -1)
	{
		cout << j << ': ' << edits[i]->getPresentationName() << endl;
	}
}

void undoManager::undoableEditHappened(undoEdit* anEdit)
{
	//检测是否超出undoManager允许保存的操作数量，只保留最新的操作
	if (end + start == MAX_UNDO - 1)
	{
		delete edits[start];
		if (++start == MAX_UNDO)
			start = 0;
	}
	//原本可以redo的操作现在失效
	int i = next;
	if (--i < 0)
		i = MAX_UNDO - 1;
	while (i != end && end != -1)
	{
		if (++i >= MAX_UNDO)
			i = 0;
		delete edits[i];
	}
	if (end != -1)
	{
		delete edits[i];
	}
	end = next;
	//插入新操作
	edits[next++] = anEdit;
	if (next >= MAX_UNDO)
		next = 0;
}

int undoManager::getUndoSize()
{
	int size = end - next + 1;
	if (size <= 0 && end != -1)
	{
		size += MAX_UNDO;
	}
	return size;
}

int undoManager::getRedoSize()
{
	int size = next - start - 1;
	if (size <= 0 && end != -1)
	{
		size += MAX_UNDO;
	}
	return size;
}
