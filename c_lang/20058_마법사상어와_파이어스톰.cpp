/********************************************/
// [20058] 마법사 상어와 파이어스톰 (골드3)
// 구현 - 44ms, 2248KB (1시간 3분 소요)
// A의 subgrid를 회전하여 tmp에 저장 후 A에 복사 
// tmp는 [0,n) x [0,n)만 사용
/********************************************/

#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int N, Q;
int R, C;
int A[64][64];   
int tmp[64][64];
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
	
	R = C = pow(2, N);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
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
			tmp[c][n - 1 - r] = A[sr + r][sc + c];
		}
	}
	
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			A[sr + r][sc + c] = tmp[r][c];
		}
	}
}

// n = 2^L (step size)
void Rotate(int n) {
	if (n == 1) return;

	for (int i = 0; i < R; i += n) {
		for (int j = 0; j < C; j += n) {
			// (i,j)에서 시작하는 n x n subgrid 를 90도 회전
			RotateSubgrid(i, j, n);
		}
	}
}

void RemoveIce() {
	vector<POS> rem;
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			if (!A[r][c]) continue;

			int cnt = 0;
			for (int i = 0; i < 4; i++) {
				int nr = r + dr[i];
				int nc = c + dc[i];
				if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
				if (!A[nr][nc]) continue;
				cnt++;
			}
			if (cnt < 3) rem.push_back({ r,c });
		}
	}

	for (POS p : rem) {
		A[p.r][p.c]--;
		sumA--;
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
			if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
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
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
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
