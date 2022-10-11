/******************************************************/
// [20058] 마법사 상어와 파이어스톰 (골드3)
// 구현 - 44ms, 2248KB (1시간 3분 소요)
// A의 subgrid를 회전하여 tmp에 저장 후 A에 복사 
// tmp는 [0,n) x [0,n)만 사용
//
// 40ms: A의 테두리를 얼음양 0으로 생각하고 (1,1)부터 시작 
//       -> 인덱스 범위 체크 필요없어서 4ms 빨라짐
//       -> FloodFill을 재귀로 구현하면 20ms 까지 가능
// (sr,sc)에서 시작하는 subgrid를 tmp[sr][sc]에 옮기기 -> 실행시간은 동일
// tmp[sr + c][sc + (n-1) - r] = A[sr + r][sc + c]
/******************************************************/

#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int N, Q;
int A[64 + 2][64 + 2]; // 테두리 얼음양 0으로 생각
int tmp[64 + 2][64 + 2];
int L[1000];
int sumA;
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

struct POS {
	int r, c;
};
queue<POS> q;


void Input() {
	cin >> N >> Q;
	
	N = pow(2, N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
			sumA += A[i][j];
		}
	}
	for (int i = 0; i < Q; i++) {
		cin >> L[i];
	}
}


void RotateSubgrid(int sr, int sc, int n) {
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			tmp[sr + c][sc + n - 1 - r] = A[sr + r][sc + c];
		}
	}
}

void Rotate(int n) {
	// n = 2^L (step size)
	for (int i = 1; i <= N; i += n) {
		for (int j = 1; j <= N; j += n) {
			// (i,j)에서 시작하는 n x n subgrid 를 90도 회전
			RotateSubgrid(i, j, n);
		}
	}
}

void RemoveIce() {
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (!tmp[r][c]) {
				A[r][c] = 0;
				continue;
			}

			int cnt = 0;
			for (int i = 0; i < 4; i++) {
				if (tmp[r + dr[i]][c + dc[i]]) cnt++;
			}

			if (cnt < 3) {
				A[r][c] = tmp[r][c] - 1;
				sumA--;
			}
			else A[r][c] = tmp[r][c];
		}
	}
}

void Simulation() {
	for (int i = 0; i < Q; i++) {
		Rotate(pow(2, L[i]));
		RemoveIce();
	}
}

int BFS(int sr, int sc) {
	q.push({ sr,sc });
	A[sr][sc] = 0; // 방문한 얼음은 제거
	int cnt = 1;

	while (!q.empty()) {
		POS cur = q.front(); q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (!A[nr][nc]) continue;

			q.push({ nr,nc });
			A[nr][nc] = 0;
			cnt++;
		}
	}
	return cnt;
}

int FloodFill() {
	int max = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (!A[i][j]) continue;

			int cnt = BFS(i, j);
			max = (cnt > max) ? cnt : max;
		}
	}
	return max;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Simulation();
	cout << sumA << "\n";
	cout << FloodFill() << "\n";
}
