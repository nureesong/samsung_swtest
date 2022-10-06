/*****************************************************************/
// [19237] 어른 상어 (골드2)
// 자료구조, 구현 - 4ms, 3640KB
// 총 5시간 소요ㅠㅠ 
// 1. 상어의 현위치 = 머리, K초간 남아있는 냄새 흔적 = 몸통 으로 생각
//    '뱀' 문제처럼 머리 먼저 이동 후 꼬리 제거하여 전체 길이를 K로 유지
//    초반 (K-1)초 동안은 꼬리가 제거되지 않는다.
// 2. 상어의 상태 3종류
//    살아있음, 쫓겨났지만 냄새는 남아있음, 냄새흔적까지 전부 사라짐
//    -> 상태별로 적절한 자료구조 활용하기!
// 3. 상어 이동 시 겹치면 큰 번호가 제거된다. -> 앞번호부터 이동
//    빈칸을 찾은 앞번호 상어를 원본맵에 표시해버리면,
//    t초일 때와 t+1초일 때 상황이 섞일 수 있다.
//    t초 시작할 때 빈칸이었던 공간을 앞번호 상어가 차지해버리면,
//    뒷번호 상어는 빈칸이 없어서 자기 냄새 위치로 되돌아가는 문제 발생!
//    cop 배열을 따로 만들어 모든 상어를 동시에 이동시키기
// 4. 빈칸이 없어서 자기 냄새 위치로 되돌아가는 경우 때문에,
//    현재 맵 상태에서 t-K초 위치의 냄새를 바로 제거하면 안 된다.
//    같은 위치에 가장 마지막으로 방문한 시각을 기록해두기!!
//    t-K초 이후에 재방문했으면 냄새 제거X
/***************************************************************/

#include <iostream>
#include <map>
#include <deque>
#include <cstring>
using namespace std;

int N, M, K;
int arr[20][20]; // t초일 때 맵 상태. (0:빈칸, 1~M: 상어,냄새)
int cop[20][20]; // 상어가 새로 이동한 위치만 기록 (겹치는지 확인용)
int vis[20][20][400 + 1]; // 0~1000: 상어의 마지막 방문시각 (0x7f: 미방문)

int LUT[400 + 1][4][4]; // 다음 탐색방향 테이블. 상하좌우(0123)

struct SHARK {
	int r, c, d; // 현위치, 방향
};
map<int, SHARK> S; // key: 살아있는 상어 (1 ~ M번) -> 상어 머리
deque<int> out; // 쫓겨났지만 냄새는 남아있는 상어들의 번호

// 최근 K초 간 상어의 이동경로(냄새흔적) (front: t-K초, back: t초)
struct POS {
	int r, c;
};
deque<POS> path[400 + 1]; 


void Input() {
	memset(vis, 0x7f, sizeof(vis));

	cin >> N >> M >> K;
	int n;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> n;
			if (!n) continue;
			arr[i][j] = n;
			S.insert({ n, {i,j,-1} });  // 상어 시작방향 입력받기 전
			path[n].push_back({ i,j }); // 현위치 저장
			vis[i][j][n] = 0;
		}
	}

	// 방향 0123 이 되게 1씩 빼기!!
	for (int n = 1; n <= M; n++) {
		cin >> S[n].d;
		S[n].d--;
	}

	for (int i = 1; i <= M; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				cin >> LUT[i][j][k];
				LUT[i][j][k]--;
			}
		}
	}
}


// 살아있는 상어는 앞번호부터 이동
void MoveShark(int t) {
	memset(cop, 0, sizeof(cop));
	static int dr[] = { -1,1,0,0 }; // 상하좌우
	static int dc[] = { 0,0,-1,1 };

	for (auto it = S.begin(); it != S.end(); it++) {
		int n = it->first;
		int r = it->second.r, c = it->second.c;
		int d = it->second.d;

		// 빈칸 찾기 (우선순위 방향순서)
		// 빈칸 못 찾을 수도 있으니까 자기 냄새 발견하면 킵해놓기
		int i, mine = -1;
		for (i = 0; i < 4; i++) {
			int nd = LUT[n][d][i];
			int nr = r + dr[nd];
			int nc = c + dc[nd];
			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;

			// 빈칸 찾은 경우
			if (!arr[nr][nc]) {
				if (cop[nr][nc]) {  // 앞번호 상어와 겹침
					out.push_back(n); // 지금 상어 쫓아내기!
					M--;
				}
				else {
					it->second = { nr,nc,nd };
					path[n].push_back({ nr,nc });
					cop[nr][nc] = n;
					vis[nr][nc][n] = t;
				}
				break;
			}
			if (arr[nr][nc] == n && mine < 0) mine = nd;
		}
		if (i < 4) continue;

		// 빈칸 못 찾은 경우 -> 자기 냄새 방향으로 후진
		// 현재 상어 냄새가 있는 곳에 다른 상어는 오지 않는다.
		int nr = r + dr[mine];
		int nc = c + dc[mine];
		it->second = { nr,nc,mine };
		path[n].push_back({ nr,nc });
		cop[nr][nc] = n;
		vis[nr][nc][n] = t;
	}

	// 위에 for문 안에서 쫓아내면 iterator 망가짐ㅠㅠ
	for (int n : out) {
		S.erase(n);
	}
}

// t-K초일 때 위치를 제거 (tk: 냄새 제거 시점)
void RemovePath(int tk) {
	// 살아있는 상어
	for (auto it = S.begin(); it != S.end(); it++) {
		int n = it->first;

		POS tar = path[n].front();
		path[n].pop_front();
		int r = tar.r, c = tar.c;
		if (vis[r][c][n] > tk) continue;
		arr[r][c] = 0;
	}

	// 쫓겨난 상어 (쫓겨난 시간 순으로 진행)
	for (int n : out) {
		if (path[n].empty()) out.pop_front();
		else {
			POS tar = path[n].front();
			path[n].pop_front();
			int r = tar.r, c = tar.c;
			if (vis[r][c][n] > tk) continue;
			arr[r][c] = 0;
		}
	}
}

void CopyHead() {
	for (auto it = S.begin(); it != S.end(); it++) {
		int r = it->second.r;
		int c = it->second.c;
		arr[r][c] = cop[r][c];
	}
}

int Solve() {
	int t;
	for (t = 1; t <= 1000; t++) {
		MoveShark(t);
		if (M == 1) return t;

		// K초 전의 냄새 흔적 지우기
		if (t >= K) RemovePath(t - K);

		// 살아있는 상어들의 현위치(cop)를 냄새 제거 완료한 arr에 옮기기
		CopyHead();
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Solve() << "\n";
}
