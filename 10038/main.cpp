#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

#define MATRIX(n, m) vector<vector<char>>(n, vector<int>(m, '0'))
#define RANGE(container) container.begin(), container.end()

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<int> v(n);
        for_each(RANGE(v), [](int &i) { cin >> i; });
        vector<bool> mask(n, false);
        for (int j = 1; j < n; ++j) {
            try {
                mask.at(abs(v[j] - v[j - 1]) - 1) = true;
            } catch (...) {
                cout << "Not jolly\n";
                break;
            }
        }
        if (count(RANGE(mask), false))
            cout << "Not jolly\n";
        else
            cout << "Jolly\n";
    }
    return 0;
}