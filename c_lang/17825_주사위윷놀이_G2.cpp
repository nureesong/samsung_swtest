/***********************************************************/
// [17825] 주사위 윷놀이 (골드2)
// 12ms, 2020KB
// 도착 위치에 있는 말은 겹쳐도 되는데, 이거 안 해서 한참 헤맴ㅠㅠ
// 각 위치별 주사위눈 1~5일 때 도착위치 룩업테이블 만들어도 됨
/**********************************************************/

#include <iostream>
using namespace std;

int N, K;
int dice[10];
int pos[4]; // 4개 말의 위치 (시작 = 0)
int sol; // 점수 최댓값
int flag[32 + 1]; // i번 위치에 말 존재여부
// 각 칸마다 부여된 점수
int S[] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,
		   13,16,19,22,24,28,27,26,25,30,35,0 };


int NextPos(int cur, int d) {
	int tmp = cur + d;

	if (cur == 5) {
		if (tmp < 9) tmp += 15;
		else tmp += 20;
	}
	else if (cur == 10) {
		if (tmp < 13) tmp += 13;
		else tmp += 16;
	}
	else if (cur == 15) tmp += 10;
	else if (cur <= 20 && tmp > 20) tmp = 32;
	else if (cur < 24 && tmp > 23) {
		if (tmp == 27) tmp = 20;
		else if (tmp == 28) tmp = 32;
		else tmp += 5;
	}
	else if (cur < 26 && tmp > 25) {
		if (tmp == 29) tmp = 20;
		else if (tmp == 30) tmp = 32;
		else tmp += 3;
	}
	else if (cur < 29 && tmp > 28) {
		if (tmp == 32) tmp = 20;
		else if (tmp > 32) tmp = 32;
	}
	else if (cur < 32 && tmp > 31) {
		if (tmp == 32) tmp = 20;
		else if (tmp > 32) tmp = 32;
	}
	return tmp;
}

// 주사위 굴린 횟수
void DFS(int cnt, int score) {
	if (score > sol) sol = score;
	if (cnt == 10) return;

	// 4개의 말 중에 이동시킬 말 하나 선택
	int d = dice[cnt];
	for (int i = 0; i < 4; i++) {
		int cur = pos[i];
		if (cur == 32) continue; // 도착 칸에 있는 말 선택X

		int next = NextPos(cur, d);
		if (next != 32 && flag[next]) continue; // 다른말 겹치면 이동 못함

		// 이동
		flag[cur] = 0;
		pos[i] = next;
		flag[next] = 1;
		DFS(cnt + 1, score + S[next]);

		// 복원
		flag[next] = 0;
		pos[i] = cur;
		flag[cur] = 1;
	}
}


void Input() {
	for (int i = 0; i < 10; i++) {
		cin >> dice[i];
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
