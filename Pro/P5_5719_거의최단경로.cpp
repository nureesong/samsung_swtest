/****************************************/
// [5719] 거의 최단 경로 (플래5)
// 25%에서 메모리 초과... PQ에 경로를 전부 넣은 게 문제일듯
/****************************************/

#include <iostream>
#include <vector>
#include <queue>
#define INF (0x7fffffff)
using namespace std;

int N, M, S, D;
struct EDGE {
    int n, d, flag;
};
vector<EDGE> A[500]; // Adjacency List
vector<int> dp;
vector<vector<int>> shortest_paths;

struct STATUS {
    int n, d; //string path;
    vector<int> path;
};
struct comp {
    bool operator()(STATUS &a, STATUS &b) {
        return a.d > b.d;
    }
};
priority_queue<STATUS, vector<STATUS>, comp> pq;
struct STATUS2 {
    int n, d;
};
struct comp2 {
    bool operator()(STATUS2 &a, STATUS2 &b) {
        return a.d > b.d;
    }
};
priority_queue<STATUS2, vector<STATUS2>, comp2> pq2;

void Init() {
    for (int i = 0; i < 500; i++) A[i].clear();
    dp.clear();
    shortest_paths.clear();
    pq = {}; pq2 = {};
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

void Dijkstra() {
    pq = {};
    vector<int> init_path{S};
    pq.push({S, 0, init_path});
    dp[S] = 0;

    while (!pq.empty()) {
        STATUS cur = pq.top(); pq.pop();
//        cout << "\ncur: " << cur.n << " " << cur.d << " " << cur.path << "\n";
        if (cur.n == D && cur.d == dp[cur.n]) {
//            cout << "shortest_path\n";
            shortest_paths.push_back(cur.path);
            continue;  // 현재 노드가 도착지면 더이상 상태발전X
        }

        for (auto next : A[cur.n]) {
            int nd = cur.d + next.d;
            vector<int> npath = cur.path;
            if (nd > dp[next.n]) continue;

            npath.push_back(next.n);
            pq.push({next.n, nd, npath});
            dp[next.n] = nd;
//            cout << "[push] " << e.n << " " << nd << " " << npath << "\n";
        }
    }
}

// 최단경로에 해당하는 엣지들 제거
void Remove() {
    for (auto path : shortest_paths) {
        // path = {0,3,6} / {0,1,5,6}
        for (int i = 0; i < path.size()-1; i++) {
            int src = path[i];
            int dest = path[i+1];
            for (int j = 0; j < A[src].size(); j++) {
                if (A[src][j].n == dest) {
                    A[src][j].flag = 1;
//                    cout << src << " -> " << A[src][j].n << "\n";
                }
            }
        }
//        cout << "\n";
    }
}

int Dijkstra2() {
    pq2 = {};
    pq2.push({S, 0});
    dp.clear();
    dp.resize(N, INF);
    dp[S] = 0;

    while (!pq2.empty()) {
        STATUS2 cur = pq2.top(); pq2.pop();
//        cout << "\ncur: " << cur.n << " " << cur.d << "\n";
        if (cur.n == D && cur.d == dp[cur.n]) {
            return dp[cur.n];
        }

        for (auto next : A[cur.n]) {
            if (next.flag) continue; // 제거된 엣지인지 확인
//            cout << "next: " << next.n << " " << next.flag << "\n";

            int nd = cur.d + next.d;
            if (nd >= dp[next.n]) continue;

            pq2.push({next.n, nd});
            dp[next.n] = nd;
//            cout << "[push] " << next.n << " " << nd << "\n";
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("input.txt", "r", stdin);

    while (Input()) {
        Dijkstra();
        Remove(); // 제거한 엣지는 flag = 1 표시
        cout << Dijkstra2() << "\n"; // 거의최단경로 재탐색
    }
}
