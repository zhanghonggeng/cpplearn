#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>
#include <format>

using namespace std;

string_view extractExtension(string_view filename) {
    return filename.substr(filename.rfind('.'));
}

void handleExtension(const string &extension) { /* ... */ }

int main() {
    string s{"hello"};
    auto tmp = s + "world";
    string_view sv{tmp};
    cout << sv;

    const char *raw{"test"};
    cout << raw;
    size_t  length {2};

}
