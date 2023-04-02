/*
    分配器
*/
#include <memory>

using namespace std;

class MyClass {};

int main()
{
	// Create an allocator to use.
	allocator<MyClass> alloc;

	// Allocate uninitialized memory block.
    // 分配一块内存
	auto* memory{ alloc.allocate(1) };

	// Use placement new operator to construct a MyClass in place.
    // 在特定位置上构造一个对象
	new(memory) MyClass{};

	// Destroy MyClass instance.
    // destroy_at(销毁在给定地址的对象) destroy(销毁一个范围中的对象) destroy_n(销毁范围中一定数量的对象)
	destroy_at(memory);

	// Deallocate memory block.
    // 释放内存
	alloc.deallocate(memory, 1);
	memory = nullptr;
}
