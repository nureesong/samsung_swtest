/************************************/
// [17837] 새로운 게임2 (골드2)
// 구현 - 0ms, 2172KB
// 09:02 ~ 10:44 (1시간 42분 소요)
/************************************/

#include <iostream>
#include <vector>
using namespace std;

int N, K;
int brd[12 + 2][12 + 2];    // 체스판 0:빈칸, 1:빨강, 2:파랑(테두리도 파랑!)
vector<int> arr[12 + 2][12 + 2]; // 쌓여있는 말 번호 (한칸 당 최대 3개 쌓일 수 있음)

struct HORSE {
	int r, c, d;
	int s; // stair (0,1,2층 중 하나)
}H[10 + 1]; // 말: 1~K번


void Input() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		brd[i][0] = brd[i][N + 1] = brd[0][i] = brd[N + 1][i] = 2;
		for (int j = 1; j <= N; j++) {
			cin >> brd[i][j];
		}
	}
	for (int i = 1; i <= K; i++) {
		cin >> H[i].r >> H[i].c >> H[i].d;
		arr[H[i].r][H[i].c].push_back(i);
	}
}

// n번 말 이동 성공하면 1 (제자리 포함), 실패(말 4개)하면 0
int Move(int n) {
	static int dr[] = { 0, 0,0,-1,1 }; // 우좌상하(1234)
	static int dc[] = { 0, 1,-1,0,0 };
	static int rev[] = { 0,2,1,4,3 }; // 우좌상하 -> 좌우하상

	int r = H[n].r, c = H[n].c;
	int d = H[n].d, s = H[n].s;

	int nr = r + dr[d];
	int nc = c + dc[d];
	int color = brd[nr][nc];

	if (color == 2) { // 파란색
		H[n].d = rev[d]; // 실수 - 파란색 칸이면 무조건 방향 뒤집어놓기!!
		nr = r + dr[H[n].d];
		nc = c + dc[H[n].d];
		color = brd[nr][nc];

		if (color == 2) return 1;  // 반대방향도 파란색이면 제자리
	}
	
	// 빨간색, 흰색인 경우만 남음!!
	int sz = arr[r][c].size() - s; // 현재칸에서 n번 말 위로 쌓여있는 말 개수
	int nsz = arr[nr][nc].size();  // 이동하려는 칸에 쌓여있는 말 개수
	if (nsz >= 3 || sz + nsz >= 4) return 0;

	if (color == 1) { // 빨간색: 말 뒤집어서 쌓기
		while (sz--) {
			int cur = arr[r][c].back(); arr[r][c].pop_back();
			arr[nr][nc].push_back(cur);
			H[cur] = { nr,nc,H[cur].d,nsz++ };
		}
	}
	else { // 흰색: 말 순서대로 쌓기
		for (int i = s; i < s + sz; i++) {
			int cur = arr[r][c][i];
			arr[nr][nc].push_back(cur);
			H[cur] = { nr,nc,H[cur].d,nsz++ };
		}
		while (sz--) arr[r][c].pop_back();
	}
	return 1;
}

int Solve() {
	for (int t = 1; t <= 1000; t++) {
		for (int n = 1; n <= K; n++) {
			if (!Move(n)) return t;
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Solve() << "\n";
}
