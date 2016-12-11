#include "stdafx.h"
#include "observable.h"
#include "upDateEdit.h"
#include "addObserverEdit.h"
#include "deleteObserverEdit.h"


observable::observable(string Name, string Content)
{
	name = Name;
	content = Content;
	type = "observable";
}


observable::~observable()
{
}


void observable::display()
{
	list<entry*>::iterator it = obList.begin();
	cout << "observable: " << name << " content: " << content << endl;
	for (; it != obList.end(); ++it)
	{
		(*it)->display("");
	}
	
}

void observable::display(string s)
{	
	list<entry*>::iterator it = obList.begin();
	cout << s << "-" << "observable: " << name << " content: " << content << endl;
	string str = s + ' ';
	for (; it != obList.end(); ++it)
	{
		(*it)->display(str);
	}
}


bool observable::hasSame(entry* pe)
{
	list<entry*>::iterator it = obList.begin();
	if (this == pe)
		return true;
	for (; it != obList.end(); ++it)
	{
		if ((*it)->hasSame(pe))
			return true;
	}
	return false;
}


void observable::onUpdate(entry* pe)
{
	updateAll(pe);
}

void observable::updateAll(entry* pe)
{
	upDateEdit* edit = NULL;
	if (requireUndo())
		edit = new upDateEdit(this, pe->getContent());
	content = pe->getContent();
	list<entry*>::iterator it = obList.begin();
	for (; it != obList.end(); ++it)
	{
		(*it)->setCompoundEdit(edit);
		(*it)->onUpdate(pe);
	}
	postEdit(edit);
}

void observable::addObserver(entry* po)
{
	if (po->hasSame(this))
	{
		cout << "\nFailed! If you add Observer this way, loop will appear." << endl;
	}
	else
	{
		addObserverEdit* edit = NULL;
		if (requireUndo())
			edit = new addObserverEdit(this, po); 
		list<entry*>::iterator it = obList.begin();
		for (; it != obList.end(); ++it)
		{
			if ((*it) == po)
			{
				cout << "\nThe observer has been exsited." << endl;
				postEdit(NULL);
				return ;
			}
		}
		obList.push_back(po);
		postEdit(edit);
	}
}

bool observable::deleteObserver(entry* po)
{
	deleteObserverEdit* edit = NULL;
	if (requireUndo())
		edit = new deleteObserverEdit(this, po);
	list<entry*>::iterator it = obList.begin();
	for (; it != obList.end(); ++it)
	{
		if ((*it) == po)
		{
			obList.erase(it);
			postEdit(edit);
			return true;
		}
	}
	postEdit(NULL);
	return false;
}