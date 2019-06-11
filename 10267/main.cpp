#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <array>

#define RANGE(container) container.begin(), container.end()
#define MATRIX(n, m) vector<vector<char>>(n, vector<char>(m, 'O'))

using namespace std;

class Image {
    vector<vector<char>> matrix;
    char cash_color = 'O';
public:
    void create(int m, int n) {
        matrix = MATRIX(n, m);
    }

    void clear() {
        for_each(RANGE(matrix), [](vector<char> &line) {
            fill(RANGE(line), 'O');
        });
    }

    void color(int x, int y, char c) {
        decrement({ &x, &y });
        matrix[y][x] = c;
    }

    void draw_vertical(int x, int y1, int y2, char c) {
        int_correct_order(y1, y2);
        decrement({ &x, &y1, &y2 });
        for_each(matrix.begin() + y1, matrix.begin() + y2 + 1, [x, c](vector<char> &line) {
            line[x] = c;
        });
    }

    void draw_horizontal(int x1, int x2, int y, char c) {
        int_correct_order(x1, x2);
        decrement({ &x1, &x2, &y });
        fill_n(matrix[y].begin() + x1, x2 - x1 + 1, c);
    }

    void draw_rectangle(int x1, int y1, int x2, int y2, char c) {
        int_correct_order(x1, x2);
        int_correct_order(y1, y2);
        decrement({ &x1, &x2, &y1, &y2 });
        for_each(matrix.begin() + y1, matrix.begin() + y2 + 1, [x1, x2, c](vector<char> &line) {
            fill_n(line.begin() + x1, x2 - x1 + 1, c);
        });
    }

    void fill_region(int x, int y, char c) {
        decrement({ &x, &y });
        cash_color = matrix[y][x];
        fill_around(y, x, c);
    }

    void write(const string& name) {
        cout << name << "\n";
        for_each(matrix.begin(), matrix.end(), [](vector<char> &line) {
            for_each(line.begin(), line.end(), [](const char& c) {
                cout << c;
            });
            cout << '\n';
        });
    }

private:
    void fill_around(int x, int y, char c) {
        if (matrix[x][y] != c)
        {
            matrix[x][y] = c;
            try_fill(x + 1, y, c);
            try_fill(x - 1, y, c);
            try_fill(x, y + 1, c);
            try_fill(x, y - 1, c);
        }
    }

    void try_fill(int x, int y, char c) {
        try {
            char current = matrix.at(x).at(y);
            if (current == cash_color)
                fill_around(x, y, c);
        }
        catch (...) {
            return;
        }
    }

    static void decrement(initializer_list<int*> list) {
        for_each(list.begin(), list.end(), [](int* n) {
            (*n)--;
        });
    }

    static void int_correct_order(int& first, int& second)
    {
        if (first > second) {
            swap(first, second);
        }
    }
};

int main() {
    string allowCommands("ICLVHKFSX");
    char command;
    Image image;
    int x, x1, x2, y, y1, y2;
    char c;
    while (cin >> command) {
        switch (command) {
            case 'I': {
                int m, n;
                cin >> m >> n;
                image.create(m, n);
                break;
            }
            case 'C': {
                image.clear();
                break;
            }
            case 'L': {
                cin >> x >> y >> c;
                image.color(x, y, c);
                break;
            }
            case 'V': {
                cin >> x >> y1 >> y2 >> c;
                image.draw_vertical(x, y1, y2, c);
                break;
            }
            case 'H': {
                cin >> x1 >> x2 >> y >> c;
                image.draw_horizontal(x1, x2, y, c);
                break;
            }
            case 'K': {
                cin >> x1 >> x2 >> y1 >> y2 >> c;
                image.draw_rectangle(x1, x2, y1, y2, c);
                break;
            }
            case 'F': {
                cin >> x >> y >> c;
                image.fill_region(x, y, c);
                break;
            }
            case 'S': {
                string s;
                cin >> s;
                image.write(s);
                break;
            }
            case 'X': {
                return 0;
            }
            default:
                break;
        }
    }
    return 0;
}