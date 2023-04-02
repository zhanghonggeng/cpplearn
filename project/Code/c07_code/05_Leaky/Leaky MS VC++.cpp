// 启用内存泄漏检测功能
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
// 重新定义new运算符
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

class Simple
{
public:
    Simple() { m_intPtr = new int{}; }
    ~Simple() { delete m_intPtr; }

    void setValue(int value) { *m_intPtr = value; }

private:
    int* m_intPtr;
};

void doSomething(Simple*& outSimplePtr)
{
    outSimplePtr = new Simple{}; // BUG! Doesn't delete the original.
}

int main()
{
    // 需要在main函数的第一行添加下面代码
    // 这段代码告诉Visual C++（C运行时）库，在应用程序退出时，将所有检测到的内存泄露写入调式输出控制台
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Simple* simplePtr{ new Simple{} }; // Allocate a Simple object.

    doSomething(simplePtr);

    delete simplePtr; // Only cleans up the second object.
}

//Detected memory leaks!
//Dumping objects ->
//E:\github\c++\clion_porjtct\C++20\Code\c07_code\05_Leaky\Leaky MS VC++.cpp(16) : {92} normal block at 0x000001E5431C73D0, 4 bytes long.
//Data : < > 00 00 00 00
//E : \github\c++\clion_porjtct\C++20\Code\c07_code\05_Leaky\Leaky MS VC++.cpp(36) : {91} normal block at 0x000001E5431D2950, 8 bytes long.
//Data : < s C    > D0 73 1C 43 E5 01 00 00
//Object dump complete.