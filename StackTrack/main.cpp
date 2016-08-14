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

void func4()
{
	printf("hello\n");
}

int _tmain(int argc, TCHAR* argv[])
{
	func4();
	func3();

	return 0;
}
