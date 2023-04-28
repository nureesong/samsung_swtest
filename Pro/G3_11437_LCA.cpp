/***********************************************/
// [11437] LCA (골드3)
// Lowest Common Ancestor (LCA): 최소 공통 조상
// - 28ms 10396KB (솔루션 )
/***********************************************/

#include <iostream>
#include <vector>
#include <cmath>
#define K ((int)floor(log2(50001)))
using namespace std;

int N, M;
vector<int> graph[50001];
int depth[50001];
int ac[50001][16]; // i의 2^j 번째 조상

struct query {
    int a, b;
}Q[10000];

void Input() {
    cin >> N;
    int a, b;
    for (int i = 1; i < N; i++) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> Q[i].a >> Q[i].b;
    }
}

void MakeTree(int cur, int par) {
    depth[cur] = depth[par] + 1;

    ac[cur][0] = par; // 2^0번째 조상 = 부모노드
    for (int k = 1; k <= K; k++) {
        int tmp = ac[cur][k-1]; // 2^(k-1)번째 조상
        ac[cur][k] = ac[tmp][k-1];
    }

    // DFS
    for (int nbd : graph[cur]) {
        if (nbd == par) continue;
        MakeTree(nbd, cur);
    }
}

int LCA(int a, int b) {
    if (depth[a] > depth[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    for (int k = K; k >= 0; k--) {
        if (depth[b] - depth[a] >= (1 << k)) b = ac[b][k];
    }
    if (a == b) return a;

    for (int k = K; k >= 0; k--) {
        if (ac[a][k] != ac[b][k]) {
            a = ac[a][k];
            b = ac[b][k];
        }
    }
    return ac[a][0];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    depth[0] = -1;
    MakeTree(1, 0);

    for (int i = 0; i < M; i++) {
        cout << LCA(Q[i].a, Q[i].b) << "\n";
    }
}
