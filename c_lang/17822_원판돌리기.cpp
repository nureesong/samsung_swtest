/************************************/
// [17822] 원판 돌리기 (골드3)
// 09:13 ~ 10:58 (1시간 45분)
// 8ms, 2180KB
// 평균이랑 같은 수일 때는 숫자 안 바뀜!
// 원판을 한번에 훑어서 인접 영역에 같은 숫자 있으면 전부 지워야 함 -> FloodFill
// 원판 중 한 숫자 인접영역만 순차적으로 지우다가 안 지워진 게 생기는 걸 발견..!
/************************************/

#include <iostream>
#include <deque>
#include <queue>
using namespace std;

int N, M, T;
deque<int> deq[50 + 1];
int total_sum;
int cnt_rem; // 원판에 남아있는 숫자 개수

struct STATUS {
	int r, c;
};
queue<STATUS> q;

void Input() {
	cin >> N >> M >> T;
	int n;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> n;
			deq[i].push_back(n);
			total_sum += n;
		}
	}
	cnt_rem = M * N;
}

void Rotate(int n, int d, int k) {
	if (d == 1) k = M - k; // 반시계 k칸 회전 = 시계 M-k칸 회전
	// 시계 방향 회전으로 통일!
	for (int i = 0; i < k; i++) {
		deq[n].push_front(deq[n].back());
		deq[n].pop_back();
	}
}

int FloodFill(int r, int c) {
	static int dr[] = { 0,0,-1,1 }; // 좌우상하
	static int dc[] = { -1,1,0,0 };

	q.push({ r,c });
	int tar = deq[r][c];
	int cnt = 0;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();

		for (int k = 0; k < 4; k++) {
			int nr = cur.r + dr[k];
			int nc = (cur.c + dc[k] + M) % M;
			if (nr < 1 || nr > N) continue;
			if (deq[nr][nc] != tar) continue;

			q.push({ nr,nc });
			deq[nr][nc] = 0;
			total_sum -= tar;
			cnt_rem--;
			cnt++;
		}
	}
	return cnt;
}

int Remove() {
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			if (!deq[i][j]) continue;
			cnt += FloodFill(i, j);
		}
	}
	return cnt > 0;
}

void Modify() {
	double avg = (double)total_sum / cnt_rem;

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			if (!deq[i][j]) continue;

			if ((double)deq[i][j] > avg) {
				deq[i][j]--;
				total_sum--;
			}
			else if ((double)deq[i][j] < avg) {
				deq[i][j]++;
				total_sum++;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	int x, d, k;
	for (int t = 0; t < T; t++) {
		cin >> x >> d >> k;
		
		if (!cnt_rem) break;

		for (int n = x; n <= N; n += x) {
			Rotate(n, d, k);
		}
		if (!Remove()) Modify();
	}
	cout << total_sum << "\n";
}
