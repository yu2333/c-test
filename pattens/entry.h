#pragma once
#include "undoSupport.h"
class entry:
	public undoSupport
{
public:
	entry();
	~entry();
	string getName(){ return name; };
	string getContent(){ return content; };
	string getType(){ return type; };
	string toStirng(){ return type + ": " + name + "   content: " + content; };
	void setContent(string);

	//���ڼ���ʵ�����Ƿ������pe��ͬ��ʵ��
	virtual bool hasSame(entry *pe){ return false; };
	//���ڵݹ�չʾʵ������
	virtual void display(){};
	//��������
	virtual void display(string s){};

	virtual void onUpdate(entry* pe){};

protected:
	string name;
	string content;
	string type;
};

