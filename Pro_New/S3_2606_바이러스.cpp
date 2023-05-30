/****************************************/
// [2606] 바이러스 (실버3)
// - DFS: 0ms, 1232KB
// - BFS: 0ms, 1232KB
// - Linked List:
/****************************************/


// BFS
#if 0
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

int N, E;
vector<int> A[101];
queue<int> q;
int vis[101];

int bfs(int start) {
    q.push(start);
    vis[start] = 1;
    int cnt = 0;

    while (!q.empty()) {
        int cur = q.front(); q.pop();

        for (int next : A[cur]) {
            if (vis[next]) continue;
            vis[next] = 1;
            cnt++;
            q.push(next);
        }
    }
    return cnt;
}

int main() {
    scanf("%d %d", &N, &E);
    for (int i = 0; i < E; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        A[a].push_back(b);
        A[b].push_back(a);
    }
    printf("%d\n", bfs(1));
}
#endif


// DFS
#if 0
#include <stdio.h>
#include <vector>
using namespace std;

int N, E;
vector<int> A[101];
int vis[101];
int cnt;

void dfs(int cur) {
    for (int nbd : A[cur]) {
        if (vis[nbd]) continue;
        vis[nbd] = 1;
        cnt++;
        dfs(nbd);
    }
}

int main() {
    scanf("%d %d", &N, &E);
    for (int i = 0; i < E; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        A[a].push_back(b);
        A[b].push_back(a);
    }

    vis[1] = 1;
    dfs(1);
    printf("%d\n", cnt);
}
#endif
