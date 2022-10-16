/************************************/
// [SW역량평가 1번] 캠핑
//8 4
//0 0 0 0 0 0 0 0
//0 P P 0 0 0 0 0
//0 P P 0 3 0 0 0
//0 0 0 2 0 0 0 0
//0 0 1 0 4 0 0 0
//0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0
//2 4
//3 3
//4 2
//4 4
//답: 14
/************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

int N, M;
int tent;
int arr[15][15];  // 0:공터, 1:빈 주차구역, 2:주차완료, 3:텐트
struct POS {
	int r, c;
};
POS C[30]; // camping site

struct VISITOR {
	int r, c, tent;
};
vector<VISITOR> V; // visitors 현재 위치

int dr[] = { -1,0,0,1 }; // 상좌우하
int dc[] = { 0,-1,1,0 };
int vis[15][15];
struct STATUS1 {
	int r, c, d;
	string path;
};
struct COMP1 {
	bool operator()(STATUS1 &a, STATUS1 &b) {
		if (a.d == b.d) return a.path > b.path;
		return a.d > b.d;
	}
};
priority_queue<STATUS1, vector<STATUS1>, COMP1> pq1;

struct STATUS2 {
	int r, c, d;
};
struct COMP2 {
	bool operator()(STATUS2 &a, STATUS2 &b) {
		if (a.d == b.d && a.c == b.c) return a.r > b.r;
		if (a.d == b.d) return a.c > b.c;
		return a.d > b.d;
	}
};
priority_queue<STATUS2, vector<STATUS2>, COMP2> pq2;


void Input() {
	// Init
	tent = 0;
	V.clear();

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> C[i].c >> C[i].r;
	}
}


STATUS1 FindShortest(int sr, int sc, int n) {
	memset(vis, 0, sizeof(vis));
	pq1 = {};

	pq1.push({ sr,sc,0,"" });
	vis[sr][sc] = 1;

	while (!pq1.empty()) {
		STATUS1 cur = pq1.top(); pq1.pop();
		if (cur.r == C[n].r && cur.c == C[n].c) return cur;

		int nd = cur.d + 1;
		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
			if (vis[nr][nc] || arr[nr][nc] >= 2) continue;

			string npath = cur.path + (char)(i + '0');
			pq1.push({ nr,nc,nd,npath });
			vis[nr][nc] = 1;
		}
	}
	return { -1,-1,-1,"" };
}

void MoveVisitors() {
	int sz = V.size();
	for (int i = 0; i < sz; i++) {
		if (V[i].tent) continue;

		STATUS1 ret = FindShortest(V[i].r, V[i].c, i);
		int dir = ret.path[0] - '0';
		V[i].r += dr[dir];
		V[i].c += dc[dir];
	}
}

void SetTent() {
	int sz = V.size();
	for (int i = 0; i < sz; i++) {
		if (V[i].tent) continue;

		if (V[i].r == C[i].r && V[i].c == C[i].c) {
			arr[V[i].r][V[i].c] = 3;
			V[i].tent = 1;
			tent++;
		}
	}
}

void BFS_Parking(int sr, int sc) {
	memset(vis, 0, sizeof(vis));
	pq2 = {};

	pq2.push({ sr,sc,0 });
	vis[sr][sc] = 1;

	while (!pq2.empty()) {
		STATUS2 cur = pq2.top(); pq2.pop();
		if (arr[cur.r][cur.c] == 1) {
			arr[cur.r][cur.c] = 2;
			V.push_back({ cur.r,cur.c });
			return;
		}

		int nd = cur.d + 1;
		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
			if (vis[nr][nc] || arr[nr][nc] >= 2) continue;

			pq2.push({ nr,nc,nd });
			vis[nr][nc] = 1;
		}
	}
}

int Simulation() {
	int t = 0;
	while (tent < M) {
		MoveVisitors();
		SetTent();
		if (t < M) BFS_Parking(C[t].r, C[t].c);
		t++;
	}
	return t;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Input();
		cout << "#" << i << " " << Simulation() << "\n";
	}
	return 0;
}
