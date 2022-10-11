/*********************************************/
// [1953] 탈주범 검거
// BFS - 8ms, 13,568KB (19분 소요)
// 파이프 모양별 뚫린 방향 체크한 룩업테이블 활용
/*********************************************/

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, M, R, C, L;
int arr[50][50];
int vis[50][50];

struct STATUS {
	int r, c, t;
};
queue<STATUS> q;

// 상하좌우 (0123)
int P[7 + 1][4] = {
	{}, {1,1,1,1}, {1,1,0,0}, {0,0,1,1},
	{1,0,0,1}, {0,1,0,1}, {0,1,1,0}, {1,0,1,0}
};
int rev[] = { 1,0,3,2 };


void Input() {
	cin >> N >> M >> R >> C >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}
}

int BFS() {
	// Init
	memset(vis, 0, sizeof(vis));
	q = {};

	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };

	q.push({ R,C,1 });
	vis[R][C] = 1;
	int cnt = 1;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();
		int p = arr[cur.r][cur.c]; // 현위치 파이프 모양
		
		if (cur.t >= L) break;
		int nt = cur.t + 1;

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
			if (vis[nr][nc]) continue;
			
			int np = arr[nr][nc]; // 인접칸 파이프 모양
			if (P[p][i] && P[np][rev[i]]) {
				q.push({ nr,nc,nt });
				vis[nr][nc] = 1;
				cnt++;
			}
		}
	}
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Input();
		cout << "#" << i << " " << BFS() << "\n";
	}
}
