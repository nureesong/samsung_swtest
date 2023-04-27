/***********************************************/
// [5719] 거의 최단 경로 (플래5)
// - 다익스트라: 36ms 2444KB
// 1. 최단경로 탐색 (여러 개 존재 가능)
// 2. 최단경로 역추적하며 엣지 제거 (인접리스트 노드번호 -1로 변경)
// 3. 남은 엣지로 다시 최단경로 탐색
// - 내가 했던 방법: PQ 상태에 이동경로 저장 -> 메모리 초과
/***********************************************/

#include <iostream>
#include <vector>
#include <queue>
#define INF (0x7fffffff)
using namespace std;

int N, M, S, D;
struct EDGE {
    int n, d;
};
vector<EDGE> A[500]; // Adjacency List
vector<int> P[500]; // 경로 역추적. prev[도착] = 출발
vector<int> dp;
struct comp {
    bool operator()(EDGE &a, EDGE &b) {
        return a.d > b.d;
    }
};
priority_queue<EDGE, vector<EDGE>, comp> pq;


void Init() {
    for (int i = 0; i < 500; i++) {
        A[i].clear();
        P[i].clear();
    }
    dp.clear();
    pq = {};
}

int Input() {
    Init();
    cin >> N >> M;
    if (N == 0) return 0;
    cin >> S >> D;
    dp.resize(N, INF);
    int u,v,p;
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> p;
        A[u].push_back({v,p});
    }
    return 1;
}

int Dijkstra() {
    pq = {};
    pq.push({S, 0});
    dp.clear();
    dp.resize(N, INF);
    dp[S] = 0;

    while (!pq.empty()) {
        EDGE cur = pq.top(); pq.pop();
        if (cur.n == D && cur.d == dp[D]) return dp[D]; // 목적지 도착. 최단경로 달성!

        for (int i = 0; i < A[cur.n].size(); i++) {
            EDGE next = A[cur.n][i];
            if (A[cur.n][i].n == -1) continue; // 제거된 엣지 확인

            int nd = cur.d + next.d;
            if (nd > dp[next.n] || nd > dp[D]) continue;
            // 가지치기: 목적지의 현재 누적거리보다 길면 상태발전X

            if (nd < dp[next.n]) {
                dp[next.n] = nd;
                pq.push({next.n, nd});
                P[next.n].clear(); // 최단경로 갱신되었으므로 모두 제거
            }
            P[next.n].push_back(cur.n); // 최단경로 추가
        }
    }
    return -1;
}

// 최단경로 역추적 (재귀)
void Remove(int dst) {
    if (dst == S) return;

    for (int src : P[dst]) {
        for (int i = 0; i < A[src].size(); i++) {
            if (A[src][i].n == dst) {
                A[src][i].n = -1; // 최단경로에 포함된 엣지 제거
                Remove(src);
                break;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("input.txt", "r", stdin);

    while (Input()) {
        Dijkstra(); // 최단경로 탐색
        Remove(D);  // 인접리스트의 노드번호를 -1로 표시하여 엣지 제거 
        cout << Dijkstra() << "\n";  // "거의 최단경로" 재탐색
    }
}
