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
	//由于func4在进行追踪之前栈环境已经被释放，所以这个程序不会输出func4的信息
	func4();
	func3();

	return 0;
}
