#include<cstring>
#include<cstdio>
#include <doctest/doctest.h>

int factorial(int number) {
    return number <= 1 ? number :
           factorial(number - 1) * number;
}


TEST_CASE("testing the factorial function") {
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(10) == 3628800);
}

class CMyString {
public:
    CMyString(char *pData = nullptr);

//
    CMyString(const CMyString &str);

    ~CMyString(void);

    CMyString &operator=(const CMyString &rhs);

    bool operator==(const CMyString &str) const;

    void Print();

private:
    char *m_pData;
};

/*----------------------------------
实现1 有问题
----------------------------------*/
/*
CMyString &CMyString::operator=(const CMyString &rhs) {
    // p222 防范自赋值
    if (this == &rhs)
        return *this;

    // note：delete 已有内存
    delete[] m_pData;
    m_pData = nullptr;

    auto rhsLen = strlen(rhs.m_pData) + 1;
     */
/*stub：如果抛出一个异常，new将是一个空指针
      * 解决办法：
      * 1. 先使用new分配的内存再delete原有内容
      * 2. 更好的办法是先创建一个临时示例，再交换临时示例和原来的示例
      *//*

    m_pData = new char[rhsLen];
    // std::copy函数的第二个参数应该是一个指向目标范围的迭代器
    std::copy(m_pData, m_pData + rhsLen, rhs.m_pData);
    return *this;
};

*/

/*----------------------------------
实现2
----------------------------------*/
CMyString &CMyString::operator=(const CMyString &rhs) {
    // p222 防范自赋值
    if (this != &rhs) {
        CMyString strTemp(rhs);
        char *pTemp = strTemp.m_pData;
        strTemp.m_pData = m_pData;
        m_pData = pTemp;
        return *this;
    }
    return *this;
}


CMyString::CMyString(char *pData) {
    /*stub：在构造函数里用new分配内存
     * 如果由于内存不足抛出诸如bad_alloc等异常，
     * 还没修改遇原来的状态，因此实例的状态还是有效的，
     * 也就保证了异常安全性
     */
    if (pData == nullptr) {
        m_pData = new char[1];
        m_pData[0] = '\0';
    } else {
        int length = strlen(pData);
        m_pData = new char[length + 1];
        strcpy(m_pData, pData);
    }
}

CMyString::CMyString(const CMyString &src) {
    int length = strlen(src.m_pData);
    m_pData = new char[length + 1];
    strcpy(m_pData, src.m_pData);
}

CMyString::~CMyString() {
    delete[] m_pData;
}

// ====================测试代码====================
void CMyString::Print() {
    printf("%s", m_pData);
}

bool CMyString::operator==(const CMyString &str) const {
    // 如果指针都为空，则认为字符串相等
    if (m_pData == nullptr && str.m_pData == nullptr)
        return true;

    // 如果指针都不为空，则比较字符串内容
    if (m_pData && str.m_pData)
        return strcmp(m_pData, str.m_pData) == 0;

    // 如果一个指针为空，另一个指针不为空，则字符串不相等
    return false;
}

void Test1() {
    printf("Test1 begins:\n");

    char *text = const_cast<char *>("Hello world");

    CMyString str1(text);
    CMyString str2;
    str2 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str2.Print();
    printf(".\n");
}

// 赋值给自己
void Test2() {
    printf("Test2 begins:\n");

    char *text = const_cast<char *>("Hello world");

    CMyString str1(text);
    str1 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str1.Print();
    printf(".\n");
}

// 连续赋值
void Test3() {
    printf("Test3 begins:\n");

    char *text = const_cast<char *>("Hello world");

    CMyString str1(text);
    CMyString str2, str3;
    str3 = str2 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str2.Print();
    printf(".\n");

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str3.Print();
    printf(".\n");
}


TEST_CASE("CMyString assignment operator") {
    char *text = const_cast<char *>("Hello world");
    CMyString str1(text);
    CMyString str2,str3;

    SUBCASE("TEST1") {
        str2 = str1;
        CHECK(str2 == str1);
    }
    SUBCASE("TEST2") {
        str1 = str1;
        CHECK(str1 == str1);
    }
    SUBCASE("TEST2") {
        str3 = str2 = str1;
        CHECK(str2 == str1);
        CHECK(str3 == str1);
    }
}


//    Test1();
//    Test2();
//    Test3();
//
//    return 0;
//
//}

