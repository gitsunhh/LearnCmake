#include <windows.h>
#include <iostream>
#include <stdlib.h>

// 静态调用DLL库-需复制dll到执行文件夹内
//#pragma comment(lib,"D:/code/cmake-dll-std/build/lib/Release/my_dll.lib") //绝对路径写法
#define LIBPATH(p, f) p##f
#pragma comment(lib, LIBPATH(__FILE__, "/../build/lib/Release/my_dll.lib")) //分隔符也可替换为//
#define IMPORT_DLL __declspec(dllimport)

IMPORT_DLL int add(int a, int b);
namespace NS
{
	class IMPORT_DLL COperation
	{
	public:
		int Add(int a, int b);
		int Sub(int a, int b);
		int Avg(int* buf,int count);
		static int i;
	};
};
namespace DLLTEST
{
	IMPORT_DLL void PrintHello();
};
IMPORT_DLL void createAlphaMat();


void StaticUse()
{
	int sum = add(10, 20);
	printf("StaticUse result: sum = %d\n", sum);
	//using namespace 
	DLLTEST::PrintHello();

	using namespace NS;
	COperation c;
	int val = COperation::i;
	int nums[] = {1, 2, 3, 4, 5};
	int avg = c.Avg(nums, 5);
	int res = c.Add(2, 3);
	std::cout << "val: " << val << " avg: " << avg << " res: " << res << std::endl;

	createAlphaMat();
}
int main()
{
	StaticUse();
	system("pause");
	return 0;
}