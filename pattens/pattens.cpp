// pattens.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "observable.h"
#include "observer.h"
#include "undoManager.h"
#include "entryContainer.h"


#include <iostream>

using namespace std;

void clearScreen()
{
	system("cls");
	cout << "====================================\n"
		<< "            operations:\n"
		<< "        1:createObserver\n"
		<< "        2:createObservable\n"
		<< "        3:deleteEntry\n"
		<< "        4:addObserver\n"
		<< "        5:deleteObserver\n"
		<< "        6:display\n"
		<< "        7:setContent\n"
		<< "        8:update\n"
		<< "        9:undo\n"
		<< "        10:redo\n"
		<< "        11:clearScreen\n"
		<< "        12:exit\n"
		<< "====================================\n" << endl;
}

//用于读取输入指令的下一单词到currentWord
bool readNext(string& currentWord, string& input, int& current, int& next)
{
	if (next == input.size())
		return false;
	next = input.find(' ', next) + 1;
	//输入的命令读取完毕的情况
	if (next == 0)
	{
		next = input.size();
		currentWord = input.substr(current, next - current);
	}
	else
		currentWord = input.substr(current, next - current - 1);
	current = next;
	//防止连续输入空格的情况
	if (currentWord.size() == 0)
		return readNext(currentWord, input, current, next);
	return true;
}


int _tmain(int argc, _TCHAR* argv[])
{
	//初始化undo管理器与实体容器
	undoManager manager;
	entryContainer container;
	container.setUndoManager(&manager);

	clearScreen();
	while (true)
	{
		string input="";
		string currentWord="";
		string tempInput = "";
		string commond = "";					//用于缓存指令
		string parameter[2];					//用于缓存指令参数
		bool effictiveCommmond = false;			//用于记录输入的指令是否有效
		int next = 0;
		int current = 0;

		//清空缓存区并读入一行指令
		cin.clear();
		cin.sync();
		cout << "#";

		//读取指令
		getline(cin, input);
		readNext(currentWord, input, current, next);
		commond = currentWord;

		/*创建observer操作*/
		if (commond == "1" || commond == "createObserver")
		{
			//此命令有两个参数
			for (int i = 0; i < 2; ++i)
			{
				//读取命令参数
				if (!readNext(parameter[i], input, current, next))
				{
					//未输入参数时，要求补充输入
					cout << "Please intput the name and the content of the observer:"
						<< endl;
					cin >> parameter[i];
				}
			}
			//检测输入命令是否符合规范
			if (next == input.size())
			{
				container.createObserver(parameter[0], parameter[1]);
				effictiveCommmond = true;
			}
		}

		/*创建observable操作*/
		if (commond == "2" || commond == "createObservable")
		{
			//此命令有两个参数
			for (int i = 0; i < 2; ++i)
			{
				//读取命令参数
				if (!readNext(parameter[i], input, current, next))
				{
					//未输入参数时，要求补充输入
					cout << "Please intput the name and the content of the observable:"
						<< endl;
					cin >> parameter[i];
				}
			}
			//检测输入命令是否符合规范
			if (next == input.size())
			{
				if (!container.createObservable(parameter[0], parameter[1]))
					cout << "Such a name has been existed" << endl;
				effictiveCommmond = true;
			}
		}

		/*删除实体操作*/
		if (commond == "3" || commond == "deleteEntry")
		{
			//读取命令参数
			if (!readNext(parameter[0], input, current, next))
			{
				//未输入参数时，要求补充输入
				cout << "Please intput the name of the entry you whant to delete:"
					<< endl;
				cin >> parameter[0];
			}
			//检测输入命令是否符合规范
			if (next == input.size())
			{
				if (!container.eraseEntry(parameter[0]))
					cout << "There is no entry named like this." << endl;
				effictiveCommmond = true;
			}
		}

		/*为observable添加observer操作*/
		if (commond == "4" || commond == "addObserver")
		{
			//此命令有两个参数
			for (int i = 0; i < 2; ++i)
			{
				//读取命令参数
				if (!readNext(parameter[i], input, current, next))
				{
					//未输入参数时，要求补充输入
					cout << "It will add an observer to an observable, \n"
						<<"please first input the name of the observable, then the observer:"
						<< endl;
					cin >> parameter[i];
				}
			}
			//检测输入命令是否符合规范
			if (next == input.size())
			{
				entry* oble = container.find(parameter[0]);
				entry* ober = container.find(parameter[1]);
				if (oble == NULL)
					cout << "Can't find the entry: " << parameter[0] << endl;
				if (ober == NULL)
					cout << "Can't find the entry: " << parameter[1] << endl;
				if ((oble != NULL) && (ober != NULL))
				{
					if (oble->getType() == "observable")
						((observable*)oble)->addObserver(ober);
					else
						cout << parameter[0] << " is not an observable." << endl;
				}
				effictiveCommmond = true;
			}
		}



		/*为observable删除observer操作*/
		if (commond == "5" || commond == "deleteObserver")
		{
			//此命令有两个参数
			for (int i = 0; i < 2; ++i)
			{
				//读取命令参数
				if (!readNext(parameter[i], input, current, next))
				{
					//未输入参数时，要求补充输入
					cout << "It will delete an observer to an observable, \n"
						<< "please first input the name of the observable, then the observer:"
						<< endl;
					cin >> parameter[i];
				}
			}
			//检测输入命令是否符合规范
			if (next == input.size())
			{
				entry* oble = container.find(parameter[0]);
				entry* ober = container.find(parameter[1]);
				if (oble == NULL)
					cout << "Can't find the entry: " << parameter[0] << endl;
				if (ober == NULL)
					cout << "Can't find the entry: " << parameter[1] << endl;
				if ((oble != NULL) && (ober != NULL))
				{
					if (oble->getType() == "observable")
					{ 
						if (!((observable*)oble)->deleteObserver(ober))
							cout << parameter[0] + " is not connected with " + parameter[1] << endl;
					}
					else
						cout << parameter[0] << " is not an observable." << endl;
				}
				effictiveCommmond = true;
			}
		}


		/*展示操作*/
		if (commond == "6" || commond == "display")
		{
			//读取命令参数
			if (!readNext(parameter[0], input, current, next))
			{
				//未输入参数时，表示展示实体容器
				container.display();
				effictiveCommmond = true;
			}
			//输入参数时，表示展示实体
			else if (next == input.size())
			{
				entry* en = container.find(parameter[0]);
				if (en == NULL)
					cout << "There is no entry named like this." << endl;
				else
					en->display();
				effictiveCommmond = true;
			}
		}


		/*改变实体内容操作*/
		if (commond == "7" || commond == "setContent")
		{
			//此命令有两个参数
			for (int i = 0; i < 2; ++i)
			{
				//读取命令参数
				if (!readNext(parameter[i], input, current, next))
				{
					//未输入参数时，要求补充输入
					cout << "Please first input the name of the entry you want to change, then the content:"
						<< endl;
					cin >> parameter[i];
				}
			}
			//检测输入命令是否符合规范
			if (next == input.size())
			{
				entry* en = container.find(parameter[0]);
				if (en == NULL)
					cout << "Can't find the entry: " << parameter[0] << endl;
				else
					en->setContent(parameter[1]);
				effictiveCommmond = true;
			}
		}

		/*更新操作*/
		if (commond == "8" || commond == "update")
		{
			//读取命令参数
			if (!readNext(parameter[0], input, current, next))
			{
				//未输入参数时，要求补充输入
				cout << "Please first input the name of the entry you want to update:"
					<< endl;
				cin >> parameter[0];
			}
			//检测输入命令是否符合规范
			if (next == input.size())
			{
				entry* en = container.find(parameter[0]);
				if (en == NULL)
					cout << "Can't find the entry: " << parameter[0] << endl;
				else if (en->getType() == "observable")
					en->onUpdate(en);
				else
					cout << parameter[0] <<" is not an observable."<< endl;
				effictiveCommmond = true;
			}
		}

		/*undo操作*/
		if (commond == "9" || commond == "undo")
		{
			//读取命令参数
			if (!readNext(parameter[0], input, current, next))
			{
				//未输入参数时，输出可撤回操作列表
				manager.printUndoList();
				cout << "\nPlease input how many edits you want to undo: ";
				cin >> parameter[0];
			}
			if (next == input.size())
			{
				int tempi = std::atoi(parameter[0].c_str());
				if (tempi > 0)
				{
					if (!manager.undoTo(tempi))
						cout << "The number you input is too large." << endl;
					effictiveCommmond = true;
				}
			}
		}

		/*redo操作*/
		if (commond == "10" || commond == "redo")
		{
			//读取命令参数
			if (!readNext(parameter[0], input, current, next))
			{
				//未输入参数时，输出可撤回操作列表
				manager.printRedoList();
				cout << "\nPlease input how many edits you want to redo: ";
				cin >> parameter[0];
			}
			if (next == input.size())
			{
				int tempi = std::atoi(parameter[0].c_str());
				if (tempi > 0)
				{
					if (!manager.redoTo(tempi))
						cout << "The number you input is too large." << endl;
					effictiveCommmond = true;
				}
			}
		}

		/*清屏操作*/
		if (commond == "11" || commond == "clearScreen")
		{
			if (next == input.size())
			{
				clearScreen();
				effictiveCommmond = true;
			}
		}

		/*清屏操作*/
		if (commond == "12" || commond == "exit")
		{
			break;
		}

		if (!effictiveCommmond)
			cout << "error input!"
			<< endl;
	}
	/*
	undoManager manager;
	entryContainer container;
	container.setUndoManager(&manager);
	container.createObservable("ob1", "1");
	container.createObservable("ob2", "2");
	container.createObservable("ob3", "3");
	container.createObservable("ob4", "4");
	container.createObserver("ob5", "5");
	container.createObserver("ob6", "6");
	entry* tempE = container.find("ob1");
	if (tempE->getType() == "observable")
		((observable*)tempE)->addObserver(container.find("ob2"));
	tempE = container.find("ob2");
	if (tempE->getType() == "observable")
		((observable*)tempE)->addObserver(container.find("ob3"));
	tempE = container.find("ob2");
	if (tempE->getType() == "observable")
		((observable*)tempE)->addObserver(container.find("ob4"));
	tempE = container.find("ob1");
	if (tempE->getType() == "observable")
		((observable*)tempE)->addObserver(container.find("ob5"));
	tempE = container.find("ob3");
	if (tempE->getType() == "observable")
		((observable*)tempE)->addObserver(container.find("ob6"));

	tempE = container.find("ob2");
	tempE->setContent("233");
	if (tempE->getType() == "observable")
		((observable*)tempE)->updateAll(tempE);
	manager.printUndoList();
	manager.printRedoList();
	manager.undoTo(5);
	container.createObserver("ob7", "7");
	container.display();
	manager.printRedoList();
	manager.redoTo(5);
	container.display();
	manager.printUndoList();
	manager.undo();
	system("pause");*/
	return 0;
}

