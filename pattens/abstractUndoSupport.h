#pragma once

#include <iostream>
#include <string>
using std::string;
using namespace std;
class abstractUndoSupport
{
public:
	abstractUndoSupport();
	virtual ~abstractUndoSupport();

	void startUpdate(){ _canUpdate = true; };
	void stopUpdate(){ _canUpdate = false; };
	bool canUpdate(){ return _canUpdate; };
protected:
	bool _canUpdate;
};
