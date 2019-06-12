#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define MATRIX(n, m) vector<vector<char>>(n, vector<char>(m, '0'))
#define RANGE(container) container.begin(), container.end()

using namespace std;

struct Config {
    int i;
    int j;
    char c;
};

struct FConfig {
    initializer_list<int> pieces;

    int(*fi)(int, int);

    int(*fj)(int, int);

    FConfig(initializer_list<initializer_list<int>> list) {
        auto sub_list1 = *list.begin();
        pieces = *(list.begin() + 1);

        if (*(sub_list1.begin()) == '+') {
            fi = [](int ii, int k) { return ii + k; };
        }
        else if (*(sub_list1.begin()) == '-') {
            fi = [](int ii, int k) { return ii - k; };
        }
        else {
            fi = [](int ii, int k) { return ii; };
        }

        if (*(sub_list1.begin() + 1) == '+') {
            fj = [](int ii, int k) { return ii + k; };
        }
        else if (*(sub_list1.begin() + 1) == '-') {
            fj = [](int ii, int k) { return ii - k; };
        }
        else {
            fj = [](int ii, int k) { return ii; };
        }
    }
};

bool in_check(const vector<vector<char>> &matrix, initializer_list<Config> list) {
    bool in_check = false;
    for_each(RANGE(list), [&matrix, &in_check](const Config &item) {
        try {
            if (matrix.at(item.i).at(item.j) == item.c) in_check = true;
        }
        catch (const out_of_range &) {

        }
    });
    return in_check;
}

bool in_matrix(vector<vector<char>> matrix, int i, int j) {
    try {
        matrix.at(i).at(j);
    }
    catch (const out_of_range &) {
        return false;
    }
    return true;
}

bool in_check_iterative(const vector<vector<char>> &matrix, int i, int j, initializer_list<FConfig> list) {
    bool in_check = false;
    for (auto it = list.begin(); it < list.end(); it++) {
        for (auto it1 = (*it).pieces.begin(); it1 < (*it).pieces.end(); ++it1) {
            for (int k = 1; k < 8; k++) {
                int iii = (*it).fi(i, k);
                int jjj = (*it).fj(j, k);
                if (!in_matrix(matrix, iii, jjj)) break;
                char c = matrix[iii][jjj];
                if (c == '.') {
                    continue;
                }
                if (c == *it1) {
                    in_check = true;
                }
                break;
            }
            if (in_check) {
                break;
            }
        }
        if (in_check) {
            break;
        }
    }
    return in_check;
}

int main() {
    int game_id = 0;
    while (++game_id) {
        auto matrix = MATRIX(8, 8);
        bool end_flag = true;
        for (int i = 0; i < 8; ++i) {
            string s;
            cin >> s;
            for (int j = 0; j < 8; ++j) {
                if (s[j] != '.') end_flag = false;
                matrix[i][j] = s[j];
            }
        }
        if (end_flag) break;
        bool black(false), white(false);
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (matrix[i][j] == 'k') {

                    // nearby
                    if (in_check(matrix, {
                            { i + 1, j - 1, 'P' },
                            { i + 1, j + 1, 'P' },

                            { i - 2, j - 1, 'N' },
                            { i - 2, j + 1, 'N' },
                            { i - 1, j - 2, 'N' },
                            { i - 1, j + 2, 'N' },
                            { i + 1, j - 2, 'N' },
                            { i + 1, j + 2, 'N' },
                            { i + 2, j - 1, 'N' },
                            { i + 2, j + 1, 'N' },

                            { i - 1, j - 1, 'K' },
                            { i + 1, j + 1, 'K' },
                            { i - 1, j + 1, 'K' },
                            { i + 1, j - 1, 'K' },
                            { i,     j + 1, 'K' },
                            { i,     j - 1, 'K' },
                            { i + 1, j,     'K' },
                            { i - 1, j,     'K' },
                    })) {
                        black = true;
                        break;
                    }

                    // not nearby
                    if (in_check_iterative(matrix, i, j, {
                            { { '+', '+' },{ 'B', 'Q' } },
                            { { '+', '-' },{ 'B', 'Q' } },
                            { { '-', '+' },{ 'B', 'Q' } },
                            { { '-', '-' },{ 'B', 'Q' } },
                            { { '-', '0' },{ 'R', 'Q' } },
                            { { '0', '-' },{ 'R', 'Q' } },
                            { { '+', '0' },{ 'R', 'Q' } },
                            { { '0', '+' },{ 'R', 'Q' } },
                    })) {
                        black = true;
                        break;
                    }

                }
                if (matrix[i][j] == 'K') {
                    if (in_check(matrix, {
                            { i - 1, j - 1, 'p' },
                            { i - 1, j + 1, 'p' },

                            { i - 2, j - 1, 'n' },
                            { i - 2, j + 1, 'n' },
                            { i - 1, j - 2, 'n' },
                            { i - 1, j + 2, 'n' },
                            { i + 1, j - 2, 'n' },
                            { i + 1, j + 2, 'n' },
                            { i + 2, j - 1, 'n' },
                            { i + 2, j + 1, 'n' },

                            { i - 1, j - 1, 'k' },
                            { i + 1, j + 1, 'k' },
                            { i - 1, j + 1, 'k' },
                            { i + 1, j - 1, 'k' },
                            { i,     j + 1, 'k' },
                            { i,     j - 1, 'k' },
                            { i + 1, j,     'k' },
                            { i - 1, j,     'k' },
                    })) {
                        white = true;
                        break;
                    }

                    // not nearby
                    if (in_check_iterative(matrix, i, j, {
                            { { '+', '+' },{ 'b', 'q' } },
                            { { '+', '-' },{ 'b', 'q' } },
                            { { '-', '+' },{ 'b', 'q' } },
                            { { '-', '-' },{ 'b', 'q' } },
                            { { '-', '0' },{ 'r', 'q' } },
                            { { '0', '-' },{ 'r', 'q' } },
                            { { '+', '0' },{ 'r', 'q' } },
                            { { '0', '+' },{ 'r', 'q' } },
                    })) {
                        white = true;
                        break;
                    }
                }
            }
            if (black || white) {
                break;
            }
        }
        if (black) {
            printf("Game #%d: black king is in check.\n", game_id);
        }
        else if (white) {
            printf("Game #%d: white king is in check.\n", game_id);
        }
        else {
            printf("Game #%d: no king is in check.\n", game_id);
        }

    }
    return 0;
}