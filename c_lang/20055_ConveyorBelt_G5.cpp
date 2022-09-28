/***************************************/
// [20055] 컨베이어 벨트 위의 로봇 (골드5)
// 48ms, 2024KB
// Deque 으로 컨베이어 벨트 회전
// 올리는 위치: 0번, 내리는 위치: N-1번
// 벨트에 먼저 올라간 로봇일수록 내리는 위치에 가깝다!!
// 로봇은 항상 0 ~ N-2번 칸에 위치
/***************************************/

#include <iostream>
#include <deque>
using namespace std;

int N, K;
int drop;      // 로봇 내리는 위치
deque<int> A;  // 내구도 (0번 칸부터 시작!!)
deque<int> R;  // 벨트 위치별 로봇 존재 여부

void Input() {
	cin >> N >> K;
	int a;
	for (int i = 0; i < 2*N; i++) {
		cin >> a;
		A.push_back(a);
		R.push_back(0);
	}
	drop = N - 1;
}

int Solve() {
	int step = 0;
	int cnt_zero = 0;
	
	while (cnt_zero < K) {
		// 1. 컨베이어 벨트 한 칸 회전 (내구도, 로봇) - O(1)
		A.push_front(A.back()); A.pop_back();
		R.push_front(R.back()); R.pop_back();
		if (R[drop]) R[drop] = 0;  // 내리는 위치에 있는 로봇 제거
		

		// 2. 앞번호 로봇부터 이동 - O(N)
		// 벨트에 먼저 올라간 로봇일수록 내리는 위치에 가깝다.
		for (int i = drop - 1; i >= 0; i--) {
			if (!R[i]) continue;

			// 이동하려는 칸의 내구도가 0이거나 로봇 있으면 이동X
			int next = i + 1;
			if (!A[next] || R[next]) continue;

			// 로봇 이동
			A[next]--;
			if (A[next] == 0) cnt_zero++;
			
			// 내리는 위치면 로봇 제거
			if (next == drop) R[next] = 0;
			else R[next] = R[i];
			R[i] = 0;			
		}


		// 3. 올리는 위치 내구도 > 0, 비었으면 로봇 올리기 - O(1)
		if (A[0] && !R[0]) {
			A[0]--;
			if (A[0] == 0) cnt_zero++;
			R[0] = 1;
		}

		step++;
	}

	return step;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	Input();
	cout << Solve() << "\n";
}
