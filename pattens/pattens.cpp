// pattens.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "observable.h"
#include "observer.h"
#include <iostream>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	observable o1("1", "c1"); 
	observable o2("2", "c2");
	observer o11("11", "c11");
	observer o21("21", "c21");

	o1.addObserver(&o2);
	o1.addObserver(&o11);
	o2.addObserver(&o21);
	o2.addObserver(&o11);
	o2.updateAll(&o2);
	o1.display();
	system("pause");
	return 0;
}

