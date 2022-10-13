/**************************************/
// [21609] 상어중학교 (골드2)
// 구현 - 0ms, 2028KB (1시간 36분 소요)
/**************************************/
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int N, M;
int arr[20][20]; // -1: 검정, 1~5: 일반, 7: 무지개, 0: 빈칸
int vis[20][20];
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

struct GROUP {
	int cnt, cnt_rb;
};

struct POS {
	int r, c;
};
POS maxP; // 크기가 가장 큰 그룹의 기준블록
queue<POS> q;


void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 0) arr[i][j] = 7;
		}
	}
}

GROUP FloodFill(int sr, int sc) {
	int tar = arr[sr][sc];
	q.push({ sr,sc });
	vis[sr][sc] = 1;
	int cnt = 1;
	vector<POS> rainbow;

	while (!q.empty()) {
		POS cur = q.front(); q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
			if (vis[nr][nc]) continue;
			if (arr[nr][nc] <= 0) continue; // 빈칸/검은색
			if (arr[nr][nc] < 7 && arr[nr][nc] != tar) continue; // 다른 숫자 일반블록

			q.push({ nr,nc });
			vis[nr][nc] = 1;
			cnt++;
			if (arr[nr][nc] == 7) rainbow.push_back({ nr,nc });
		}
	}

	// 방문한 rainbow 복원
	for (POS p : rainbow) {
		vis[p.r][p.c] = 0;
	}

	if (cnt == 1) return { 0,0 };
	return { cnt, (int)rainbow.size() };
}

int FindGroup() {
	memset(vis, 0, sizeof(vis));
	int maxcnt = 0, maxcnt_rb = -1, maxsr, maxsc;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (arr[i][j] <= 0 || arr[i][j] == 7) continue;
			if (vis[i][j]) continue;

			// 일반블록을 기준블록으로 놓고 그룹찾기
			GROUP ret = FloodFill(i, j);
			if (ret.cnt == 0) continue;

			if ((ret.cnt > maxcnt) ||
				(ret.cnt == maxcnt && ret.cnt_rb > maxcnt_rb) ||
				(ret.cnt == maxcnt && ret.cnt_rb == maxcnt_rb && i > maxsr) ||
				(ret.cnt == maxcnt && ret.cnt_rb == maxcnt_rb && i == maxsr && j > maxsc)) {

				maxcnt = ret.cnt;
				maxcnt_rb = ret.cnt_rb;
				maxsr = i;
				maxsc = j;
			}
		}
	}

	// 그룹이 하나라도 존재하면 maxcnt >= 2 로 갱신된다.
	// 그룹이 존재하지 않으면,  maxcnt = 0 (-1,7 밖에 없는 상황 등)
	if (maxcnt > 0) maxP = { maxsr, maxsc };
	
	return maxcnt;
}

void Remove() {
	int tar = arr[maxP.r][maxP.c];
	q.push({ maxP.r,maxP.c });
	arr[maxP.r][maxP.c] = 0;

	while (!q.empty()) {
		POS cur = q.front(); q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
			
			if (arr[nr][nc] == 7 || arr[nr][nc] == tar) { // 같은숫자, 무지개 블록
				q.push({ nr,nc });
				arr[nr][nc] = 0;
			}
		}
	}
}

void Gravity() {
	// 컬럼별로 밑으로 끌어내리기 (검은색 블록 제외!!)
	for (int j = 0; j < N; j++) {
		for (int i = N - 1; i >= 0; i--) {
			if (arr[i][j]) continue;

			int r = i;
			while (r >= 0 && arr[r][j] == 0) r--;
			// while문 종료 시, r = -1 이거나 arr[r][j] 빈칸 아님
			if (r < 0) break;  // i행 ~ 0행 전부 빈칸

			// 검은 블록은 끌어내리면 안 됨
			if (arr[r][j] == -1) continue;

			// r행 블록을 i행으로 끌어내리기
			arr[i][j] = arr[r][j];
			arr[r][j] = 0;
		}
	}
}

void Rotate() {
	int rot[20][20] = { 0, };
	
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			rot[N-1-c][r] = arr[r][c];
		}
	}
	memcpy(arr, rot, sizeof(rot));
}

int AutoPlay() {
	int score = 0;

	for (;;) {
		int B = FindGroup();
		if (B == 0) break;

		score += B * B;
		Remove();  // 최대크기 그룹만 다시 FF 돌리면서 제거하기

		Gravity();
		Rotate();
		Gravity();
	}
	return score;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << AutoPlay() << "\n";
}
