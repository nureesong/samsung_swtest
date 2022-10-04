/************************************/
// [5656] 벽돌 깨기
// DFS - 중복순열, FloodFill & Queue
// 1921ms, 13560KB
// 시간초과 해결 -> sol == 0이 되면 더이상 진행할 필요없이 중단!
// 10:35 ~ 11:35 (1시간)
/************************************/

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int N, R, C;
int arr[15 + 2][12 + 2];
int cop[15 + 2][12 + 2];
int vis[15 + 2][12 + 2];
int pick[4];

int M;   // 초기 벽돌 개수
int rem; // 각 시뮬레이션 마다 남은 벽돌 개수
int sol; // 남은 벽돌 개수 최솟값

struct STATUS {
	int r, c;
};
queue<STATUS> q;
queue<int> a;


void Input() {
	M = 0;
	sol = 0x7fffffff;
	
	cin >> N >> C >> R;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> arr[i][j];
			if (arr[i][j]) M++;
		}
	}
}


void Arrange() {
	for (int j = 0; j < C; j++) {
		a = {};

		for (int i = R - 1; i >= 0; i--) {
			if (cop[i][j]) {
				a.push(cop[i][j]);
				cop[i][j] = 0;
			}
		}

		int sz = a.size();
		int r = R - 1;
		for (int i = 0; i < sz; i++) {
			cop[r--][j] = a.front(); a.pop();
		}
	}
}


void FloodFill(int c) {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };
	fill(&vis[0][0], &vis[R - 1][C], 0);
	q = {};

	int r = 0;
	while (r < R && !cop[r][c]) r++;
	if (r == R) return; // c열은 전부 빈칸

	q.push({ r,c }); // 구슬 명중 위치
	vis[r][c] = 1;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();
		int n = cop[cur.r][cur.c]; // 벽돌에 적힌 숫자

		// 4방향으로 n-1칸 범위에 반응하는 벽돌 찾기
		for (int i = 0; i < 4; i++) {
			int nr = cur.r;
			int nc = cur.c;
			for (int j = 1; j < n; j++) {
				nr += dr[i];
				nc += dc[i];
				if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
				if (!cop[nr][nc] || vis[nr][nc]) continue;

				q.push({ nr,nc });
				vis[nr][nc] = 1;
			}
		}

		// 현재 벽돌은 반응하는 범위 다 살펴봤으니까 제거
		cop[cur.r][cur.c] = 0;
		rem--;
	}

	// 빈 공간 벽돌 정리
	Arrange();
}


int DFS(int n) {
	// 가지치기
	if (sol == 0) return 1;

	if (n == N) {
		// 벽돌 제거 시뮬레이션
		copy(&arr[0][0], &arr[R - 1][C], &cop[0][0]);
		rem = M;
		for (int i = 0; i < N; i++) {
			FloodFill(pick[i]);
		}

		sol = (rem < sol) ? rem : sol;
		if (sol == 0) return 1;
		return 0;
	}

	for (int i = 0; i < C; i++) {
		pick[n] = i;
		if (DFS(n + 1)) return 1;
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Input();
		DFS(0);
		cout << "#" << i << " " << sol << "\n";
	}
	return 0;
}
