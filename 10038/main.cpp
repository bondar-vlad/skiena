#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>

#define MATRIX(n, m) vector<vector<char>>(n, vector<int>(m, '0'))
#define RANGE(container) container.begin(), container.end()

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        if (n == 1) {
            int trash;
            cin >> trash;
            cout << "Jolly\n";
            continue;
        }
        vector<int> v(n);
        for_each(v.begin(), v.end(), [](int &i) { cin >> i; });
        int max = 0;
        int min = 2147483647;
        int sum = 0;
        bool jolly = true;
        set<int> s;
        for (int i = 1; i < n; ++i) {
            int d = abs(v[i] - v[i - 1]);
            if (s.count(d) || d < 1 || d > n - 1) {
                jolly = false;
                break;
            }
            sum += d;
            min = (d < min) ? d : min;
            max = (d > max) ? d : max;
        }
        if (jolly && min == 1 && max == n - 1 && sum == n * (n - 1) / 2) {
            cout << "Jolly\n";
        } else {
            cout << "Not jolly\n";
        }
    }
    return 0;
}