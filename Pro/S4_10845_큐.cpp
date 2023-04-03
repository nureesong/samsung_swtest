/************************************/
// [10845] 큐 (실버4)
// - 0ms 2164KB
// - switch문은 정수로만 분기할 수 있음.
//   HashMap을 통해 문자열 -> 정수로 변환
/************************************/

#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

int N;
queue<int> q;
unordered_map<string, int> m =
        {{"push",0},{"pop",1},{"size",2},{"empty",3},{"front",4},{"back",5}};

void Solve() {
    cin >> N;
    string query;
    for (int i = 0; i < N; i++) {
        cin >> query;

        switch (m[query]) {
            case 0:
                int num;
                cin >> num;
                q.push(num);
                break;
            case 1:
                if (q.empty()) cout << "-1\n";
                else {
                    cout << q.front() << "\n";
                    q.pop();
                }
                break;
            case 2:
                cout << q.size() << "\n";
                break;
            case 3:
                cout << (q.empty() ? 1 : 0) << "\n";
                break;
            case 4:
                cout << (q.empty() ? -1 : q.front()) << "\n";
                break;
            default:
                cout << (q.empty() ? -1 : q.back()) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("input.txt", "r", stdin);
    Solve();
}
