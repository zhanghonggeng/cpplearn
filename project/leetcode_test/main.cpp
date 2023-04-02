#include <vector>
#include <iostream>
#include <map>

using namespace std;

class Solution {
public:
    int findRepeatNumber(vector<int> &nums) {
        map<int, int> test;
        for (const auto &i: nums) {
            if (test.find(i) == test.end())
               test[i]=1;
            else
                ++test.at(i);
        }

        for (const auto &[key, value]: test) {
            cout << key << " " << value << endl;
            if (value >= 2)
                return key;
        }
        return 0;
    }
};

int main() {
    vector<int> test{2, 3, 1, 0, 2, 5, 3};
    Solution s;
    s.findRepeatNumber(test);
}