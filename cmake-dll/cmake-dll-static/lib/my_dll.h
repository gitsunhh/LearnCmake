#ifndef CPP_LEARN_MY_DLL_H
#define CPP_LEARN_MY_DLL_H

#define EXPORT_DLL __declspec(dllexport)
#include <iostream>
//如果要导出C++文件中的函数，并且不让编译器改动函数名，用def文件导出函数并且在函数名前加extern "C"
EXPORT_DLL int add(int a, int b); //不加C风格dll动态调用不成功，原因暂时不明
namespace DLLTEST
{
	EXPORT_DLL void PrintHello();//extern "C"
}
namespace NS
{
 
	class EXPORT_DLL COperation
	{
	public:
		int Add(int a, int b);
		int Sub(int a, int b);
		int Avg(int* buf,int count);
		static int i;
	};
};

//opencv-test
#include <opencv2/opencv.hpp>
EXPORT_DLL void createAlphaMat();

#endif //CPP_LEARN_MY_DLL_H