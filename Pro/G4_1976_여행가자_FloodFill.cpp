/**************************************************/
// [1976] 여행가자 (골드4)
// - 유니온파인드(재귀) 0ms 2316KB
// - FloodFill(BFS) 0ms 2324KB -> 인접행렬로 하면 4ms
/**************************************************/

#include <iostream>
#include <set>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int A[200][200];  // Adjacency matrix (symmetric)
vector<int> adj[200]; // Adjacency list
int chk[200]; // group 번호 마킹
vector<int> v; // Journey plan

void Input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
            if (A[i][j]) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    set<int> s; // Journey plan (오름차순 정렬)
    int x;
    for (int i = 0; i < M; i++) {
        cin >> x;
        s.insert(--x);
    }
    for (int n : s) {
        v.push_back(n);
    }
}

void BFS(int start, int group) {
    queue<int> q;
    q.push(start);
    chk[start] = group;

    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int nn : adj[cur]) {
            if (chk[nn]) continue;
            q.push(nn);
            chk[nn] = group;
        }
    }
}

void FloodFill() {
    int group = 1;
    for (int i = 0; i < N; i++) {
        if (chk[i]) continue;
        BFS(i, group++);
    }
}

void Solve() {
    int sz = v.size() - 1;
    for (int i = 0; i < sz; i++) {
        if (chk[v[i]] != chk[v[i+1]]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    FloodFill();
    Solve();
}
