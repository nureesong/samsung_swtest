/*********************************************************/
// [5653] 줄기세포배양
// 구현 - 253ms (솔루션)
// t = x (비활성화), 0 (활성화), -1 (번식), -x (죽음)
// active 변수를 따로 만들지 말고 -x ~ +x 시간으로 놓고 보면
// 활성화 때는 딱히 할 일이 없음. 번식, 죽음만 처리하면 된다.
/*********************************************************/

#include <iostream>
#include <list>
#include <vector>
#include <cstring>
using namespace std;

int N, M, K;
int arr[650][650]; // (K,K)부터 시작

struct CELL {
	int r, c, t; 
};
list<CELL> cell[10 + 1]; // 생명력 수치 큰 순서대로 처리하기 위해 분류!


void Input() {
	memset(arr, 0, sizeof(arr)); // 초기화했어야 함..
	for (int i = 1; i <= 10; i++) cell[i].clear();

	cin >> N >> M >> K;
	for (int i = K; i < K + N; i++) {
		for (int j = K; j < K + M; j++) {
			int n;
			cin >> n;
			if (n) {
				arr[i][j] = n;
				cell[n].push_back({ i,j,n });
			}
		}
	}
}

void Print() {
	for (int r = K-5; r < K+10; r++) {
		for (int c = K-5; c < K+10; c++) {
			cout << arr[r][c] << " ";
		}
		cout << "\n";
	}
}


void ActivateKill() {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };

	for (int x = 10; x >= 1; x--) {
		vector<CELL> ncell; // 번식된 세포들 담기

		auto it = cell[x].begin();
		while (it != cell[x].end()) {
			it->t--;

			// 활성화 1시간 후 -> 번식
			if (it->t == -1) {
				for (int d = 0; d < 4; d++) {
					int nr = it->r + dr[d];
					int nc = it->c + dc[d];
					if (arr[nr][nc]) continue;

					arr[nr][nc] = x;
					ncell.push_back({ nr, nc, x });
				}
			}

			// 활성화 X시간 후 -> 죽음 
			// x = 1 세포들은 번식하고 바로 죽는다! -> 두 조건문 다 만족!)
			if (it->t == -x) { 
				it = cell[x].erase(it); // 제거된 데이터 다음 주소 리턴
			}
			else it++;
		}

		// 번식한 세포들 합치기
		for (CELL c : ncell) {
			cell[c.t].push_back(c);
		}
	}
}


int Simulation() {
	for (int t = 1; t <= K; t++) {
		// 활성 상태 1시간 지난 세포들 번식시키기
		// 활성 상태 X시간 지난 세포들 죽이기
		ActivateKill();
	}

	int cnt = 0;
	for (int x = 1; x <= 10; x++) {
		cnt += cell[x].size();
	}
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Input();
		cout << "#" << i << " " << Simulation() << "\n";
	}
}
