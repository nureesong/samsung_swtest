/***************************************************/
// [15685] 드래곤 커브 (골드4)
// 1세대: (0세대 커브) + (0세대 끝->시작 순서로 점 하나씩 90도 회전)
// 90도 회전의 기준점 = 이전세대 끝점
// (r,c)를 (a,b) 기준으로 90도 회전하면 (a-b+c, a+b-r)
// 입력받은 x,y -> c,r 행,열 바뀌는 거 주의!!
/***************************************************/

#include <iostream>
#include <vector>
using namespace std;

int N;
int grid[101 + 2][101 + 2];

struct POS {
	int r, c;
};
vector<POS> curve;


void DrawCurve(int r, int c, int d, int g) {
	static int dr[] = { 0,-1,0,1 }; // 우상좌하(0123)
	static int dc[] = { 1,0,-1,0 };
	curve.clear();

	// 0세대 드래곤 커브는 시작방향 고려!!
	curve.push_back({ r,c });
	curve.push_back({ r + dr[d], c + dc[d] });
	grid[r][c] = 1;
	grid[r + dr[d]][c + dc[d]] = 1;

	// 1 ~ g세대 드래곤 커브 그리기
	for (int i = 1; i <= g; i++) {
		// 90도 회전시 기준점 = 이전 세대 끝점
		int a = curve.back().r;
		int b = curve.back().c;

		// (r,c)를 (a,b) 기준으로 90도 회전하면 (a-b+c, a+b-r)
		for (int j = curve.size() - 2; j >= 0; j--) {
			int nr = a - b + curve[j].c;
			int nc = a + b - curve[j].r;
			curve.push_back({ nr,nc });
			grid[nr][nc] = 1;
		}
	}
}

int CountSquare() {
	int cnt = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (grid[i][j] && grid[i][j + 1] && grid[i + 1][j] && grid[i + 1][j + 1]) cnt++;
		}
	}
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int r, c, d, g;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> r >> c >> d >> g;
		DrawCurve(c, r, d, g);
	}
	
	cout << CountSquare() << "\n";
}
