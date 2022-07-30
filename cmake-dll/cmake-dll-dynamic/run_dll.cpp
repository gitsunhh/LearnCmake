#include <windows.h>
#include <iostream>
#include <stdlib.h>

// 动态调用DLL库
int DynamicUse_v1(const char* dll_path)
{
    HINSTANCE handle = LoadLibrary(dll_path);
    typedef int (*add)(int, int);// 定义函数指针类型
    auto f = (add) GetProcAddress(handle, "add");
    int result = f(100, 32);
    std::cout << "DynamicUse_v1 result: sum = " << result << std::endl;

	typedef void (*PrintHello)();
	auto DLLTEST_PrintHello = (PrintHello) GetProcAddress(handle, "PrintHello");//调用无视命名空间
	DLLTEST_PrintHello();

	typedef int (*multi)(int , int);
	auto m = (multi) GetProcAddress(handle, "multi");
    std::cout << "DynamicUse_v1 result: product = " << m(100, 32) << std::endl;
    FreeLibrary(handle);
    return 0;
}

int DynamicUse_v2(const char* dll_path){
	HMODULE module = LoadLibrary(dll_path);
	if (module == NULL)
	{
		printf("DLL loading failed\n");
		return -1;
	}
	typedef int(*AddFunc)(int, int); 
	AddFunc add;
	add = (AddFunc)GetProcAddress(module, "add");

	int sum = add(100, 200);
	printf("DynamicUse_v2 result: sum = %d\n", sum);


	FreeLibrary(module);
    return 0;
}
int main()
{
    const char* dll_path = "../lib_out/Release/my_dll.dll";
	//const char* dll_path = "./my_dll.dll";
    DynamicUse_v1(dll_path);
    DynamicUse_v2(dll_path);
	//StaticUse();
    system("pause");
	return 0;
}