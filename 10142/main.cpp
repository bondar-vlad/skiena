#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

#define MATRIX(n, m) vector<vector<char>>(n, vector<int>(m, '0'))
#define RANGE(container) container.begin(), container.end()

using namespace std;

struct Candidate {
    bool loser;
    int votes;

    Candidate() : loser(false), votes(0) {}
};

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        vector<string> candidates(m);
        for_each(RANGE(candidates), [](string &s) { while (s.empty()) { getline(cin, s); }});
        string ballot;
        vector<queue<int>> ballots;
        while (getline(cin, ballot) && !ballot.empty()) {
            queue<int> q;
            for (int j = 0, begin = 0, end = ballot.find(' ', begin); j < m; ++j, end = ballot.find(' ', begin)) {
                int num = stoi(ballot.substr(begin, end - begin));
                begin = end + 1;
                q.push(num - 1);
            }
            ballots.push_back(q);
        }

        bool victory(false);
        vector<int> winners;
        vector<Candidate> candidate_votes(m);
        for_each(RANGE(ballots), [&candidate_votes](queue<int> &q) {
            candidate_votes[q.front()].votes++;
        });

        while (!victory) {
            for_each(RANGE(ballots), [&candidate_votes](queue<int> &q) {
                while (candidate_votes[q.front()].loser) {
                    q.pop();
                    candidate_votes[q.front()].votes++;
                }
            });
            vector<Candidate> remaining;
            for_each(RANGE(candidate_votes), [&remaining](const Candidate &c) {
                if (!c.loser) {
                    remaining.push_back(c);
                }
            });
            int max = (*max_element(
                    RANGE(remaining),
                    [](const Candidate a, const Candidate b) {
                        return a.votes < b.votes;
                    })).votes;
            int min = (*min_element(
                    RANGE(remaining),
                    [](const Candidate a, const Candidate b) {
                        return a.votes < b.votes;
                    })).votes;
            if (min == max || max > ballots.size() / 2) {
                victory = true;
            }
            winners = vector<int>(0);
            for (int j = 0; j < candidate_votes.size(); ++j) {
                if (candidate_votes[j].votes == max) {
                    winners.push_back(j);
                } else if (candidate_votes[j].votes == min) {
                    candidate_votes[j].loser = true;
                }
            }
        }
        for_each(RANGE(winners), [&candidates](int winner) {
            cout << candidates[winner] << endl;
        });
        if (i != n - 1)
            cout << endl;
    }
    return 0;
}