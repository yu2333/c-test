#pragma once
#include "entry.h"
#include "observer.h"
#include <list>
using std::list;

using namespace std;

class observable :
	public entry
{
public:
	observable(string Name,string Content);
	~observable();

	void addObserver(entry* po);
	void deleteObserver(entry* po);
	void updateAll(entry* pe);

	virtual bool hasSame(entry *pe);
	virtual void onUpdate(entry* pe);
	virtual void display();
	virtual void display(string s);		
protected:
	
	list<entry*> obList;
};

