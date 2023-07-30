#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int N, M;
map<string, int> tm;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    string word;
    int score;
    for (int i = 0; i < N; i++) {
        cin >> word >> score;
        if (tm.find(word) == tm.end()) tm.insert({ word,score });
        else tm[word] += score;
    }
    string A, B;
    for (int i = 0; i < M; i++) {
        cin >> A >> B;
        if (A > B) swap(A, B);

        auto itA = tm.lower_bound(A);
        auto itB = tm.upper_bound(B);
        int sum = 0;
        for (auto it = itA; it != itB; it++) {
            sum += it->second;
        }
        cout << sum << "\n";
    }
}
