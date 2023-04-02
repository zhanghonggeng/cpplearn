  // helloworld.cpp

import <iostream>;

int main()
{
	std::cout << "Hello, World!" << std::endl;
	return 0;
}
// -------gcc单独编译模块-------
// gcc -std=c++2a -o <executable_name> <source1.cpp> [source2.cpp ...]
// -fmodules-ts 开启module支持

// 例如：
// gcc -std=c++2a -fmodules-ts -o hello helloworld.cpp