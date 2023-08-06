#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <string>
using namespace std;

unordered_map<int, vector<string>> R; // <ID, 본인이 추천한 사람 목록>
unordered_map<string, set<int>> W; // <name, 본인을 추천한 사람 목록>

int Recommend(int id, string name) {
    R[id].push_back(name);
    W[name].insert(id);
    return R[id].size();
}

void Print(int id) {
    if (R[id].empty()) cout << "none\n";
    else {
        for (string name : R[id]) cout << name << " ";
        cout << "\n";
    }
}

void WhoIs(string name) {
    if (W[name].empty()) cout << "none\n";
    else {
        for (int id : W[name]) cout << id << " ";
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N;
    cin >> N;
    while (N--) {
        string cmd;
        cin >> cmd;
        if (cmd == "recommand") {
            int id; string name;
            cin >> id >> name;
            cout << Recommend(id, name) << "\n";
        }
        else if (cmd == "print") {
            int id;
            cin >> id;
            Print(id);
        }
        else {
            string name;
            cin >> name;
            WhoIs(name);
        }
    }
}
