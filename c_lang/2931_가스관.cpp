/*************************************************/
// [2931] 가스관 (골드2)
// 구현 - 0ms, 2024KB
// 파이프 모양별 뚫린 방향에 대한 Lookup Table 활용
// 제거된 블록 = 사방을 둘러봤을 때 뚫린 파이프 존재
/************************************************/

#include <iostream>
using namespace std;

int R, C;
int arr[25 + 2][25 + 2]; // 0:빈칸, 1~7:파이프, 8:모스크바/자그레브. (1,1) 시작

int dr[] = { -1,1,0,0 }; // 상하좌우
int dc[] = { 0,0,-1,1 }; // 0 1 2 3
int rev[] = { 1,0,3,2 };

// 파이프 모양별 뚫린 방향
char P[7 + 1] = { '.','1','2','3','4','|','-','+' };
int flag[8 + 1][4] = {
	{}, {0,1,0,1}, {1,0,0,1}, {1,0,1,0}, {0,1,1,0},
	{1,1,0,0}, {0,0,1,1}, {1,1,1,1}, {0,0,0,0},
};
int remflag[4]; // 제거된 블록 주변 파이프를 통해 뚫린 방향 유추


void Input() {
	cin >> R >> C;
	char c;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> c;

			switch (c) {
			case 'M':
			case 'Z':
				arr[i][j] = 8; break;
			case '|':
				arr[i][j] = 5; break;
			case '-':
				arr[i][j] = 6; break;
			case '+':
				arr[i][j] = 7; break;
			case '.':
				arr[i][j] = 0; break;
			default:
				arr[i][j] = c - '0';
			}
		}
	}
}

int CheckOpen(int r, int c) {
	int find = 0;
	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (nr < 1 || nr > R || nc < 1 || nc > C) continue;
		
		int p = arr[nr][nc];
		if (flag[p][rev[i]]) {
			remflag[i] = 1;
			find = 1;
		}
	}
	return find;
}

void SolvePOS() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (arr[i][j]) continue;

			// 빈 칸에서 사방을 둘러보다가 뚫린 파이프 찾으면 제거된 블록!
			if (CheckOpen(i, j)) {
				cout << i << " " << j << " ";
				return;
			}
		}
	}
}

void SolvePipe() {
	// 파이프 종류 찾기
	for (int i = 1; i <= 7; i++) {
		int cnt = 0;
		for (int j = 0; j < 4; j++) {
			if (flag[i][j] == remflag[j]) cnt++;
		}
		if (cnt == 4) {
			cout << P[i] << "\n";
			return;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();

	SolvePOS();
	SolvePipe();
}
