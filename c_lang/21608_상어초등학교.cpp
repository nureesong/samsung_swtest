/*******************************************/
// [21608] 상어 초등학교 (골드5)
// 구현 - 0ms, 2660KB (2시간 40분 소요)
// 초기값 설정할 때 반드시 갱신되는지 확인하기!
// n번 학생이 m번 학생을 좋아하는지 빠르게 판단하기 위해
// directed 인접행렬을 사용했다. O(1)이지만, 인접행렬이 매우 sparse하다.
// unordered_set으로 하면 O(logN)이지만, 메모리를 적게 사용한다.
/*******************************************/
// 0ms, 2652KB
// 빈칸 중에서 사방에 좋아하는 학생수, 빈칸수를 동시에 세서
// 우선순위 조건대로 갱신하면 됨

#include <iostream>
using namespace std;

int N, M;
int arr[20][20];
int adj[400 + 1][400 + 1]; // directed
int S[400];    // 배정 순서대로 학생번호

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };


void Input() {
	cin >> N;
	M = N * N;
	int u, v;
	for (int i = 0; i < M; i++) {
		cin >> u;
		S[i] = u;
		for (int j = 0; j < 4; j++) {
			cin >> v;
			adj[u][v] = 1;
		}
	}
}

void Assign(int cur) {
	int maxcnt = -1, maxempty = -1, minr, minc;

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (arr[r][c]) continue;

			// 좋아하는 학생 수, 빈칸수 동시에 체크
			int cnt_like = 0, cnt_empty = 0;

			for (int d = 0; d < 4; d++) {
				int nr = r + dr[d];
				int nc = c + dc[d];
				if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;

				int nbd = arr[nr][nc];
				if (!nbd) cnt_empty++;
				else if (adj[cur][nbd]) cnt_like++;
			}

			if (cnt_like > maxcnt ||
				cnt_like == maxcnt && cnt_empty > maxempty ||
				cnt_like == maxcnt && cnt_empty == maxempty && r < minr ||
				cnt_like == maxcnt && cnt_empty == maxempty && r == minr && c < minc) {
				maxcnt = cnt_like;
				maxempty = cnt_empty;
				minr = r;
				minc = c;
			}
		}
	}

	arr[minr][minc] = cur;
}


void Simulation() {
	int r = 1, c = 1;
	arr[r][c] = S[0];  // 0번째 학생은 무조건 (1,1)

	for (int i = 1; i < M; i++) {
		Assign(S[i]);
	}

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cout << arr[r][c] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int SatisfySum() {
	int score[] = { 0,1,10,100,1000 };
	int sum = 0;

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			int cur = arr[r][c];
			int cnt = 0;
			for (int d = 0; d < 4; d++) {
				int nr = r + dr[d];
				int nc = c + dc[d];
				if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;

				int nbd = arr[nr][nc];
				if (adj[cur][nbd]) cnt++;
			}
			sum += score[cnt];
		}
	}

	return sum;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Simulation();
	cout << SatisfySum() << "\n";
}
