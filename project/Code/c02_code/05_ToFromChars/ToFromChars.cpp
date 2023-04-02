#include <cstddef>
#include <charconv>
#include <iostream>

using namespace std;

int main() {
    const size_t BufferSize{50};

    {
        string out(BufferSize, ' '); // 初始化成50个空格
        auto result{to_chars(out.data(), out.data() + out.size(), 12345)};
        if (result.ec == errc{}) { cout << out << endl; /* Conversion successful. */ }

    }

    {
        // to_chars() with structured binding.
        string out(BufferSize, ' '); // A string of BufferSize space characters.
        auto [ptr, error] {to_chars(out.data(), out.data() + out.size(), 12345)};
        if (error == errc{}) { cout << out << endl; /* Conversion successful. */ }
    }

    {
        // Demonstrating perfect round-tripping.
        double value1{1.49012e-09};
        string out(BufferSize, ' '); // A string of BufferSize space characters.
        auto [ptr1, error1] {to_chars(out.data(), out.data() + out.size(), value1)};
        if (error1 == errc{}) { cout << out << endl; /* Conversion successful. */ }


        float value2;
        auto [ptr2, error2] {from_chars(out.data(), out.data() + out.size(), value2,
                                        chars_format::fixed)};
        cout << out << value2 << endl;

        if (error2 == errc{}) {
            if (value1 == value2) {
                cout << "Perfect roundtrip" << endl;
            } else {
                cout << "No perfect roundtrip?!?" << endl;
            }
        }
    }
}

from_chars_result from_chars(const char *const _First,
                             const char *const _Last, float &_Value) {}
