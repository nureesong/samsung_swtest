#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N, M, X;
struct STATUS {
    int n, t;
};
struct COMP {
    bool operator()(STATUS &a, STATUS &b) {
        return a.t > b.t;
    }
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;
vector<STATUS> A[1000];

void Input() {
    cin >> N >> M >> X;
    X--;
    int a, b, ti;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> ti;
        a--; b--;
        A[a].push_back({b,ti});
    }
}

vector<int> Dijkstra(int start) {
    vector<int> dp(N, 0x7fffffff);
    dp[start] = 0;
    pq.push({start,0});
    
    while (!pq.empty()) {
        STATUS cur = pq.top(); pq.pop();
        
        for (auto next : A[cur.n])  {
            int nt = cur.t + next.t;
            if (nt < dp[next.n]) {
                dp[next.n] = nt;
                pq.push({next.n,nt});
            }
        }
    }
    return dp;
}

int Solve() {
    // 각 노드 -> X번 노드로 가는 최단시간
    int mint[N] = {0,};
    for (int i = 0; i < N; i++) {
        if (i == X) continue;
        vector<int> v = Dijkstra(i);
        mint[i] = v[X];
    }
    
    // X번 노드 -> 각자 집으로 돌아가는 것도 누적!
    vector<int> v = Dijkstra(X);
    int maxt = 0;
    for (int i = 0; i < N; i++) {
        mint[i] += v[i];
        if (mint[i] > maxt) {
            maxt = mint[i];
        }
    }
    return maxt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    Input();
    cout << Solve() << "\n";
    return 0;
}
