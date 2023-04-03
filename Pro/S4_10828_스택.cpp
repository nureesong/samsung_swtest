/******************************/
// [10828] 스택 (실버4)
// - 0ms 2164KB
/******************************/

#include <iostream>
#include <unordered_map>
#include <stack>
using namespace std;

int N;
stack<int> s;
unordered_map<string,int> m = {
        {"push",0},{"pop",1},{"size",2},{"empty",3},{"top",4}
};

void Solve() {
    cin >> N;
    string query;
    for (int i = 0; i < N; i++) {
        cin >> query;
        switch (m[query]) {
            case 0:
                int num;
                cin >> num;
                s.push(num);
                break;
            case 1:
                if (s.empty()) cout << "-1\n";
                else {
                    cout << s.top() << "\n";
                    s.pop();
                }
                break;
            case 2:
                cout << s.size() << "\n";
                break;
            case 3:
                cout << (s.empty() ? 1 : 0) << "\n";
                break;
            default:
                cout << (s.empty() ? -1 : s.top()) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Solve();
}
