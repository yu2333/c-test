#pragma once
#include <iostream>
#include <string>
using std::string;

using namespace std;
class entry
{
public:
	entry();
	~entry();
	string getName(){ return name; };
	string getContent(){ return content; };

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
};

