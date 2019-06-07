#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int max_iterations(int i, int j) {
    int result = 0;
    for (int k = min(i, j); k <= max(i, j); ++k) {
        int current = k;
        int counter = 1;
        while (current != 1) {
            counter++;
            if (current % 2 == 0) {
                current = current / 2;
            } else {
                current = 3 * current + 1;
            }
        }
        result = max(counter, result);
    }
    return result;
}

int main() {
    int i, j;
    while (cin >> i >> j) {
        int answer[3];
        answer[0] = i;
        answer[1] = j;
        answer[2] = max_iterations(i, j);
        printf("%d %d %d\n", answer[0], answer[1], answer[2]);
    }
    return 0;
}