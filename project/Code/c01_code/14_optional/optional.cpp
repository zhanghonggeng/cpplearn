#include <optional>
#include <iostream>

using namespace std;

// 返回optional函数
// 保留特定类型的值，或者不包含任何值
optional<int> getData(bool giveIt)
{
    if (giveIt) {
        return 42;
    }
    return nullopt;  // or simply return {};
}

int main()
{
    optional<int> data1{ getData(true) };
    optional<int> data2{ getData(false) };

    // 判断一个optional是否有值
    cout << "data1.has_value = " << data1.has_value() << endl;
    if (data2) {
        cout << "data2 has a value." << endl;
    }

    // 如果有值，访问；没有值访问时会抛出一个bad_optional_access的异常
    cout << "data1.value = " << data1.value() << endl;
    cout << "data1.value = " << *data1 << endl;

    try {
        cout << "data2.value = " << data2.value() << endl;
    } catch (const bad_optional_access& ex) {
        cout << "Exception: " << ex.what() << endl;
    }

    // 返回optional的值，如果optional为空，则返回指定的值
    cout << "data2.value = " << data2.value_or(0) << endl;
}
