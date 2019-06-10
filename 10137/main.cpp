#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>

#define RANGE(container) container.begin(), container.end()

using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        vector<double> a(n);
        for_each(RANGE(a), [](double &item) { cin >> item; });
        auto avr = accumulate(RANGE(a), (double)0) / n;
        double res_pos(0.0), res_neg(0.0);
        for_each(RANGE(a), [&res_pos, &res_neg, avr](double item) {
            double diff = (double) (long) ((item - avr) * 100.0) / 100.0;
            if (diff > 0) {
                res_pos += diff;
            } else {
                res_neg += diff;
            }
        });
        double res = max(res_pos, -res_neg);
        res = (res < 0) ? -res : res;
        printf("$%.2lf\n",res);
    }
    return 0;
}