#include <iostream>
#include <string>
#include <vector>

#define MATRIX(n, m) vector<vector<char>>(n, vector<char>(m, '0'))

using namespace std;

int main() {
    int n, m, x(0);
    while (cin >> n >> m) {
        if (n == 0 || m == 0)
        {
            return 0;
        }
        if(x++) cout << '\n';
        getchar();
        auto matrix = MATRIX(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                char c = getchar();
                if (c == '*') {
                    matrix[i][j] = c;
                    for (int k = -1; k <= 1; ++k) {
                        for (int l = -1; l <= 1; ++l) {
                            try {
                                if (matrix.at(i + k).at(j + l) != '*')
                                    matrix.at(i + k).at(j + l)++;
                            }
                            catch (const out_of_range &) {/*do nothing*/}
                        }
                    }
                }
            }
            getchar();
        }
        printf("Field #%d:\n", x);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << matrix[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}