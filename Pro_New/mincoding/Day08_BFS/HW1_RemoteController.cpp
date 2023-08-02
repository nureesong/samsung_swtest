#include <iostream>
#include <deque>
using namespace std;

int S, D;
int vis[100001];
struct STATUS {
    int n, d;
};
deque<STATUS> q;

int move(int num, int button) {
    switch (button) {
        case 0:
            return num >> 1;
        case 1:
            return num * 2;
        case 2:
            return num + 1;
        default:
            return num - 1;
    }
}

int BFS() {
    q.push_back({ S,0 });
    vis[S] = 1;
    while (!q.empty()) {
        STATUS cur = q.front(); q.pop_front();
        int nd = cur.d + 1;
        for (int i = 0; i < 4; i++) {
            int next = move(cur.n, i);
            if (next == D) return nd;
            if (next < 0 || next > 100000) continue;
            if (vis[next]) continue;
            q.push_back({ next,nd });
            vis[next] = 1;
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> S >> D;
    cout << BFS() << "\n";
}
