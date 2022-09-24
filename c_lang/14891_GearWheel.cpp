/**************************************************/
// [14891] 톱니바퀴 (골드5)
// deque은 인덱스로 random access가 가능하다!
// 
// 현재 톱니에서 좌우로 맞닿은 극 확인해서 회전하지 않는 톱니 찾기
// 맞닿은 극: 왼쪽 톱니 2번째, 오른쪽 톱니 6번째
// 반드시 현재 톱니와 인접한 톱니부터 차례로 확인한다!!
/*************************************************/

#include <iostream>
#include <deque>
using namespace std;

deque<int> d[4 + 1]; // 톱니바퀴 4개의 상태(0: N극, 1: S극)

int K;
struct DATA {
	int n, c;
}R[100];

int flag[4 + 1];  // i번 톱니바퀴 회전시킬 방향 저장 (1:시계, -1:반시계)


void Rotate() {
	for (int i = 1; i <= 4; i++) {
		if (flag[i] > 0) {  // 시계방향
			d[i].push_front(d[i].back());
			d[i].pop_back();
		}
		else if (flag[i] < 0) {  // 반시계방향
			d[i].push_back(d[i].front());
			d[i].pop_front();
		}
	}
}

// 4개 톱니바퀴의 회전방향은 2가지 뿐! (1,-1,1,-1) or (-1,1,-1,1)
// 회전시킬 톱니바퀴 번호가 짝홀, 시계/반시계에 따라 둘 중 하나로 세팅
void SetFlag(int cur, int dir) {
	int d1; // 1번 톱니바퀴의 회전방향
	
	// 홀수번호가 시계방향 또는 짝수번호가 반시계방향 -> (1,-1,1,-1)로 세팅
	if ((cur % 2 && dir > 0) || (!(cur % 2) && dir < 0) ) d1 = 1;
	else d1 = -1; // 나머지는 반대방향 (-1,1,-1,1)로 세팅

	for (int i = 1; i <= 4; i++) {
		flag[i] = d1;
		d1 *= -1;
	}
}


int Solve() {
	for (int k = 0; k < K; k++) {
		int cur = R[k].n;
		int dir = R[k].c;

		SetFlag(cur, dir);
		
		// 현재 톱니바퀴부터 왼쪽으로 비교
		for (int i = cur; i > 1; i--) {
			// 오른쪽 톱니가 회전 안하면 왼쪽도 안함
			if (flag[i] == 0) flag[i - 1] = 0;

			// 맞닿은 극이 같을 때 회전 플래그를 끈다.
			if (d[i - 1][2] == d[i][6]) flag[i-1] = 0;
		}

		// 현재 톱니바퀴부터 오른쪽으로 비교
		for (int i = cur; i < 4; i++) {
			// 왼쪽 톱니가 회전 안하면 오른쪽도 안함
			if (flag[i] == 0) flag[i + 1] = 0;

			// 맞닿은 극이 같을 때 회전 플래그를 끈다.
			if (d[i][2] == d[i + 1][6]) flag[i + 1] = 0;
		}

		Rotate(); // 현재 톱니는 무조건 회전한다.
	}
	return d[1][0] + d[2][0] * 2 + d[3][0] * 4 + d[4][0] * 8;
}

void Input() {
	char c;
	for (int n = 1; n <= 4; n++) {
		for (int i = 0; i < 8; i++) {
			cin >> c;
			d[n].push_back(c - '0');
		}
	}

	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> R[i].n >> R[i].c;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Solve() << "\n";
}
