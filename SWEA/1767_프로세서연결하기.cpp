/***********************************************************/
// [1767] 프로세서 연결하기 
// DFS - 중복순열
//
// 14:10 ~ 15:25 (1시간 15분 소요) 
// *시간초과
// 코어 하나 방향 선택할 때마다 원본 맵에 마킹하면서 개수를 세려고 했는데,
// 리턴하고 돌아와서 복원하는 과정에서 남아있는 문제가 해결이 안 됨..
// 모든 코어의 방향 다 선택한 후 전선 안 겹치게 설치 가능한지 확인했다.
//
// *솔루션 - 196ms
// 코어 전원 연결할 때마다 원본 맵에 전선 마킹하고 길이 누적
// 주의: 전원이 연결되지 않는 코어가 존재할 수 있다!!
// 코어 개수가 최대인 게 우선이고, 동률일 때는 전선 길이 최소!!
/**********************************************************/

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N;
int arr[12][12]; // 0:빈칸, 1:코어, 2:전선
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

struct POS {
	int r, c;
};
vector<POS> Core; // 전원 연결되지 않은 코어의 위치
int n_core;    // 초기에 전원 연결되지 않은 코어 개수
int maxcore;   // 전원 연결한 코어 개수 최댓값
int minlen;    // 전선 길이 합의 최솟값


void Input() {
	// Init
	Core.clear();
	maxcore = 0;
	minlen = 0x7fffffff;

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			if (!arr[i][j]) continue;
			if (i == 0 || i == N - 1 || j == 0 || j == N - 1) continue;
			Core.push_back({ i,j });
		}
	}
	n_core = Core.size();
}

// n번째 코어를 d 방향으로 설치한 전선 길이 구하기
int SetCore(int n, int d) {
	int r = Core[n].r + dr[d];
	int c = Core[n].c + dc[d];
	int cnt = 0;

	while (r >= 0 && r < N && c >= 0 && c < N) {
		if (arr[r][c]) return 0; // 다른 코어/전선과 겹치면 불가능
		arr[r][c] = 2;
		cnt++;
		r += dr[d];
		c += dc[d];
	}
	return cnt;
}


// n번째 코어의 전선 연결여부/방향 선택
void DFS(int n, int cnt, int sumlen) {
	// 전원 연결한 코어 개수가 최대이면 전선 길이 합 갱신
	if (cnt > maxcore) {
		maxcore = cnt;
		minlen = sumlen;
		Print();
	}
	else if (cnt == maxcore) { // 동률이면 최솟값인지 확인
		minlen = (sumlen < minlen) ? sumlen : minlen;
		if (sumlen == minlen) Print();
	}
	
	if (n == n_core) return;
	

	// 전원 연결하지 않는 경우
	DFS(n + 1, cnt, sumlen);

	int cop[12][12];
	memcpy(cop, arr, sizeof(arr));

	// 전원 연결하는 경우 (4방향 탐색)
	for (int i = 0; i < 4; i++) {
		int ret = SetCore(n, i);
		if (ret) DFS(n + 1, cnt + 1, sumlen + ret);
		memcpy(arr, cop, sizeof(cop));
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Input();
		DFS(0, 0, 0);
		cout << "#" << i << " " << minlen << "\n";
	}
	return 0;
}
