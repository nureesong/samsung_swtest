#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int R, C, N;
struct NODE {
    int r, c;
};
unordered_map<int, vector<NODE>> hm;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> R >> C;
    int num;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
           cin >> num;
           hm[num].push_back({ i,j });
        }
    }
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> num;
        if (hm[num].empty()) cout << "none";
        else {
            for (NODE node : hm[num]) {
                cout << "(" << node.r << "," << node.c << ") ";
            }
        }
        cout << "\n";
    }
}
