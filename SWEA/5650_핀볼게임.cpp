#define _CRT_SECURE_NO_WARNINGS

/***************************************************/
// [5650] 핀볼 게임
// 구현 - 81ms
// 시간초과 원인 - 시작위치를 블랙홀(-1)로 변경해야 while문 종료!!
// 벽에 부딪히면 리턴된다고 잘못 생각했다.
// 한 행에 웜홀 두 개만 존재하고 두 웜홀 사이에서 오른쪽으로 시작하는 경우, 
// 계속 두 웜홀 사이를 왔다갔다 하는 무한루프에 빠진다!!
// N = 4
// 0 0 0 0
// 6 0 0 6
// 0 0 0 0
// 0 0 0 0
/***************************************************/

#include <iostream>
#include <vector>
using namespace std;

int N;
int arr[100 + 2][100 + 2]; // 테두리 5번 블럭으로 세팅. (1,1)부터 시작

struct POS {
	int r, c;
};
vector<POS> wh[10 + 1]; // 웜홀 6~10
vector<POS> E;     // 빈 칸 0


// 현위치의 상우하좌(0123)에 n번 블럭 위치 시 다음 이동 방향
int LUT[5 + 1][4] = {
	{}, { 2,3,1,0 }, { 1,3,0,2 }, { 3,2,0,1 }, { 2,0,3,1 }, { 2,3,0,1 }
};
// 수평/수직면 여부
int flag[5 + 1][4] = {
	{}, {1,1,0,0}, {0,1,1,0}, {0,0,1,1}, {1,0,0,1}, {1,1,1,1}
};


void Input() {
	// Init
	for (int i = 6; i <= 10; i++) wh[i].clear();
	E.clear();

	cin >> N;
	int n;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> n;
			arr[i][j] = n;
			if (!n) E.push_back({ i,j });
			else if (n > 5) wh[n].push_back({ i,j });
		}
	}

	// 벽에 충돌 시 튕겨나오도록 테두리를 5번 블럭으로 세팅
	for (int i = 1; i <= N; i++) {
		arr[i][0] = arr[i][N + 1] = arr[0][i] = arr[N + 1][i] = 5;
	}	
}


int Simulation(int sr, int sc, int sd) {
	static int dr[] = { -1,0,1,0 }; // 상우하좌
	static int dc[] = { 0,1,0,-1 };

	int r = sr + dr[sd];
	int c = sc + dc[sd];
	int d = sd;
	arr[sr][sc] = -1; // 시작지점 블랙홀로 바꿔놓기
	int cnt = 0;

	while (arr[r][c] != -1) {
		int b = arr[r][c];

		if (b && b <= 5) {     // 블럭/벽
			if (!flag[b][d]) { // 경사면 충돌
				cnt++;
				d = LUT[b][d];
			}
			else { // 수직/수평면 충돌
				arr[sr][sc] = 0;
				return 2 * cnt + 1;
			}
		}
		else if (b > 5) { // 웜홀
			int other = 0;
			if (r == wh[b][0].r && c == wh[b][0].c) other = 1;
			r = wh[b][other].r;
			c = wh[b][other].c;
		}

		r += dr[d];
		c += dc[d];
	}

	arr[sr][sc] = 0;
	return cnt;
}

int Solve() {
	int sol = 0; // 점수 최댓값
	for (POS s : E) {
		for (int d = 0; d < 4; d++) {
			int ret = Simulation(s.r, s.c, d);
			sol = (ret > sol) ? ret : sol;
		}
	}
	return sol;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Input();
		cout << "#" << i << " " << Solve() << "\n";
	}
	return 0;
}
