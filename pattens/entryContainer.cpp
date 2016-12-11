#include "stdafx.h"
#include "entryContainer.h"
#include "createEntryEdit.h"
#include "eraseEntryEdit.h"


entryContainer::entryContainer()
{
}


entryContainer::~entryContainer()
{
}

bool entryContainer::createObserver(string name, string content)
{
	createEntryEdit* edit = NULL;
	if (_container.count(name) > 0)
		return false;
	_container[name] = new observer(name, content);
	_container[name]->setUndoManager(getUndoManager());
	edit = new createEntryEdit(this, _container[name]);
	postEdit(edit);
	return true;
}

bool entryContainer::createObservable(string name, string content)
{
	createEntryEdit* edit = NULL;
	if (_container.count(name) > 0)
		return false;
	_container[name] = new observable(name, content);
	_container[name]->setUndoManager(getUndoManager());
	edit = new createEntryEdit(this, _container[name]);
	postEdit(edit);
	return true;
}


bool entryContainer::createEntry(entry* Entry)
{
	createEntryEdit* edit = NULL;
	string name = Entry->getName();
	if (_container.count(name) > 0)
		return false;
	edit = new createEntryEdit(this, Entry);
	_container[name] = Entry;
	_container[name]->setUndoManager(getUndoManager());
	postEdit(edit);
	return true;
}

bool entryContainer::eraseEntry(string name)
{
	eraseEntryEdit* edit = NULL;
	map<string, entry*>::iterator it = _container.begin();
	if (_container.count(name) == 0)
		return false;
	edit = new eraseEntryEdit(this, _container[name]);
	for (; it != _container.end(); ++it)
	{
		if ((*it).second->getType() == "observable")
		{
			(*it).second->setCompoundEdit(edit);
			((observable*)(*it).second)->deleteObserver(_container[name]);
		}
	}
	_container.erase(name);
	postEdit(edit);
	return true;
}



entry* entryContainer::find(string name)
{
	if (_container.count(name) > 0)
		return _container[name];
	else
		return NULL;
}

void entryContainer::display()
{
	cout << "The entrys stored are:" << endl;
	map<string, entry*>::iterator it = _container.begin();
	for (; it != _container.end(); ++it)
	{
		cout << (*it).second->toStirng() << endl;
	}
}