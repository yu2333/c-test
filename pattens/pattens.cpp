// pattens.cpp : �������̨Ӧ�ó������ڵ㡣
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

//���ڶ�ȡ����ָ�����һ���ʵ�currentWord
bool readNext(string& currentWord, string& input, int& current, int& next)
{
	if (next == input.size())
		return false;
	next = input.find(' ', next) + 1;
	//����������ȡ��ϵ����
	if (next == 0)
	{
		next = input.size();
		currentWord = input.substr(current, next - current);
	}
	else
		currentWord = input.substr(current, next - current - 1);
	current = next;
	//��ֹ��������ո�����
	if (currentWord.size() == 0)
		return readNext(currentWord, input, current, next);
	return true;
}


int _tmain(int argc, _TCHAR* argv[])
{
	//��ʼ��undo��������ʵ������
	undoManager manager;
	entryContainer container;
	container.setUndoManager(&manager);

	clearScreen();
	while (true)
	{
		string input="";
		string currentWord="";
		string tempInput = "";
		string commond = "";					//���ڻ���ָ��
		string parameter[2];					//���ڻ���ָ�����
		bool effictiveCommmond = false;			//���ڼ�¼�����ָ���Ƿ���Ч
		int next = 0;
		int current = 0;

		//��ջ�����������һ��ָ��
		cin.clear();
		cin.sync();
		cout << "#";

		//��ȡָ��
		getline(cin, input);
		readNext(currentWord, input, current, next);
		commond = currentWord;

		/*����observer����*/
		if (commond == "1" || commond == "createObserver")
		{
			//����������������
			for (int i = 0; i < 2; ++i)
			{
				//��ȡ�������
				if (!readNext(parameter[i], input, current, next))
				{
					//δ�������ʱ��Ҫ�󲹳�����
					cout << "Please intput the name and the content of the observer:"
						<< endl;
					cin >> parameter[i];
				}
			}
			//������������Ƿ���Ϲ淶
			if (next == input.size())
			{
				container.createObserver(parameter[0], parameter[1]);
				effictiveCommmond = true;
			}
		}

		/*����observable����*/
		if (commond == "2" || commond == "createObservable")
		{
			//����������������
			for (int i = 0; i < 2; ++i)
			{
				//��ȡ�������
				if (!readNext(parameter[i], input, current, next))
				{
					//δ�������ʱ��Ҫ�󲹳�����
					cout << "Please intput the name and the content of the observable:"
						<< endl;
					cin >> parameter[i];
				}
			}
			//������������Ƿ���Ϲ淶
			if (next == input.size())
			{
				if (!container.createObservable(parameter[0], parameter[1]))
					cout << "Such a name has been existed" << endl;
				effictiveCommmond = true;
			}
		}

		/*ɾ��ʵ�����*/
		if (commond == "3" || commond == "deleteEntry")
		{
			//��ȡ�������
			if (!readNext(parameter[0], input, current, next))
			{
				//δ�������ʱ��Ҫ�󲹳�����
				cout << "Please intput the name of the entry you whant to delete:"
					<< endl;
				cin >> parameter[0];
			}
			//������������Ƿ���Ϲ淶
			if (next == input.size())
			{
				if (!container.eraseEntry(parameter[0]))
					cout << "There is no entry named like this." << endl;
				effictiveCommmond = true;
			}
		}

		/*Ϊobservable���observer����*/
		if (commond == "4" || commond == "addObserver")
		{
			//����������������
			for (int i = 0; i < 2; ++i)
			{
				//��ȡ�������
				if (!readNext(parameter[i], input, current, next))
				{
					//δ�������ʱ��Ҫ�󲹳�����
					cout << "It will add an observer to an observable, \n"
						<<"please first input the name of the observable, then the observer:"
						<< endl;
					cin >> parameter[i];
				}
			}
			//������������Ƿ���Ϲ淶
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



		/*Ϊobservableɾ��observer����*/
		if (commond == "5" || commond == "deleteObserver")
		{
			//����������������
			for (int i = 0; i < 2; ++i)
			{
				//��ȡ�������
				if (!readNext(parameter[i], input, current, next))
				{
					//δ�������ʱ��Ҫ�󲹳�����
					cout << "It will delete an observer to an observable, \n"
						<< "please first input the name of the observable, then the observer:"
						<< endl;
					cin >> parameter[i];
				}
			}
			//������������Ƿ���Ϲ淶
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


		/*չʾ����*/
		if (commond == "6" || commond == "display")
		{
			//��ȡ�������
			if (!readNext(parameter[0], input, current, next))
			{
				//δ�������ʱ����ʾչʾʵ������
				container.display();
				effictiveCommmond = true;
			}
			//�������ʱ����ʾչʾʵ��
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


		/*�ı�ʵ�����ݲ���*/
		if (commond == "7" || commond == "setContent")
		{
			//����������������
			for (int i = 0; i < 2; ++i)
			{
				//��ȡ�������
				if (!readNext(parameter[i], input, current, next))
				{
					//δ�������ʱ��Ҫ�󲹳�����
					cout << "Please first input the name of the entry you want to change, then the content:"
						<< endl;
					cin >> parameter[i];
				}
			}
			//������������Ƿ���Ϲ淶
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

		/*���²���*/
		if (commond == "8" || commond == "update")
		{
			//��ȡ�������
			if (!readNext(parameter[0], input, current, next))
			{
				//δ�������ʱ��Ҫ�󲹳�����
				cout << "Please first input the name of the entry you want to update:"
					<< endl;
				cin >> parameter[0];
			}
			//������������Ƿ���Ϲ淶
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

		/*undo����*/
		if (commond == "9" || commond == "undo")
		{
			//��ȡ�������
			if (!readNext(parameter[0], input, current, next))
			{
				//δ�������ʱ������ɳ��ز����б�
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

		/*redo����*/
		if (commond == "10" || commond == "redo")
		{
			//��ȡ�������
			if (!readNext(parameter[0], input, current, next))
			{
				//δ�������ʱ������ɳ��ز����б�
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

		/*��������*/
		if (commond == "11" || commond == "clearScreen")
		{
			if (next == input.size())
			{
				clearScreen();
				effictiveCommmond = true;
			}
		}

		/*��������*/
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

