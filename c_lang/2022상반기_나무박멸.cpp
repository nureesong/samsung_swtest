/******************************************/
// [2022상반기_오후2번] 나무박멸 (난이도 중)
// 구현 - 11ms (2시간 소요)
// 인덱스 범위 체크 빼먹지 말기!!
/******************************************/

#include <iostream>
#include <vector>
using namespace std;

int N, M, K, C;
int dr[] = { -1,1,0,0,-1,-1,1,1 }; // 상하좌우(0123), 대각선(4567)
int dc[] = { 0,0,-1,1,-1,1,-1,1 };

struct TREE {
	int n, t; // 나무 그루수, 제초제 잔여시간
}arr[20][20];

struct POS {
	int r, c;
};
struct DATA {
	int cnt;
	POS p;
};

void Input() {
	cin >> N >> M >> K >> C;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j].n;
		}
	}
	C++;
}

void GrowTree() {
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (arr[r][c].t) arr[r][c].t--; // 제초제 잔여시간 감소
			if (arr[r][c].n <= 0) continue; // 빈칸.벽은 성장X

			// 나무 성장 - 인접 4칸 중 나무가 있는 칸의 수만큼
			for (int d = 0; d < 4; d++) {
				int nr = r + dr[d];
				int nc = c + dc[d];
				if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
				if (arr[nr][nc].n > 0) arr[r][c].n++;
			}
		}
	}
}

void AddTree() {
	int tmp[20][20] = { 0, }; // 번식한 나무 그루수 기록

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (arr[r][c].n <= 0) continue; // 빈칸.벽

			vector<POS> E; // 번식 가능한 칸 담기 (제초제.벽.다른나무X)
			for (int d = 0; d < 4; d++) {
				int nr = r + dr[d];
				int nc = c + dc[d];
				if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
				if (arr[nr][nc].t == 0 && arr[nr][nc].n == 0) {
					E.push_back({ nr,nc });
				}
			}

			if (!E.empty()) {
				int v = arr[r][c].n / E.size();
				for (POS p : E) {
					tmp[p.r][p.c] += v;
				}
			}
		}
	}

	// 기존 나무들과 번식한 나무 합치기
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			arr[r][c].n += tmp[r][c];
		}
	}
}

DATA FindMax() {
	int maxcnt = -1; POS maxP;

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			// (r,c)에 제초제를 뿌렸을 때 박멸되는 나무 그루 수 계산
			int cnt = arr[r][c].n;  // 현위치 나무 전부 박멸
			if (cnt == -1) cnt = 0; // 벽인 경우, 0으로 바꾸기!

			// 나무가 있는 칸만 대각선 4방향으로 k칸 전파
			if (cnt) {
				for (int d = 4; d < 8; d++) {
					for (int k = 1; k <= K; k++) {
						int nr = r + k * dr[d];
						int nc = c + k * dc[d];
						if (nr < 0 || nr >= N || nc < 0 || nc >= N) break;
						if (arr[nr][nc].n <= 0) break;
						cnt += arr[nr][nc].n;
					}
				}
			}

			if (cnt > maxcnt) {
				maxcnt = cnt;
				maxP = { r,c };
			}
		}
	}
	return { maxcnt, maxP };
}

void Remove(int sr, int sc) {
	// 시작지점 나무 박멸
	if (arr[sr][sc].n > 0) arr[sr][sc].n = 0; // 벽에 뿌릴 때, 0그루로 만들지 않도록 주의!
	arr[sr][sc].t = C;

	for (int d = 4; d < 8; d++) {
		for (int k = 1; k <= K; k++) {
			int nr = sr + k * dr[d];
			int nc = sc + k * dc[d];
			if (nr < 0 || nr >= N || nc < 0 || nc >= N) break;
			
			arr[nr][nc].t = C; // 벽/빈칸까지는 뿌리고 전파 중단
			if (arr[nr][nc].n <= 0) break;
			arr[nr][nc].n = 0;
		}
	}
}

int Simulation() {
	int sum = 0;
	for (int t = 1; t <= M; t++) {
		GrowTree();
		AddTree();
		DATA ret = FindMax();
		Remove(ret.p.r, ret.p.c);
		sum += ret.cnt;
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
