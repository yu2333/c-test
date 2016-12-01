#include "stdafx.h"
#include "observable.h"


observable::observable(string Name, string Content)
{
	name = Name;
	content = Content;
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
	content = pe->getContent();
	list<entry*>::iterator it = obList.begin();
	for (; it != obList.end(); ++it)
	{
		(*it)->onUpdate(pe);
	}
}

void observable::addObserver(entry* po)
{
	if (po->hasSame(this))
	{
		cout << "\nFailed! If you add Observer this way, loop will appear." << endl;
	}
	else
	{
		obList.push_back(po);
	}
}

void observable::deleteObserver(entry* po)
{
	list<entry*>::iterator it = obList.begin();
	for (; it != obList.end(); ++it)
	{
		if ((*it) == po)
		{
			obList.erase(it);
			return;
		}
	}
}