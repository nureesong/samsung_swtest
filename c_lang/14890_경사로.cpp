/************************************/
// [14890] 경사로 (골드3)
// 구현 - 0ms, 2060KB (솔루션 공부)
/************************************/

#include <iostream>
using namespace std;

int N, L;
int arr[100][100];

void Input() {
	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
}

int CheckRow(int r) {
	int last = arr[r][0];
	int cnt = 1;
	int mode = 0;

	for (int c = 1; c < N; c++) {
		if (last == arr[r][c]) {
			if (mode == 0) cnt++;
			else {
				cnt--;
				if (cnt == 0) mode = 0; // 경사로 다 내려옴
			}
		}
		else if (last - arr[r][c] == -1) { // 오르막
			if (mode == 1) return 0;
			if (cnt < L) return 0;
			cnt = 1;
			last = arr[r][c];
		}
		else if (last - arr[r][c] == 1) { // 내리막
			if (mode == 1) return 0;

			cnt = L - 1;
			mode = (cnt == 0) ? 0 : 1;
			last = arr[r][c];
		}
		else return 0;
	}
	return mode == 0;
}

int CheckCol(int c) {
	int last = arr[0][c];
	int cnt = 1;  // 평지 길이 / 경사로 타고 내려온 길이
	int mode = 0; // 경사로를 타고 내려가는 중이면 1, 아니면 0

	for (int r = 1; r < N; r++) {
		if (last == arr[r][c]) {
			if (mode == 1) {  // 경사로 내려오는 중이면 평지 길이 감소
				cnt--;
				if (cnt == 0) mode = 0; // 경사로 다 타고 내려옴
			}
			else cnt++; // 경사로 위에 있지 않으면 평지 길이 증가
		}
		else if (last - arr[r][c] == 1) { // 내리막
			if (mode == 1) return 0; // 경사로 타고 내려오던 중에 또 내리막
			
			cnt = L - 1;
			mode = (cnt == 0) ? 0 : 1;
			last = arr[r][c];
		}
		else if (last - arr[r][c] == -1) { // 오르막 만났을 때
			if (mode == 1) return 0;  // 경사로를 타고 내려오던 중이면 실패
										   
			// 지금까지 평지 길이가 L미만이면 경사로 놓을 수 없음
			if (cnt < L) return 0; 
			cnt = 1; // 현재 높이부터 다시 평지길이 1
			last = arr[r][c];
		}
		else return 0;  // 높이 차 2 이상
	}
	return mode == 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	
	int sum = 0;
	for (int i = 0; i < N; i++) {
		sum += CheckRow(i);
		sum += CheckCol(i);
	}
	cout << sum << "\n";
}
