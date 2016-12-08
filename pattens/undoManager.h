#pragma once
#include "undoEdit.h"
#define MAX_UNDO 5
class undoManager
{
public:
	undoManager();
	~undoManager();

	bool undo();
	bool redo();
	bool undoTo(int);
	bool redoTo(int);
	void printUndoList();		//打印可进行的undo操作
	void printRedoList();		//打印可进行的redo操作
	int getUndoSize();			//返回可以做几次undo操作
	int getRedoSize();			//返回可以做几次redo操作

	void undoableEditHappened(undoEdit*);

private:
	undoEdit* edits[MAX_UNDO];
	int start;
	int next;
	int end;
};
