/************************************/
// [15686] 치킨 배달 (골드5)
/************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M; // M: 생존할 치킨집 개수
int arr[50 + 2][50 + 2];

struct POS {
	int r, c;
};
vector<POS> H;  // 집
POS S[13];      // 치킨집
int cnt_store;  // 치킨집 개수
int sol;        // 도시 치킨거리 최솟값
int pick[13];   // 생존 선택한 치킨집 번호

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 1) H.push_back({ i,j });
			else if (arr[i][j] == 2) S[cnt_store++] = { i,j };
		}
	}
	sol = 0x7fffffff;
}

int GetDist() {
	int sumd = 0;
	int cur, min;

	for (POS h : H) {
		min = 0x7fffffff;
		for (int j = 0; j < M; j++) {
			cur = abs(S[pick[j]].r - h.r) + abs(S[pick[j]].c - h.c);
			min = (cur < min) ? cur : min;
		}
		sumd += min;
	}
	return sumd;
}

// s번 치킨집부터 생존할 치킨집 선택 - 조합
// cnt: 현재까지 선택한 생존 치킨집 수
void DFS(int s, int cnt) {
	if (cnt == M) {
		int d = GetDist();
		sol = (d < sol) ? d : sol;
		return;
	}

	for (int i = s; i < cnt_store; i++) {
		pick[cnt] = i;
		DFS(i + 1, cnt + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	DFS(0, 0);
	cout << sol << "\n";
}
