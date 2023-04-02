#include <cstddef>
#include <vector>
#include <iostream>
#include <limits>
#include <format>
#include <list>
#include <forward_list>
#include <queue>
#include <stdexcept>
#include <functional>
#include <string_view>
#include <string>
#include <algorithm>
#include <span>
#include <numeric>
#include <map>
#include <execution>
#include <locale>
#include <regex>

using namespace std;

// 打印当前时间
inline double my_seconds() {
//    struct timeval tp;
//    struct timezone tzp;
//    int i = gettimeofday(&tp, &tzp);  //是获得当前的秒和微秒的时间
//    return ((double)tp.tv_sec + (double)tp.tv_usec * 1.e-6);
//    auto duration_since_epoch = system_clock::now().time_since_epoch(); // 从1970-01-01 00:00:00到当前时间点的时长
//    auto microseconds_since_epoch = duration_cast<microseconds>(duration_since_epoch).count(); // 将时长转换为微秒数
//    time_t seconds_since_epoch = static_cast<time_t>(microseconds_since_epoch / 1000000); // 将时长转换为秒数
//    std::tm current_time;
//
//    localtime_s(reinterpret_cast<tm *const>(&seconds_since_epoch), reinterpret_cast<const time_t *const>(&current_time)); // 获取当前时间（精确到秒）
//    auto tm_microsec = microseconds_since_epoch % 1000; // 当前时间的微妙数
//    auto tm_millisec = microseconds_since_epoch / 1000 % 1000; // 当前时间的毫秒数

    auto a = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    auto b = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();

    auto c = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    auto d = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    return ((double) a + (double) b * 1.e-3 + (double) c * 1.e-6 + (double) d * 1.e-9);
}

double iStart = my_seconds();
double iElaps = my_seconds() - iStart;

// Function template to populate a container of ints.
// The container must support push_back().
template<typename Container>
void populateContainer(Container &cont) {
    while (true) {
        cout << "Enter a number (0 to quit): ";
        int value;
        cin >> value;
        if (value == 0) {
            break;
        }
        cont.push_back(value);
    }
}

void removeEmptyStrings(vector<string> &strings) {
    auto it{remove_if(begin(strings), end(strings),
                      [](const string &str) { return str.empty(); })};
    // Erase the removed elements.
//    strings.erase(it, end(strings));
}

template<typename Iterator>
void DumpRange(string_view message, Iterator begin, Iterator end) {
    cout << message;
    for_each(begin, end, [](const auto &element) { cout << element << " "; });
    cout << endl;
}

int main() {
    regex r{"\\d{4}/(?:0?[1-9]|1[0-2])/(?:0?[1-9]|[1-2][0-9]|3[0-1])"};
    regex r2{"(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])"};
    regex r3{R"((\d{4})/(0?[1-9]|1[0-2])/)"};
    regex r4{R"((\d{4}))"};

//    while (true) {
//        cout << "Enter a date (year/month/day) (q=quit): ";
//        string str;
////        if (!getline(cin, str) || str == "q") {
////            break;
////        }
    string str{"2011/12/01"};
    string str2{"2011/12/01/2011/12/01"};
    cout << "-------regex_match------" << endl;
    if (regex_match(str, r)) {
        cout << "  Valid date." << endl;
    } else {
        cout << "  Invalid date!" << endl;
    }

    if (smatch m; regex_match(str, m, r2)) {
        int year{stoi(m[1])};
        int month{stoi(m[2])};
        int day{stoi(m[3])};
        cout << format("  Valid date: Year={}, month={}, day={}", year, month, day) << endl;
    } else {
        cout << "  Invalid date!" << endl;
    }
    cout << "-------regex_match------" << endl;

    cout << "-------regex_search------" << endl;
    if (smatch m; regex_search(str, m, r3)) {
        cout << format("  Found comment '{}'", m[2].str()) << endl;
        cout << m.prefix() << ' ' << m.suffix() << endl;
    } else {
        cout << "  No comment found!" << endl;
    }
    cout << "-------regex_search------" << endl;

    cout << "-------sregex_iterator------" << endl;
    const sregex_iterator end;
    for (sregex_iterator iter{cbegin(str2), cend(str2), r3}; iter != end; ++iter) {
        cout << format("\"{}\"", (*iter)[0].str()) << endl;
    }
    cout << "-------sregex_iterator------" << endl;

    cout << "-------sregex_token_iterator------" << endl;
    vector indices{2, 3};
    const sregex_token_iterator end2;
    for (sregex_token_iterator iter{cbegin(str2), cend(str2), r2, indices};
         iter != end2; ++iter) {
        cout << format("\"{}\"", iter->str()) << endl;
    }
    cout << "-------------" << endl;

    const sregex_token_iterator end3;
    for (sregex_token_iterator iter{cbegin(str2), cend(str2), r3, -1};
         iter != end3; ++iter) {
        cout << format("\"{}\"", iter->str()) << endl;
    }
    cout << "-------sregex_token_iterator------" << endl;

    cout << "-------regex_replace------" << endl;
    const string str3{"2023"};
    string result{ regex_replace(str2, r4, str3) };
    string result2{regex_replace(str2,r4,str3,regex_constants::format_no_copy)};

    cout << format("Original string: '{}'", str2) << endl;
    cout << format("New string     : '{}'", result) << endl;
    cout << format("New string_format_no_copy: '{}'", result2) << endl;

    cout << "-------regex_replace------" << endl;


//    }

}

