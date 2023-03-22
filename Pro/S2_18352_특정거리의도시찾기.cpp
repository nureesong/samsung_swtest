/****************************************/
// [18352] 특정 거리의 도시 찾기 (실버2)
// - 다익스트라 O(ElogV) => O(MlogN)
// - PQ(STATUS, COMP)  : 400ms 22920KB
// - PQ(pair<int,int>) : 416ms 22920KB
/****************************************/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M, K, X;         // N <= 30만, M <= 100만
vector<int> A[300000];  // Adjacency list
vector<int> dist;       // Optimal distnaces

struct STATUS {
    int n, d; // node, distance(누적거리) from start node
};
struct COMP {
    bool operator()(STATUS &a, STATUS &b) {
        return a.d > b.d;
    }
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;


void Input() {
    cin >> N >> M >> K >> X;
    X--;
    for (int i = 0; i < M; i++) {
        int from, to;
        cin >> from >> to;
        A[--from].push_back(--to);
    }
}

void Dijkstra(int src) {
    // Initialize
    dist.resize(N, 0x7fffffff);
    dist[src] = 0;
    pq.push({src,dist[src]});
    
    while (!pq.empty()) {
        STATUS cur = pq.top(); pq.pop();
        
        for (int nn : A[cur.n]) {
            int nd = cur.d + 1;
            if (nd < dist[nn]) {
                dist[nn] = nd;
                pq.push({nn,nd});
            }
        }
    }
}

void PrintAnswer() {
    bool flag = false;
    for (int i = 0; i < N; i++) {
        if (dist[i] == K) {
            cout << i+1 << "\n";
            flag = true;
        }
    }
    if (!flag) cout << -1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    Input();
    Dijkstra(X);
    PrintAnswer();
    return 0;
}


/*************************  PQ(pair<int,int>)  **********************/
priority_queue<pair<int,int>> pq;  // distance, node
// 내림차순 정렬이 기본이므로 -거리 로 담아야 함!

void Dijkstra_pair(int src) {
    // Initialize
    dist.resize(N, 0x7fffffff);
    dist[src] = 0;
    pq.push({dist[src],src});
    
    while (!pq.empty()) {
        pair<int,int> cur = pq.top(); pq.pop();
        
        for (int nn : A[cur.second]) {
            int nd = -cur.first + 1; // 음수 주의!!
            if (nd < dist[nn]) {
                dist[nn] = nd;
                pq.push({-nd,nn});
            }
        }
    }
}
/************************************************************************/

