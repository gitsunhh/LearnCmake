#include "my_dll.h"

void DLLTEST::PrintHello()
{
	std::cout << "Hello world!" << std::endl;
}

int add(int a, int b) {
    return (a + b);
}
int multi(int a, int b){
    return (a * b);
}