/**************************************/
// [10282] 해킹 (골드4)
// - 다익스트라: 120ms 5580KB
// - long long 확인
//   최대 D개의 간선을 거쳐 s초마다 감염된다면 
//   10^5 * 10^3 = 최대 1억 초 (int 가능)
/**************************************/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, D, C;
vector<int> DP;  // 각 컴퓨터 감염까지 걸린 최소시간
struct STATUS {
    int n, t;
};
vector<STATUS> A[10000]; // Adjacency List
struct COMP {
    bool operator()(STATUS &a, STATUS &b) {
        return a.t > b.t;
    }
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;


void Input() {
    cin >> N >> D >> C;
    C--;
    for (int i = 0; i < N; i++) {
        A[i].clear();
    }
    DP.clear();
    for (int i = 0; i < D; i++) {
        int a, b, s;
        cin >> a >> b >> s;
        A[--b].push_back({--a, s});
    }
}

void Dijkstra(int start) {
    DP.resize(N, 0x7fffffff);
    DP[start] = 0;
    pq.push({start,0});

    while (!pq.empty()) {
        STATUS cur = pq.top(); pq.pop();
        for (auto next : A[cur.n]) {
            int nt = cur.t + next.t;
            if (nt < DP[next.n]) {
                DP[next.n] = nt;
                pq.push({next.n, nt});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) {
        Input();
        Dijkstra(C);

        int cnt = 0, maxt = 0;
        for (int i = 0; i < N; i++) {
            if (DP[i] == 0x7fffffff) continue;
            cnt++;
            maxt = (DP[i] > maxt) ? DP[i] : maxt;
        }
        cout << cnt << " " << maxt << "\n";
    }
    return 0;
}
