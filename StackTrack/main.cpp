#include "Track.h"

void func1()
{
	OPEN_STACK_TRACK;
}

void func2()
{
	func1();
}

void func3()
{
	func2();
	
}

int _tmain(int argc, TCHAR* argv[])
{
	func3();

	return 0;
}