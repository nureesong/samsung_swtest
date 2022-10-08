#define _CRT_SECURE_NO_WARNINGS

/**************************************************************/
// [20057] 마법사 상어와 토네이도 (골드3)
// 구현 - 36ms, 4668KB
// 토네이도 이동방향, 모래 흩날리는 위치 모두 룩업테이블로 만들어놓음
// 1시간 49분 소요
/**************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int N;
int A[499][499];

// 토네이도 이동방향 (총 N^2 - 1번 이동)
// 0 1 2 3 방향 순서로 1,1,2,2,3,3,4,4,5,5,...칸씩 이동
vector<int> cnt;
// 0 1 2 2 3 3 / 0 0 0 1 1 1 2 2 2 2 3 3 3 3 / .. -> 룩업테이블 만들어놓기
vector<int> M;


struct POS {
	int r, c;
};
// 다음 위치인 y기준으로 흩날리는 9칸 변위 테이블
POS LUT[4][9] = { // 토네이도 이동방향: 좌하우상(0123)
	{ {-1,1},{1,1},{-2,0},{2,0},{0,-2},{-1,0},{1,0},{-1,-1},{1,-1} },
	{ {-1,-1},{-1,1},{0,-2},{0,2},{2,0},{0,-1},{0,1},{1,-1},{1,1} },
	{ {-1,-1},{1,-1},{-2,0},{2,0},{0,2},{-1,0},{1,0},{-1,1},{1,1} },
	{ {1,-1},{1,1},{0,-2},{0,2},{-2,0},{0,-1},{0,1},{-1,-1},{-1,1} }
};
int P[9] = { 1,1,2,2,5,7,7,10,10 }; // 모래 비율. 마지막은 알파(나머지)


void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
		}
	}
}

void MoveDirection() {
	for (int i = 1; i < N; i++) {
		cnt.push_back(i);
		cnt.push_back(i);
	}

	// 토네이도 N/2바퀴 돌리기
	int d = 0;
	for (int c : cnt) {
		for (int i = 0; i < c; i++) {
			M.push_back(d);
		}
		d++; d %= 4;
	}

	// 한 바퀴 돌 때마다, 시작점이 우상향 대각선으로 한 칸씩 올라가므로
	// 마지막에는 (0,N-1) -> (0,0)까지 왼쪽으로 (N-1)칸 직진
	for (int i = 0; i < N-1; i++) {
		M.push_back(0);
	}
}

int Solve() {
	static int dr[] = { 0,1,0,-1 }; // 좌하우상
	static int dc[] = { -1,0,1,0 };
	int sol = 0; // 격자 밖으로 나간 모래양
	int r = N / 2, c = N / 2; // 토네이도 시작점

	for (int d : M) {
		r += dr[d]; // (r,c) = 그림상 y의 위치
		c += dc[d];
		int y = A[r][c];
		A[r][c] = 0;

		int alpha = y;
		int nr, nc;
		for (int i = 0; i < 9; i++) {
			int sand = y * P[i] / 100;
			alpha -= sand;

			nr = r + LUT[d][i].r;
			nc = c + LUT[d][i].c;

			if (nr < 0 || nr >= N || nc < 0 || nc >= N) sol += sand;
			else A[nr][nc] += sand;
		}
		nr = r + dr[d];
		nc = c + dc[d];
		if (nr < 0 || nr >= N || nc < 0 || nc >= N) sol += alpha;
		else A[nr][nc] += alpha;
	}

	return sol;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	MoveDirection();
	cout << Solve() << "\n";
}
