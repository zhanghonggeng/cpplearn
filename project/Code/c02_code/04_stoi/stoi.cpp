#include <cstddef>
#include <iostream>
#include <string>
#include <format>
#include <charconv>

using namespace std;

int main() {
    const string toParse{"   123USD"};
    size_t index{0};
    int value{stoi(toParse, &index)};
    cout << format("Parsed value: {}", value) << endl;
    cout << format("First non-parsed character: '{}'", toParse[index]) << endl;

    to_chars_result to_chars(char *first, char *last, IntegerT value, int base = 10);

}
