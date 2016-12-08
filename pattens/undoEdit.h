#pragma once
#include "abstractUndoSupport.h"
class undoEdit
{
public:
	undoEdit();
	virtual ~undoEdit();

	bool canUndo();
	bool canRedo();
	void undo();						//实际使用子类重载的_undo()，此操作为防止undo时调用会触发可撤回操作的函数
	void redo();
	string getPresentationName();

	virtual void die();
	virtual void end(){};

	virtual bool addEdit(undoEdit*){ return false; };			//返回是否可以添加操作
	virtual string getUndoPresentationName(){ return undoName; };
	virtual string getRedoPresentationName(){ return redoName; };

protected:
	bool hasBeenUndo;
	bool alive;
	string undoName;
	string redoName;
	abstractUndoSupport* support;

	virtual void _undo(){};
	virtual void _redo(){};
};

