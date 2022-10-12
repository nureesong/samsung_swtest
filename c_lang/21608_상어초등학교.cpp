/*******************************************/
// [21608] 상어 초등학교 (골드5)
// 구현 - 0ms, 2660KB (2시간 40분 소요)
// 초기값 설정할 때 반드시 갱신되는지 확인하기!
/*******************************************/

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int N, M;
int arr[20 + 2][20 + 2];
int emp[20 + 2][20 + 2];
int adj[400 + 1][400 + 1]; // directed
int S[400];    // 배정 순서대로 학생번호

struct POS {
	int r, c;
};
POS P[400 + 1];

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

void Input() {
	cin >> N;
	M = N * N;
	int u, v;
	for (int i = 0; i < M; i++) {
		cin >> u;
		S[i] = u;
		for (int j = 0; j < 4; j++) {
			cin >> v;
			adj[u][v] = 1;
		}
	}
}

void Init() {
	emp[1][1] = emp[1][N] = emp[N][1] = emp[N][N] = 2;
	for (int i = 2; i < N; i++) {
		emp[i][1] = emp[i][N] = emp[1][i] = emp[N][i] = 3;
		for (int j = 2; j < N; j++) {
			emp[i][j] = 4;
		}
	}
}

void Assign(int cur) {
	int cnt[20 + 2][20 + 2] = { 0, };

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (arr[r][c]) continue;

			// 비어있는 칸: 좋아하는 학생 몇명 있는지 체크
			for (int d = 0; d < 4; d++) {
				int nr = r + dr[d];
				int nc = c + dc[d];
				
				int nbd = arr[nr][nc];
				if (adj[cur][nbd]) cnt[r][c]++;
			}
		}
	}

	// 좋아하는 학생이 가장 많은 빈칸 찾기
	int maxcnt = -1;
	vector<POS> maxpos;
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (arr[r][c]) continue; // 빈칸만 봐야지!!!

			if (cnt[r][c] > maxcnt) {
				maxcnt = cnt[r][c];
				maxpos.clear();
				maxpos.push_back({ r,c });
			}
			else if (cnt[r][c] == maxcnt) {
				maxpos.push_back({ r,c });
			}
		}
	}

	// 최댓값이 여러 칸이면, 인접 영역이 가장 많이 빈 곳 찾기
	POS maxP;
	if (maxpos.size() > 1) {
		int maxempty = -1; // 주변에 빈칸이 없을수도 있지... 본인만 빈칸이면됐지..
		for (POS p : maxpos) {
			if (emp[p.r][p.c] > maxempty) {
				maxempty = emp[p.r][p.c];
				maxP = p;
			}
		}
	}
	else maxP = maxpos[0];
	
	arr[maxP.r][maxP.c] = cur;
	P[cur] = { maxP.r,maxP.c };
	for (int d = 0; d < 4; d++) {
		int nr = maxP.r + dr[d];
		int nc = maxP.c + dc[d];
		if (emp[nr][nc]) emp[nr][nc]--;
	}
}

void Simulation() {
	int r = 2, c = 2;
	arr[r][c] = S[0];
	P[S[0]] = { r,c }; // 0번째 학생은 무조건 (2,2)
	emp[r - 1][c]--; emp[r + 1][c]--;
	emp[r][c - 1]--; emp[r][c + 1]--;

	for (int i = 1; i < M; i++) {
		Assign(S[i]);
	}
}

int SatisfySum() {
	int score[] = { 0,1,10,100,1000 };
	int sum = 0;
	for (int i = 0; i < M; i++) {
		int count = 0;
		int cur = S[i];
		int r = P[cur].r, c = P[cur].c;

		for (int d = 0; d < 4; d++) {
			int nbd = arr[r + dr[d]][c + dc[d]];
			if (adj[cur][nbd]) count++;
		}
		sum += score[count];
	}
	return sum;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Init();

	Simulation();
	cout << SatisfySum() << "\n";
}
