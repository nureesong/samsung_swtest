/**************************************************************/
// [15684] 사다리 조작 (골드3)
// 인터넷 솔루션 참고
// *시간초과 해결방법*
// 양옆이 모두 비어있는(사다리 추가 가능한) 행을 찾아 점프!!
// 양옆에 가로선이 없는 범위에서는 어떤 행에 가로선을 추가해도 성공여부가 똑같다.
// 따라서, 그 범위 중 첫 행에만 가로선 추가하여 성공여부를 확인한다.
// 사다리 조작 실패 시, 양옆이 비어있는 다음 구간을 찾아서 점프한다.
/***************************************************************/

#include <iostream>
using namespace std;

int N, M, H;
int arr[30 + 2][10 + 2]; // 사다리 게임판


void Input() {
	cin >> N >> M >> H;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		arr[a][b] = 1;
	}
}

int Check() {
	for (int i = 1; i <= N; i++) {
		// 1행 i열에서 출발
		int c = i;
		for (int r = 1; r <= H; r++) {
			if (arr[r][c]) c++;
			else if (arr[r][c - 1]) c--;
		}
		if (c != i) return 0;
	}
	return 1;
}


// max: 최대 추가가능한 가로선 개수
// cnt: 현재까지 추가한 가로선 개수
int DFS(int max, int cnt) {
	// 종료조건: 사다리 추가 완료시 사다리 조작 성공 확인
	if (cnt == max) return Check();


	// 세로선 하나 고정해놓고 아래로 훑으면서 사다리 추가 가능한 곳 찾기
	for (int n = 1; n <= N; n++) {
		for (int h = 1; h <= H; h++) {
			// (h,n)에 가로선 추가 가능한지 확인 (양옆에 가로선 있으면 안됨)
			if (arr[h][n] || arr[h][n - 1] || arr[h][n + 1]) continue;

			arr[h][n] = 1; // 가로선 추가
			if (DFS(max, cnt + 1)) return 1;
			arr[h][n] = 0; // 복원
      
			// 양옆에 가로선이 없는 첫 행에 가로선을 추가했을 때 실패임을 확인하고
			// 여기로 내려온 거니까, 양옆이 비어있는 다음 구간을 찾아서 점프한다.
			while (h <= H && !arr[h][n - 1] && !arr[h][n + 1]) h++;  
			// while문 종료 후, h = 좌/우에 가로선이 있는 행
			// for문에서 h++이 되므로 그 다음 행부터 다시 탐색진행.
		}
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	
	int add;
	for (add = 0; add <= 3; add++) {
		if (DFS(add, 0)) break; // 가로선을 add개 추가했을 때 성공여부 
	}
	
	cout << ((add > 3) ? -1 : add) << "\n";
}
