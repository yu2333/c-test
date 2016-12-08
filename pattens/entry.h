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
	void setContent(string);

	//用于检测此实体中是否包含与pe相同的实体
	virtual bool hasSame(entry *pe){ return false; };
	//用于递归展示实体内容
	virtual void display(){};
	//用于缩进
	virtual void display(string s){};

	virtual void onUpdate(entry* pe){};

protected:
	string name;
	string content;
};

