#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
using namespace std;

int N, M;
unordered_map<string, map<int, string>> tm;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    string writer, title;
    int year;
    for (int i = 0; i < N; i++) {
        cin >> writer >> title >> year;
        auto it = tm.find(writer);
        if (it == tm.end()) {
            map<int, string> tmp;
            tmp.insert({ year,title });
            tm.insert({ writer,tmp });
        }
        else tm[writer].insert({ year,title });
    }
    string name;
    for (int i = 0; i < M; i++) {
        cin >> name;
        for (auto it = tm[name].begin(); it != tm[name].end(); it++) {
            cout << it->first << " " << it->second << "\n";
        }
    }
}
