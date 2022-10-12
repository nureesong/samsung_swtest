#define _CRT_SECURE_NO_WARNINGS

/************************************************************/
// [2112] 보호필름
// DFS - 1306ms, 13540KB (3시간 소요)
// 행마다 3가지 경우: 약품 A/B투입, 투입X. => O(3^D) = 최대 160만
// 경우의 수 발전마다 배열 상태를 보존해야 하는 경우에는
// DFS 내부에서 로컬변수 선언하고 전역배열을 백업해둔 후, DFS 종료 후 복원
// memset(arr+n, 1, sizeof(arr[n])) -> 01010101 로 세팅됨!!
/**********************************************************/

// 544 ms -> 행별 약품 선택값 기록(-1,0,1)
//           원본 배열을 보존하므로 DFS에서 백업, 복원할 필요X
// 389 ms -> 약품 투입 안 하는 경우를 먼저 하는 게 빠르다.. 이유는 모름!
#if 1
#include <iostream>
using namespace std;

int D, W, K;
int arr[13][20]; // 원본 보존!!
int pick[13];    // 각 행마다 경우의 수 기록 (-1: 투입X, 0/1: A/B)
int sol;


void Input() {
	cin >> D >> W >> K;
	for (int i = 0; i < D; i++) {
		pick[i] = -1; // 투입 안 하는 게 기본 세팅!!
		for (int j = 0; j < W; j++) {
			cin >> arr[i][j];
		}
	}
	sol = K; // 연속된 행 K개에 약품을 투입하면 
}


// 각 컬럼별로 K개의 행을 슬라이딩 윈도우로 확인
int Check() {
	for (int c = 0; c < W; c++) {
		// 초기 윈도우: [0, K) 의 합을 계산
		int sum = 0;
		int v;
		for (int r = 0; r < K; r++) {
			v = (pick[r] == -1) ? arr[r][c] : pick[r];
			sum += v;
		}
		if (sum == 0 || sum == K) continue;
		sum -= ((pick[0] == -1) ? arr[0][c] : pick[0]);

		// 다음 윈도우부터는 끝점 기준 [K, D)
		int r;
		for (r = K; r < D; r++) {
			v = (pick[r] == -1) ? arr[r][c] : pick[r];
			sum += v;

			if (sum == 0 || sum == K) break;
			sum -= ((pick[r-K+1] == -1) ? arr[r-K+1][c] : pick[r-K+1]);
		}

		if (r == D) return 0;
	}
	return 1;
}

// cnt: 현재까지 약품 투입횟수, n행에 대한 3가지 경우의 수 시도
void DFS(int cnt, int n) {
	if (cnt >= sol) return;

	if (Check()) {
		sol = cnt;
		return;
	}

	if (n == D) return;

	// 약품 투입X
	DFS(cnt, n + 1);

	// 약품 투입 A/B
	for (int i = 0; i < 2; i++) {
		pick[n] = i;
		DFS(cnt + 1, n + 1);
	}
	pick[n] = -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Input();
		if (K == 1) sol = 0;
		else DFS(0, 0);
		cout << "#" << i << " " << sol << "\n";
	}
}
#endif


// 1306 ms -> sol = 0x7f 초기화, DFS 가지치기 cnt > sol
// 1193 ms -> sol = K로 초기화, DFS 가지치기 cnt >= sol (등호 추가)
//  936 ms -> 약품 투입한 행 하나만 백업, 복원하기
#if 0
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int D, W, K;
int arr[13][20]; // 약품 투입할 때마다 전역배열을 바꾼다.
int sol;


void Input() {
	cin >> D >> W >> K;
	for (int i = 0; i < D; i++) {
		for (int j = 0; j < W; j++) {
			cin >> arr[i][j];
		}
	}
	sol = K;
}


// 각 컬럼별로 K개의 행을 슬라이딩 윈도우로 확인
int Check() {
	for (int c = 0; c < W; c++) {
		// 초기 윈도우: [0, K) 의 합을 계산
		int sum = 0;
		for (int r = 0; r < K; r++) sum += arr[r][c];
		if (sum == 0 || sum == K) continue;
		sum -= arr[0][c];

		// 다음 윈도우부터는 끝점 기준 [K, D)
		int r;
		for (r = K; r < D; r++) {
			sum += arr[r][c];

			if (sum == 0 || sum == K) break;
			sum -= arr[r - K + 1][c];
		}

		if (r == D) return 0;
	}
	return 1;
}

// cnt: 현재까지 약품 투입횟수
// n행에 대한 3가지 경우의 수 시도
void DFS(int cnt, int n) {
	if (cnt >= sol) return;

	if (Check()) {
		sol = cnt;
		return;
	}

	if (n == D) return;

	// 현재까지 약품 투입한 상태가 전역배열에 저장되어 있으므로 백업
	// cop를 로컬변수로 선언해야 DFS 스택 종료 후 돌아왔을 때 
	// cop에 DFS 들어가기 전 arr의 상태가 복사되어 있다.
	int cop[20] = { 0, }; // n행만 백업!!
	memcpy(cop, arr + n, sizeof(arr[n])); // 1B 단위로 복사는 문제없다!

	// 약품 투입 A/B
	for (int i = 0; i < 2; i++) {
		fill(arr[n], arr[n] + W, i);
		DFS(cnt + 1, n + 1);
	}
	memcpy(arr + n, cop, sizeof(cop)); // 복원

	// 약품 투입X
	DFS(cnt, n + 1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Input();
		if (K == 1) sol = 0;
		else DFS(0, 0);
		cout << "#" << i << " " << sol << "\n";
	}
}
#endif
