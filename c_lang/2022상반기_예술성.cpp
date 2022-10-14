/************************************************************/
// [2022상반기_오전2번] 예술성 (난이도 중)
// FloodFill(BFS) - 4ms, 2MB (2시간 소요)
// FF를 두 번 돌리면서 그룹 정보, 그룹간 맞닿은 변의 개수 계산
// 한 그룹당 인접할 수 있는 그룹은 최대 4개 
// adj[900][900]은 매우 sparse -> map으로 하면 메모리 절감
// ** 솔루션 ** FF 한 번만 돌리기
// n번 그룹 FloodFill 돌릴 때 이전에 확정된 1 ~ n-1번 그룹들과의 
// 맞닿은 변 개수를 구해서 점수 계산을 바로바로 해줄 수 있다!!
/************************************************************/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int N;
int arr[29][29];   // 원본 보존
int chk[29][29];   // (r,c)가 몇번 그룹인지 표시 (그룹번호 1번부터!)
int rot[29][29];   // 회전결과 담을 임시공간
int num[900];      // i번 그룹의 색깔(1~10)
int sz[900];       // i번 그룹의 크기
int adj[900][900]; // 두 그룹 간 맞닿은 변의 개수
int G;             // 그룹수

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };
struct POS {
	int r, c;
};
vector<POS> S; // 각 그룹 시작위치 (맞닿은 변 계산할 때 사용)
queue<POS> q;


void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
}

void Init() {
	memset(chk, 0, sizeof(chk));
	memset(num, 0, sizeof(num));
	memset(sz, 0, sizeof(sz));
	for (int i = 0; i <= G; i++) {
		fill(adj[i], adj[i] + G + 1, 0);
	}
	G = 1; // adj 초기화할 때 G를 사용하니까 그 다음에 초기화해야지!!
	S.clear();
}

void BFS(int sr, int sc, int color) {
	chk[sr][sc] = G;
	q.push({ sr,sc });
	int cnt = 1;

	while (!q.empty()) {
		POS cur = q.front(); q.pop();
		
		for (int d = 0; d < 4; d++) {
			int nr = cur.r + dr[d];
			int nc = cur.c + dc[d];
			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
			if (chk[nr][nc] || arr[nr][nc] != color) continue;
			
			chk[nr][nc] = G;
			q.push({ nr,nc });
			cnt++;
		}
	}
	num[G] = color;
	sz[G] = cnt;
}

void FloodFill() {
	Init();

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (chk[r][c]) continue;
			BFS(r, c, arr[r][c]);
			S.push_back({ r,c });
			G++;
		}
	}
	G--;
}

void CountAdj(int sr, int sc) {
	int vis[29][29] = { 0, };
	q = {};
	q.push({ sr,sc });
	vis[sr][sc] = 1;
	int group = chk[sr][sc];

	while (!q.empty()) {
		POS cur = q.front(); q.pop();

		for (int d = 0; d < 4; d++) {
			int nr = cur.r + dr[d];
			int nc = cur.c + dc[d];
			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
			if (vis[nr][nc]) continue;

			if (chk[nr][nc] != group) {
				int other = chk[nr][nc];
				adj[group][other]++;
			}
			else {
				q.push({ nr,nc });
				vis[nr][nc] = 1;
			}
		}
	}
}

int GetScore() {
	FloodFill();
	for (POS p : S) {
		CountAdj(p.r, p.c); // 맞닿아 있는 변의 수 계산
	}

	int score = 0;
	for (int a = 1; a < G; a++) {
		for (int b = a + 1; b <= G; b++) {
			if (!adj[a][b]) continue;
			score += (sz[a] + sz[b]) * num[a] * num[b] * adj[a][b];
		}
	}
	return score;
}

void RotateSubgrid(int sr, int sc, int n) {
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			rot[sr + c][sc + n-1-r] = arr[sr + r][sc + c];
		}
	}
}

void Rotate() {
	// 십자부분
	int mid = N / 2;
	for (int i = 0; i < N; i++) {
		rot[mid][i] = arr[i][mid];
		rot[N-1 - i][mid] = arr[mid][i];
	}

	// 나머지 4개 구역
	RotateSubgrid(0, 0, mid);
	RotateSubgrid(0, mid + 1, mid);
	RotateSubgrid(mid + 1, 0, mid);
	RotateSubgrid(mid + 1, mid + 1, mid);

	memcpy(arr, rot, sizeof(rot));
}

int Simulation() {
	int sum = GetScore();
	for (int t = 1; t <= 3; t++) {
		Rotate();
		sum += GetScore();
	}
	return sum;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Simulation() << "\n";
}
