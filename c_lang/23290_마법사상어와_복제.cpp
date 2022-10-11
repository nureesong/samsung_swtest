#define _CRT_SECURE_NO_WARNINGS

/************************************/
// [23290] 마법사 상어와 복제 (골드1)
// 구현 - 0ms, 2020KB  [솔루션]
// 물고기가 최대 100만 마리이므로 한 마리씩 이동시키면 시간초과!!
// 각 위치별 같은 방향인 물고기는 한번에 이동시키기

// 복제해둔 물고기를 추가한 뒤, 다음 시뮬레이션에서 다시 물고기를 이동시킬 때
// 8방향 전부 냄새라서 못 움직이면 상어/냄새가 있는 곳에 물고기가 겹칠 수 있다.

// 상어의 이동시 방문했던 위치를 다시 방문할 수 있으나, 물고기는 중복해서 먹지 않도록 주의!
// 상어의 출발위치는 먹고 시작하면 안 된다... (몇 시간 헤맴ㅜㅜ)
/**********************************************************/

#include <iostream>
#include <cstring>
using namespace std;

int M, T;
int arr[4][4][8]; // 각 칸마다 방향별 물고기수
int cop[4][4][8]; // 복제할 공간
int cnt[4][4];    // 이동 후 해당칸 물고기 수
int smell[4][4];  // 각 칸마다 냄새 잔여시간

int vis[4][4];    // 상어 이동 시 재방문 가능하므로 방문여부가 아닌 방문횟수를 기록!
int path[3];      // 상어 이동방향 기록
int maxpath[3];   // 최대일 때의 이동방향 백업
int maxcnt;       // 상어 이동 시 최대 물고기수

int dr[] = { 0,-1,-1,-1,0,1,1,1 };
int dc[] = { -1,-1,0,1,1,1,0,-1 };

struct POS {
	int r, c;
};
POS S;    // 현재 상어 위치

void Input() {
	cin >> M >> T;
	int x, y, d;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> d;
		x--; y--; d--;
		arr[x][y][d]++;
	}
	cin >> S.r >> S.c;
	S.r--; S.c--;
}

void MoveFish() {
	memcpy(cop, arr, sizeof(arr));
	memset(arr, 0, sizeof(arr));
	memset(cnt, 0, sizeof(cnt));

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			for (int d = 0; d < 8; d++) {
				if (!cop[r][c][d]) continue;

				// 이동 가능한 방향 찾기 - 최대 8번 회전
				int i;
				for (i = 0; i < 8; i++) {
					int nd = (d - i + 8) % 8;
					int nr = r + dr[nd];
					int nc = c + dc[nd];

					if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4) continue;
					if (nr == S.r && nc == S.c) continue;
					if (smell[nr][nc]) continue;

					arr[nr][nc][nd] += cop[r][c][d];
					break;
				}
				if (i == 8) arr[r][c][d] += cop[r][c][d]; // 8방향 모두 불가능
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int d = 0; d < 8; d++) {
				cnt[i][j] += arr[i][j][d];
			}
		}
	}
}

void DFS(int n, int r, int c, int curcnt) {
	if (n == 3) {
		if (curcnt > maxcnt) {
			maxcnt = curcnt;
			memcpy(maxpath, path, 4 * 3);
		}
		return;
	}

	static int dir[4] = { 2,0,6,4 };  // 상좌하우
	for (int i = 0; i < 4; i++) {
		int d = dir[i];
		int nr = r + dr[d];
		int nc = c + dc[d];
		if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4) continue;
		
		path[n] = d;  // 이동방향 경로를 기록하자

		// 같은 위치 재방문 가능하다!! 단, 잡아먹은 물고기를 또 먹으면 안 됨!!
		int ncnt = curcnt;
		if (!vis[nr][nc]) ncnt += cnt[nr][nc];

		vis[nr][nc]++; // 방문여부가 아닌 방문횟수를 기록!
		DFS(n + 1, nr, nc, ncnt);
		vis[nr][nc]--;
	}
}

void MoveShark() {
	// 3칸 이동시 물고기를 최대로 잡아먹을 수 있는 방향 찾기
	maxcnt = -1;  // 모든 경우에서 물고기 못 잡을 때에도 상어 위치가 갱신되도록 -1로 놓기
	DFS(0, S.r, S.c, 0);

	// 잡을 수 있는 물고기가 최대인 경우로 이동하며 물고기 제거
	for (int i = 0; i < 3; i++) {
		int d = maxpath[i];
		S.r += dr[d];
		S.c += dc[d];
		if (cnt[S.r][S.c]) {
			cnt[S.r][S.c] = 0;
			memset(arr[S.r][S.c], 0, 4 * 8);
			smell[S.r][S.c] = 3;
		}
	}
}

void RemoveSmell() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (smell[i][j]) smell[i][j]--;
		}
	}
}

void AddFish() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int d = 0; d < 8; d++) {
				arr[i][j][d] += cop[i][j][d];
				cnt[i][j] += cop[i][j][d];
			}
		}
	}
}

void Simulation() {
	for (int i = 1; i <= T; i++) {
		MoveFish();    // 1~2. 물고기 복제 및 이동
		MoveShark();   // 3. 상어 이동
		RemoveSmell(); // 4. 냄새 제거
		AddFish();     // 5. 복제해둔 물고기 추가
	}
}

int CountFish() {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			sum += cnt[i][j];
		}
	}
	return sum;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Simulation();
	cout << CountFish() << "\n";
}
