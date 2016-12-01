#include "stdafx.h"
#include "observer.h"


observer::observer(string Name, string Content)
{
	name = Name;
	content = Content;
}


observer::~observer()
{
}

void observer::display()
{
	cout << "observer: " << name << " content: " << content << endl;
}

void observer::display(string s)
{
	cout << s <<"-"<< "observer: " << name << " content: " << content << endl;
}

bool observer::hasSame(entry *pe)
{
	return false;
}

void observer::onUpdate(entry* pe)
{
	content = pe->getContent();
}