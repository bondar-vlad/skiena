#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define MATRIX(n, m) vector<vector<char>>(n, vector<char>(m, '0'))
#define RANGE(container) container.begin(), container.end()

using namespace std;

void get_digits(int n, int *a) {
    a[0] = n / 100;
    a[1] = (n / 10) % 10;
    a[2] = n % 10;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        vector<int> registers(10, 0);
        vector<int> RAM(1000, 0);
        string word;
        while (word.empty())
        {
            getline(cin, word);
        }
        for (int j = 0; !word.empty(); ++j) {
            RAM[j] = stoi(word);
            getline(cin, word);
        }
        int position(0), counter(0);
        while (RAM[position] != 100) {
            int digits[3];
            get_digits(RAM[position], digits);
            position++;
            counter++;
            switch (digits[0]) {
                case 2:
                    registers[digits[1]] = digits[2];
                    break;
                case 3:
                    registers[digits[1]] += digits[2];
                    registers[digits[1]] %= 1000;
                    break;
                case 4:
                    registers[digits[1]] *= digits[2];
                    registers[digits[1]] %= 1000;
                    break;
                case 5:
                    registers[digits[1]] = registers[digits[2]];
                    break;
                case 6:
                    registers[digits[1]] += registers[digits[2]];
                    registers[digits[1]] %= 1000;
                    break;
                case 7:
                    registers[digits[1]] *= registers[digits[2]];
                    registers[digits[1]] %= 1000;
                    break;
                case 8:
                    registers[digits[1]] = RAM[registers[digits[2]]];
                    break;
                case 9:
                    RAM[registers[digits[2]]] = registers[digits[1]];
                    break;
                case 0:
                    if (registers[digits[2]] != 0)
                        position = registers[digits[1]];
                    break;
                default:
                    break;
            }
        }
        cout << counter + 1;
        if (i == n - 1) {
            cout << "\n";
        } else {
            cout << "\n\n";
        }
    }
    return 0;
}