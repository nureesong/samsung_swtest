/**********************************************************/
// [1868] 파핑파핑 지뢰찾기 (D4)
// FloodFill-재귀: 63ms, 13628KB (2시간 50분 소요)
// 
// 주변에 지뢰가 있는 칸을 클릭하면 자기자신 한칸만 오픈되므로
// 8방향 모두 지뢰가 아닌 칸만 클릭하면서 FF 수행한다.
// 총 클릭수 = FF 시작점으로 클릭한 수 + 주변에 지뢰가 있는 칸수
/**********************************************************/

#include <iostream>
#include <cstring>
using namespace std;

int N;
char arr[300][300];
int rem; // 남은 빈칸 수

int dr[] = { -1,-1,-1,0,0,1,1,1 };
int dc[] = { -1,0,1,-1,1,-1,0,1 };


void Input() {
	cin >> N;
	rem = 0; // 초기화...
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == '.') rem++;
		}
	}
}

// 8방향에 지뢰가 있는지 확인
bool IsBomb(int r, int c) {
	for (int i = 0; i < 8; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
		if (arr[nr][nc] == '*') return true;
	}
	return false;
}

// FloodFill 시작 지점은 8방향 다 지뢰가 없는 곳만 입력!
void FloodFill(int sr, int sc) {
	arr[sr][sc] = 'v';
	rem--;

	for (int d = 0; d < 8; d++) {
 		int r = sr + dr[d];
		int c = sc + dc[d];
 		if (r < 0 || r >= N || c < 0 || c >= N) continue;
		if (arr[r][c] == 'v') continue;
 
		if (IsBomb(r, c)) {
			arr[r][c] = 'v';
			rem--;
		}
		else FloodFill(r, c);
	}
}

// 8방향 모두 지뢰가 아닌 빈칸만 클릭하면서 FF 수행
int Simulation() {
	int click = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (arr[i][j] != '.') continue;
			if (IsBomb(i, j)) continue;

			FloodFill(i, j);
			click++;
		}
	}
	return click + rem;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Input();
		cout << '#' << i << " " << Simulation() << '\n';
	}
}
