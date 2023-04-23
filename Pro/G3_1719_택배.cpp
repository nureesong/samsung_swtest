/*****************************************************/
// [1719] 택배 (골드3)
// - 다익스트라: 380ms 10144KB
// - 주의: 노드번호가 연속적이지 않다!! (1~N번 아님)
// - PQ에 기록할 상태정보 = { 현재노드,누적시간,첫경유지,경로길이 }
//   첫 번째 경유지를 출력해야 하므로 경로길이 >= 2 확인!
/*****************************************************/

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#define INF (0x7fffffff)
using namespace std;

int N, M;
vector<int> S; // 노드번호 집합
struct EDGE {
    int n, t;
};
vector<EDGE> A[1001]; // adjacent list
int dp[1001][1001];   // 최단시간
int ans[1001][1001];  // 첫 경유지 (출력해야할 답)

struct STATUS {
    int n, t, first, len; // 노드번호, 누적이동시간, 첫 경유지, 경로길이
};
struct comp {
    bool operator()(STATUS &a, STATUS &b) {
        return a.t < b.t;
    }
};
priority_queue<STATUS, vector<STATUS>, comp> pq;

void Input() {
    set<int> s; // 등장한 집하장 번호들 저장
    cin >> N >> M;
    int a, b, t;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> t;
        A[a].push_back({b,t});
        A[b].push_back({a,t});
        s.insert(a);
        s.insert(b);
    }
    for (int n : s) S.push_back(n);
    s.clear();

    for (int i : S) {
        for (int j : S) {
            dp[i][j] = INF;
            ans[i][j] = i;
        }
    }
}

void Dijkstra(int start) {
    pq.push({start, 0, start, 1});
    dp[start][start] = 0;

    while (!pq.empty()) {
        STATUS cur = pq.top(); pq.pop();

        for (EDGE next : A[cur.n]) {
            int nn = next.n;
            int nt = cur.t + next.t;
            int nf = cur.first;
            if (nt >= dp[start][nn]) continue;

            // 최단시간 & 첫 경유지 갱신. PQ 푸쉬
            dp[start][nn] = nt;
            if (cur.len == 1) nf = nn;
            ans[start][nn] = nf;
            pq.push({nn,nt,nf,cur.len + 1});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    for (int i : S) {
        Dijkstra(i);
    }

    for (int i : S) {
        for (int j : S) {
            if (i != j) cout << ans[i][j] << " ";
            else cout << "- ";
        }
        cout << "\n";
    }
}
