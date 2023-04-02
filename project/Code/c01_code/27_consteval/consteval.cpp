consteval double inchToMm(double inch) {
    return inch * 25.4;
}

int main() {
    // stub：正常编译且在编译期求值
    constexpr double const_inch{6.0};
    constexpr double mm1{inchToMm(const_inch)};    // at compile time

    // stub：导致编译错误
    double dynamic_inch{8.0};
    double mm2{inchToMm(dynamic_inch)};  // compile-time error
}

//constexpr double inchToMm(double inch) {
//    return inch * 25.4;
//}
//
//int main() {
//    // stub：如果按照以下方式，则会在需要时在编译期对函数求值
//    constexpr double const_inch{6.0};
//    constexpr double mm1{inchToMm(const_inch)};    // at compile time
//
//    // stub：如果按照以下方式调用，函数不会在编译期求值，而是在运行时
//    double dynamic_inch{8.0};
//    double mm2{inchToMm(dynamic_inch)};
//}
//
