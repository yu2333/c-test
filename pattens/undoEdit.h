#pragma once
#include "abstractUndoSupport.h"
class undoEdit
{
public:
	undoEdit();
	virtual ~undoEdit();

	bool canUndo();
	bool canRedo();
	void undo();						//ʵ��ʹ���������ص�_undo()���˲���Ϊ��ֹundoʱ���ûᴥ���ɳ��ز����ĺ���
	void redo();
	string getPresentationName();

	virtual void die();
	virtual void end(){};

	virtual bool addEdit(undoEdit*){ return false; };			//�����Ƿ������Ӳ���
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

