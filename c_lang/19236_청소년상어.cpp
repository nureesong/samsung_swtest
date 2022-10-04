/******************************************************/
// [19236] 청소년 상어 (골드2)
// DFS - 상어의 이동 위치 선택
// 상어 이동이 끝나면 물고기 이동 전으로 복원하기 위해 물고기 이동 전에 백업!!
// 14:02 ~ 17:00 -> 3시간 내내 못품ㅠㅠ
// 반시계방향!!! 테케 시뮬 돌리다가 몇 개를 시계로 돌리고 있었음..
// 물고기 정보 map으로 저장하면 안 됨. 백트래킹이 안되거든!!
/*****************************************************/

#include <iostream>
#include <cstring>
using namespace std;

int arr[4][4];

struct FISH {
	int r, c, d;
	int alive;
};
FISH F[17 + 1];  
// 물고기번호(1~16) - 위치, 방향, 생존여부
// 17번: 상어! (상어는 항상 살아있다고 놓기)
int sol; // 먹을 수 있는 물고기 합 최댓값

int dr[] = { -1,-1,0,1,1,1,0,-1 }; // 방향: 0~7번
int dc[] = { 0,-1,-1,-1,0,1,1,1 };

void Input() {
	int n, d;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> n >> d;
			arr[i][j] = n;
			F[n] = { i,j,d-1,1 };
		}
	}
}

int Init() {
	int f = arr[0][0];
	arr[0][0] = 17;
	F[17] = F[f]; // 먹은 물고기의 위치, 방향 그대로 상어한테 전달!
	F[f].alive = 0;
	return f;
}

void MoveFish() {
	for (int n = 1; n <= 16; n++) {
		if (!F[n].alive) continue;

		int r = F[n].r;
		int c = F[n].c;
		int d = F[n].d;

		for (int i = 0; i < 8; i++) {
			int nr = r + dr[d];
			int nc = c + dc[d];
			if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4 || (nr == F[17].r && nc == F[17].c)) {
				d++; d %= 8; // 반시계 45도 회전
				continue;
			}
			
			// 이동 가능
			int other = arr[nr][nc];
			arr[r][c] = other;
			arr[nr][nc] = n;
			F[n] = { nr,nc,d,1 };

			if (other) { // 다른 물고기 있으면 위치 바꾸기
				F[other].r = r;
				F[other].c = c;
			}

			break;
		}
	}
}

void DFS(int sumfish) {
	if (sumfish > sol) sol = sumfish;

	// 현재 상태 백업
	int cop[4][4];
	FISH F_cop[17 + 1];
	memcpy(cop, arr, sizeof(arr));
	memcpy(F_cop, F, sizeof(F));
	
	MoveFish();
	
	// 상어의 이동 경우의 수: 최대 3가지
	// 이동 불가 시(공간 밖/빈칸) for문 종료 후 재귀호출된 곳으로 리턴
	arr[F[17].r][F[17].c] = 0;
	for (int i = 1; i <= 3; i++) {
		int nr = F_cop[17].r + i * dr[F_cop[17].d];
		int nc = F_cop[17].c + i * dc[F_cop[17].d];
		if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4) break;
		if (!arr[nr][nc]) continue;
		
		// 이동 및 물고기 먹기
		int n = arr[nr][nc]; // 먹힐 물고기 번호
		arr[nr][nc] = 17;
		F[17] = F[n]; // 먹은 물고기의 위치, 방향 그대로 복사
		F[n].alive = 0;
		
		DFS(sumfish + n);

		// 현재 먹은 물고기만 복원 (다른 물고기 먹기 위해 한 칸만 바꿔주면 됨)
		// 상어는 다른 물고기 먹을 거라서 복원 안 하는 거 주의
		arr[nr][nc] = n;
		F[n].alive = 1;
	}

	// 상어 이동이 끝나면/불가능하면 아예 물고기 이동 전으로 되돌린다!
	memcpy(arr, cop, sizeof(cop));
	memcpy(F, F_cop, sizeof(F_cop));
	
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	DFS(Init());
	cout << sol << "\n";
}
#endif
