/********************************************/
// [20056] 마법사 상어와 파이어볼 (골드4)
// 구현 - 44ms, 2792KB
// 2시간 30분 
// 입력받을 때 s %= N으로 받아서 s 더할 때 틀림
// map의 키는 변경이 안 된다!!
/*******************************************/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int N, M, K;

struct FIRE {
	int r, c, m, s, d;
};
unordered_map<int, FIRE> F; // 현재 파이어볼 위치,질량,방향,속력
vector<int> arr[50][50];    // 다음에 이동하기 위한 공간

int id;  // 마지막 파이어볼의 번호 (중간에 삭제된 번호 있어서 비연속적)
int sol; // 파이어볼 질량 총합


void Input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= M; i++) {
		cin >> F[i].r >> F[i].c >> F[i].m >> F[i].s >> F[i].d;
		F[i].r--; F[i].c--;
		sol += F[i].m;
	}
	id = M;
}

void Move() {
	static int dr[] = { -1,-1,0,1,1,1,0,-1 };
	static int dc[] = { 0,1,1,1,0,-1,-1,-1 };

	// Init
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arr[i][j].clear();
		}
	}

	for (auto it = F.begin(); it != F.end(); it++) {
		int n = it->first, r = it->second.r, c = it->second.c;
		int d = it->second.d, s = it->second.s;

		s %= N;
		int nr = (r + s * dr[d] + N) % N;
		int nc = (c + s * dc[d] + N) % N;
		arr[nr][nc].push_back(n);
		F[n].r = nr;
		F[n].c = nc;
	}
}

void MergeSplit() {
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			int cnt = arr[r][c].size();
			if (cnt < 2) continue;

			int nm = 0, ns = 0, nd;
			int d_even = 0, d_odd = 0; // 짝수, 홀수 방향 개수 세기

			// 하나로 합치기
			for (int i = 0; i < cnt; i++) {
				int n = arr[r][c][i]; // i번째 파이어볼 번호
				nm += F[n].m;
				ns += F[n].s;

				if (F[n].d % 2) d_odd++;
				else d_even++;

				F.erase(n);
			}
			arr[r][c].clear();
			sol -= nm;

			// 4개로 쪼개기
			nm /= 5;
			if (nm == 0) continue;  // 질량 0이면 소멸
			sol += nm * 4;

			ns /= cnt;
			nd = (d_odd == cnt || d_even == cnt) ? 0 : 1;

			for (int i = 0; i < 4; i++) {
				id++;
				arr[r][c].push_back(id);
				F.insert({ id, {r, c, nm, ns, nd + 2 * i} });
			}

		}
	}
}

void Solve() {
	for (int k = 1; k <= K; k++) {
		Move();
		MergeSplit();
		if (sol == 0) return;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Solve();
	cout << sol << "\n";
}
