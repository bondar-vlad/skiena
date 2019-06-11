#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>

#define RANGE(container) container.begin(), container.end() - 1

using namespace std;

int n = 0;

void draw_line_fragment(string s, bool end_space = true) {
    putchar(s[0]);
    for (int i = 0; i < n; ++i) {
        putchar(s[1]);
    }
    putchar(s[2]);
    if (end_space) putchar(' ');
}

int main() {
    string s;
    while (cin >> n >> s && n) {
        for_each(RANGE(s), [](const char &digit) {
            switch (digit) {
                case '1':
                case '4':
                    draw_line_fragment("   ");
                    break;
                default:
                    draw_line_fragment(" - ");
                    break;
            }
        });
        switch (*s.rbegin()) {
            case '1':
            case '4':
                draw_line_fragment("   ", false);
                break;
            default:
                draw_line_fragment(" - ", false);
                break;
        }
        puts("");
        for (int i = 0; i < n; ++i) {
            for_each(RANGE(s), [](const char &digit) {
                switch (digit) {
                    case '1':
                    case '2':
                    case '3':
                    case '7':
                        draw_line_fragment("  |");
                        break;
                    case '5':
                    case '6':
                        draw_line_fragment("|  ");
                        break;
                    default:
                        draw_line_fragment("| |");
                        break;
                }
            });
            switch (*s.rbegin()) {
                case '1':
                case '2':
                case '3':
                case '7':
                    draw_line_fragment("  |", false);
                    break;
                case '5':
                case '6':
                    draw_line_fragment("|  ", false);
                    break;
                default:
                    draw_line_fragment("| |", false);
                    break;
            }
            puts("");
        }
        for_each(RANGE(s), [](const char &digit) {
            switch (digit) {
                case '1':
                case '7':
                case '0':
                    draw_line_fragment("   ");
                    break;
                default:
                    draw_line_fragment(" - ");
                    break;
            }
        });
        switch (*s.rbegin()) {
            case '1':
            case '7':
            case '0':
                draw_line_fragment("   ", false);
                break;
            default:
                draw_line_fragment(" - ", false);
                break;
        }
        puts("");
        for (int i = 0; i < n; ++i) {
            for_each(RANGE(s), [](const char &digit) {
                switch (digit) {
                    case '2':
                        draw_line_fragment("|  ");
                        break;
                    case '6':
                    case '8':
                    case '0':
                        draw_line_fragment("| |");
                        break;
                    default:
                        draw_line_fragment("  |");
                        break;
                }
            });
            switch (*s.rbegin()) {
                case '2':
                    draw_line_fragment("|  ", false);
                    break;
                case '6':
                case '8':
                case '0':
                    draw_line_fragment("| |", false);
                    break;
                default:
                    draw_line_fragment("  |", false);
                    break;
            }
            puts("");
        }
        for_each(RANGE(s), [](const char &digit) {
            switch (digit) {
                case '1':
                case '4':
                case '7':
                    draw_line_fragment("   ");
                    break;
                default:
                    draw_line_fragment(" - ");
                    break;
            }
        });
        switch (*s.rbegin()) {
            case '1':
            case '4':
            case '7':
                draw_line_fragment("   ", false);
                break;
            default:
                draw_line_fragment(" - ", false);
                break;
        }
        puts("");
        puts("");
    }
    return 0;
}