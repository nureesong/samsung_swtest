/************************************/
// [5644] 무선 충전
// 구현 - 8ms, 13396KB (1시간 20분 소요)
// x,y축 <-> 행,열 방향 잘 생각하자!!
/************************************/

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int M, N;                   // 이동시간, 배터리 개수
int arr[8][10 + 1][10 + 1]; // 각 BC 충전범위에 1 표시
int path[2][100];           // A,B 이동방향 (0:제자리, 1~4:상우하좌)
int dx[] = { 0,0,1,0,-1 };  // dr, dc랑 다르다!!
int dy[] = { 0,-1,0,1,0 };
struct BATTERY {
	int x, y, d, p;
}BC[8];

struct POS { int x, y; };
POS A, B;

struct STATUS { int x, y, d; };
queue<STATUS> q;


void Input() {
	// Init
	memset(arr, 0, sizeof(arr));
	A = { 1,1 };
	B = { 10,10 };

	cin >> M >> N;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < M; j++) {
			cin >> path[i][j];
		}
	}
	for (int i = 0; i < N; i++) {
		cin >> BC[i].x >> BC[i].y >> BC[i].d >> BC[i].p;
	}
}


void FF(int n, int sx, int sy) {
	q = {};
	q.push({ sx,sy,0 });
	arr[n][sx][sy] = 1;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();
		if (cur.d == BC[n].d) return;
		int nd = cur.d + 1;

		for (int d = 1; d <= 4; d++) { // 상우하좌
			int x = cur.x + dx[d];
			int y = cur.y + dy[d];
			if (x < 1 || x > 10 || y < 1 || y > 10) continue;
			if (arr[n][x][y]) continue;
			q.push({ x,y,nd });
			arr[n][x][y] = 1;
		}
	}
}

void InitArr() {
	for (int i = 0; i < N; i++) {
		FF(i, BC[i].x, BC[i].y);
	}
}


int Check() {
	int maxsum = 0;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int sum = (arr[i][A.x][A.y]) ? BC[i].p : 0;
			int flag = arr[j][B.x][B.y];
			
			// 서로 다른 BC의 충전범위에 있거나, B만 충전범위 안에 있으면 증가
			if ((sum && flag && i != j) || (!sum && flag)) {
				sum += BC[j].p;
			}
			maxsum = (sum > maxsum) ? sum : maxsum;
		}
	}
	return maxsum;
}


int Solve() {
	int sol = Check(); // 초기 위치부터 충전 가능
	
	for (int i = 0; i < M; i++) {
		A.x += dx[path[0][i]];
		A.y += dy[path[0][i]];
		B.x += dx[path[1][i]];
		B.y += dy[path[1][i]];
		sol += Check();
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
		InitArr();
		cout << "#" << i << " " << Solve() << "\n";
	}
}
