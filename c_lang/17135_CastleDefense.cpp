/**********************************************/
// [17135] 캐슬 디펜스 (골드3)
// DFS(조합) + BFS - 8ms, 2032KB
// 적을 한칸씩 이동시키다가 덮어쓰면서 틀렸다.
// 궁수를 전진시키는 방법으로 바꾸니 통과!
// 적을 탐색할 때 BFS보다 for문 돌리는 게 빠를듯!
/*********************************************/

#include <iostream>
#include <cstring>
#include <queue>
#include <unordered_set>
using namespace std;

int N, M, D;
int arr[15 + 1][15];
int cop[15 + 1][15];
int total;
int pick[3]; // 궁수 3명이 공격 가능한 적의 번호
int sol;     // 궁수 공격으로 제거된 적의 최대수
struct POS { int r, c; };

struct STATUS {
	int r, c, d;
};
struct COMP {
	bool operator()(STATUS &a, STATUS &b) {
		if (a.d == b.d) return a.c > b.c;
		return a.d > b.d;
	}
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;


void Input() {
	cin >> N >> M >> D;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> arr[r][c];
			if (arr[r][c]) total++;
		}
	}
}

int BFS(int sr, int sc) {
	static int dr[] = { 0,-1,0 }; // 좌상우
	static int dc[] = { -1,0,1 };
	int vis[16][15] = { 0, };
	pq = {};

	pq.push({ sr,sc,0 });
	vis[sr][sc] = 1;

	while (!pq.empty()) {
		STATUS cur = pq.top(); pq.pop();

		if (cur.d > D) return -1;
		if (cop[cur.r][cur.c]) return cur.r * 100 + cur.c; 

		int nd = cur.d + 1;
		for (int d = 0; d < 3; d++) {
			int nr = cur.r + dr[d];
			int nc = cur.c + dc[d];
			if (nr < 0 || nr >= sr || nc < 0 || nc >= M) continue;
			if (vis[nr][nc]) continue;

			pq.push({ nr,nc,nd });
			vis[nr][nc] = 1;
		}
	}
	return -1;
}

int Simulation() {
	memcpy(cop, arr, sizeof(arr));
	int row = N; // 현재 궁수(성)가 위치하는 행
	int cnt = 0; // 궁수 공격으로 제거한 적의 수
	int enemy = total; // 남아있는 적의 수

	while (enemy) {
    // 모든 궁수 동시에 공격 가능한 적 탐색 
    // 중복 가능하므로 적의 위치를 정수로 맵핑 set에 담기
		unordered_set<int> rem;
		for (int i = 0; i < 3; i++) {
			int ret = BFS(row, pick[i]);
			if (ret != -1) rem.insert(ret);
		}

		// 거리 내에 공격 가능한 적 제거
		for (int p : rem) {
			cop[p / 100][p % 100] = 0;
			cnt++; enemy--;
		}

		// 궁수 한 칸 전진
		row--;
		if (row == 0) break;

		// 성에 도달한 적은 소멸
		for (int c = 0; c < M; c++) {
			if (cop[row][c]) {
				cop[row][c] = 0;
				enemy--;
			}
		}
	}
	return cnt;
}

void DFS(int n, int s) {
	if (n == 3) {
		int curcnt = Simulation();
		sol = (curcnt > sol) ? curcnt : sol;
		return;
	}

	for (int c = s; c < M; c++) {
		pick[n] = c;
		DFS(n + 1, c + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	DFS(0, 0);
	cout << sol << "\n";
}
