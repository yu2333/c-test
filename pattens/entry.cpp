#include "stdafx.h"
#include "entry.h"
#include "setContentEdit.h"


entry::entry()
{
}


entry::~entry()
{
}

void entry::setContent(string Content)
{ 
	setContentEdit* edit = NULL;
	if (requireUndo())
		edit = new setContentEdit(this, Content);
	content = Content; 
	postEdit(edit);
}