#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int N, A, B;
vector<pair<int,int>> adj[100001];
struct STATUS {
	int n, d, m; // 위치, 이동거리, 가중치 최댓값
};
deque<STATUS> q;
int vis[100001];

STATUS BFS() {
	q.push_back({ A,0,0 });
	vis[A] = 1;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop_front();
		for (pair<int,int> next : adj[cur.n]) {
			int nn = next.first;
			if (vis[nn]) continue;
			int nd = cur.d + next.second;
			vis[nn] = 1;
			int maxd = cur.m > next.second ? cur.m : next.second;
			if (next.first == B) return { B,nd,maxd };
			q.push_back({ next.first,nd,maxd });
		}
	}
	return { -1,-1,-1 };
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> A >> B;
	int a, b, d;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b >> d;
		adj[a].push_back({ b,d });
		adj[b].push_back({ a,d });
	}

	STATUS ret = BFS();
	cout << ret.d - ret.m << "\n";
}
