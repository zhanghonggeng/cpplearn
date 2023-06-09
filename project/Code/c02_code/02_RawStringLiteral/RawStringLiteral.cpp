int main()
{
	//const char* str1{ "Hello "World"!" };    // Error!
    // 对于普通字符串必须转义双引号
	const char* str2{ "Hello \"World\"!" };
    // 原始字符串常量就不用转义双引号了
	const char* str3{ R"(Hello "World"!)" };

	const char* str4{ "Line 1\nLine 2" };
	const char* str5{ R"(Line 1
Line 2)" };

	const char* str6{ R"(Is the following a tab character? \t)" };

	//const char* str7{ R"(Embedded )" characters)" };    // Error!
	const char* str8{ R"-(Embedded )" characters)-" };
}
