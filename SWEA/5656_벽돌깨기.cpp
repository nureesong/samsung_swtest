/***********************************************************/
// [5656] 벽돌 깨기
// DFS - 중복순열, FloodFill & Queue
// 1) 1921ms: 가지치기 -> sol == 0이 되는 경우 찾으면 탐색 중단!
//    10:35 ~ 11:35 (1시간 소요)
// 2) 33ms: 솔루션 -> 구슬 하나 쏠 때마다 벽돌 제거, 백트래킹 시 복원
//    - 백업할 배열을 DFS 로컬 변수로 선언해야 2번 이상 백트래킹해서
//      함수 스택으로 돌아왔을 때 그 이전 상태가 저장되어 있다!!
//    - memcpy가 copy보다 조금 빠르다.
//    - 붕뜨는 공간 바닥으로 내릴 때, 큐 보다 while문 돌리는 게 훨씬 빠르다.
/************************************************************/

// 33ms - 구슬 하나 쏠 때마다 벽돌 제거, 백트래킹 할 때 복원
#if 1
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, R, C;
int arr[15 + 2][12 + 2];

int M;   // 초기 벽돌 개수
int sol; // 남은 벽돌 개수 최솟값

struct STATUS {
	int r, c;
	int n; // 벽돌에 적힌 숫자
};
queue<STATUS> q;


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
		for (int i = R - 1; i >= 0; i--) {
			if (!arr[i][j]) {
				int r = i - 1;
				while (r >= 0 && !arr[r][j]) r--;
				if (r < 0) break;
				// r행 값을 i행으로 내리기
				arr[i][j] = arr[r][j];
				arr[r][j] = 0;
			}
		}
	}
}


int FloodFill(int r, int c) {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };

	q.push({ r,c, arr[r][c] }); // 구슬 명중 위치
	arr[r][c] = 0;
	int cnt = 1;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();

		// 4방향으로 n-1칸 범위에 반응하는 벽돌 찾기
		for (int i = 0; i < 4; i++) {
			int nr = cur.r;
			int nc = cur.c;
			for (int j = 1; j < cur.n; j++) {
				nr += dr[i];
				nc += dc[i];
				if (nr < 0 || nr >= R || nc < 0 || nc >= C) break;
				if (!arr[nr][nc]) continue;

				int n = arr[nr][nc];
				if (n > 1) q.push({ nr,nc,n });
				arr[nr][nc] = 0;  // 벽돌 제거
				cnt++;
			}
		}
	}

	Arrange();  // 빈 공간 정리
	return cnt;
}


// n: 지금까지 쏜 구슬 횟수, rem: 남은 벽돌 개수
void DFS(int n, int rem) {
	// N번 쏘기 전에 모든 벽돌이 제거될 수도 있다. (n == N일 때만 갱신하면 안 됨!)
	// 모든 상태가 완성된 경우의 수라고 보고 매번 sol을 갱신한다.
	if (rem < sol) sol = rem; 
	
	if (n == N) return;

	// 현재 상태 백업
	int cop[15 + 2][12 + 2]; // 전역에 선언하면 두 번 백트래킹 했을 때 복원 안 됨
	memcpy(cop, arr, sizeof(arr));

	for (int c = 0; c < C; c++) {
		// 맨 위 벽돌 위치 찾기
		int r = 0;
		while (r < R && !arr[r][c]) r++;
		if (r == R) continue; // c열이 전부 빈칸이면 선택X

		int cnt = FloodFill(r, c); // 제거한 벽돌 개수
		DFS(n + 1, rem - cnt);

		// 복원
		memcpy(arr, cop, sizeof(cop));
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Input();
		DFS(0, M);
		cout << "#" << i << " " << sol << "\n";
	}
	return 0;
}
#endif


// 1921ms - 모든 구슬의 위치를 결정한 후, 한번에 벽돌 제거
#if 0
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
#endif
