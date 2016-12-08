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
	void printUndoList();		//��ӡ�ɽ��е�undo����
	void printRedoList();		//��ӡ�ɽ��е�redo����
	int getUndoSize();			//���ؿ���������undo����
	int getRedoSize();			//���ؿ���������redo����

	void undoableEditHappened(undoEdit*);

private:
	undoEdit* edits[MAX_UNDO];
	int start;
	int next;
	int end;
};
