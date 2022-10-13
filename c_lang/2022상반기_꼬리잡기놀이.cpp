/***************************************************************/
// [2022상반기_오후_1번] 꼬리잡기놀이 (난이도 상)
// FloodFill(BFS) 2ms (3시간 50분 소요)
// FloodFill(DFS) 1ms
// 
// - 꼬리 먼저 옮겨서 빈 공간 만들고 머리 옮기기!! 
//   머리를 먼저 옮기면 머리와 꼬리가 붙어있는 경우 꼬리를 덮어버림
// - 시계/반시계 제대로 이동하는지 손으로 시뮬레이션 해보기!!
// - 반시계일 때는 path도 거꾸로 저장하기!! push_front()
//   path에 머리~꼬리만 저장하고 머리사람이 덱의 앞(0)/뒤(1)인지 기록하는 방법도 있다.
/**************************************************************/
// FloodFill - 재귀
#if 0
#include <iostream>
#include <cstring>
#include <deque>
using namespace std;

int N, M, K;
int arr[20][20]; // 0:빈칸, 1~3: 머리~꼬리, 4: 빈경로
int chk[20][20]; // 경로에 -팀번호 표시

int dr[] = { 0,-1,0,1 }; // 좌상우하 -> 머리의 시계방향부터 훑기
int dc[] = { -1,0,1,0 };

struct TEAM {
	int head, d, cnt, len; // 머리인덱스, 회전방향, 인원수, 경로길이
}T[5 + 1];

struct POS {
	int r, c;
};
deque<POS> path[5 + 1];


void Input() {
	cin >> N >> M >> K;

	int id = 1; // 처음으로 발견되는 머리부터 팀 번호 매기기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 1) path[id++].push_back({ i,j });
		}
	}

}

void Print(int(*a)[20]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << a[i][j] << " ";
		}
		cout << '\n';
	}
	cout << '\n';
}

void FloodFill(int r, int c, int n) {
	if (T[n].d == 1) path[n].push_back({ r,c });
	else path[n].push_front({ r,c });
	
	if (chk[r][c] > 0 && chk[r][c] < 4) T[n].cnt++;
	chk[r][c] = -n;

	for (int d = 0; d < 4; d++) {
		int nr = r + dr[d];
		int nc = c + dc[d];
		if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;

		if (chk[nr][nc] > 0 && chk[nr][nc] <= 4) {
			FloodFill(nr, nc, n);
		}
	}
}

void InitPath() {
	memcpy(chk, arr, sizeof(arr));
	for (int i = 1; i <= M; i++) {
		POS head = path[i][0];
		chk[head.r][head.c] = -i; // 지나간 길은 팀 번호로 마킹!
		T[i].cnt = 1;

		// 2번 사람(몸통) 찾기
		int nr, nc, d;
		for (d = 0; d < 4; d++) {
			nr = head.r + dr[d];
			nc = head.c + dc[d];
			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
			if (chk[nr][nc] == 2) break;
		}
		T[i].d = (d < 2) ? 1 : -1; // 시작방향 찾기
		
		FloodFill(nr, nc, i);  // 경로 찾기 (2번 사람부터 시작)
		
		T[i].len = path[i].size();
		if (T[i].d == -1) T[i].head = path[i].size() - 1;
	}
}

// m번 팀 한칸씩 이동 - 꼬리 먼저 옮겨서 빈 공간 만들고 머리 옮기기!!
void Move(int m) {
	int h = T[m].head;
	int d = T[m].d;
	int cnt = T[m].cnt;
	int len = T[m].len;

	// 꼬리 옮기기
	int t = (h + d * (cnt - 1) + len) % len;
	POS tail = path[m][t];
	arr[tail.r][tail.c] = 4; // 원래 꼬리가 있던 곳은 이제 빈 경로

	int nt = (t - d + len) % len;  // 새로운 꼬리
	POS ntail = path[m][nt];
	arr[ntail.r][ntail.c] = 3;

	// 머리 옮기기	
	POS head = path[m][h];
	arr[head.r][head.c] = 2; // 원래 머리가 있던 곳은 이제 몸통

	int nh = (h - d + len) % len; // 새로운 머리
	POS nhead = path[m][nh];
	arr[nhead.r][nhead.c] = 1;
	T[m].head = nh;
}

// 공 던지기 + 점수 획득한 팀 방향 바꾸기
int ThrowBall(int round) {
	int d = (round / N) % 4; // 공 던지는 방향 (우상좌하 - 0123)

	int r, c;
	if (d == 0) { // 우
		r = round % N;
		c = 0;
		while (c < N && (arr[r][c] == 0 || arr[r][c] == 4)) c++;
		if (c == N) return 0; // 공에 맞은 사람 없음
	}
	else if (d == 2) { // 좌
		r = N - 1 - round % N;
		c = N - 1;
		while (c >= 0 && (arr[r][c] == 0 || arr[r][c] == 4)) c--;
		if (c == -1) return 0;
	}
	else if (d == 1) { // 상
		c = round % N;
		r = N - 1;
		while (r >= 0 && (arr[r][c] == 0 || arr[r][c] == 4)) r--;
		if (r == -1) return 0;
	}
	else {  // 하
		c = N - 1 - round % N;
		r = 0;
		while (r < N && (arr[r][c] == 0 || arr[r][c] == 4)) r++;
		if (r == N) return 0;
	}

	// 최초로 공에 맞은 사람 -> 무슨 팀인지, 팀내 몇 번째인지
	int id = -chk[r][c];   // 팀 번호
	int head = T[id].head; // 해당 팀 머리

	int p = head, k;  // 머리부터 차례로 이동하면서 좌표비교
	for (k = 1; k <= T[id].cnt; k++) {
		if (r == path[id][p].r && c == path[id][p].c) break;
		p = (p + T[id].d + T[id].len) % T[id].len;
	}

	// 공 맞은 팀: 머리-꼬리 위치, 이동방향 뒤집기
	T[id].head = (head + T[id].d * (T[id].cnt - 1) + T[id].len) % T[id].len;
	T[id].d *= (-1);

	return k * k;
}

int Simulation() {
	int score = 0;

	for (int i = 0; i < K; i++) {
		for (int m = 1; m <= M; m++) {
			Move(m);
		}

		score += ThrowBall(i);
	}
	return score;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//freopen("in.txt", "r", stdin);

	Input();
	InitPath();
	cout << Simulation() << "\n";
}
#endif
