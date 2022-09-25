/**********************************************************/
// [16235] 나무 재테크 (골드3)
// 4ms, 2156KB
// 각각의 칸마다 나이가 동일한 나무그룹 한번에 처리해야 시간초과X
// 각 좌표별 나무 나이를 list 컨테이너에 오름차순으로 저장
// (나이 1인 나무를 맨 앞에 삽입할 거라서 vector보다 list가 적합)
// for문 도중에 제거하고 끝까지 완주해야 하니까, it = erase()로 리턴값 받기!!
/**********************************************************/

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int N, M, K;
int F[10 + 2][10 + 2]; // (1,1)부터 시작. 양분
int A[10 + 2][10 + 2]; // 겨울에 추가되는 양분

struct TREE {
	int age, cnt;
};
list<TREE> T[10 + 2][10 + 2]; // 살아있는 나무들의 나이(오름차순)

int sol; // 살아있는 나무의 수


// 나무를 심는 경우 1) 초기 입력 나무 : age 1~10
//                 2) 가을에 번식    : age = 1
void Add_Tree(int r, int c, int age, int cnt) {
	sol += cnt;
	auto iter = T[r][c].begin();

	// (r,c)의 기존 나무그룹 중 나이 1인 그룹이 있으면 개수만 증가
	// 나무가 없거나, 나이 > 1인 나무그룹만 있으면 맨 앞에 나무그룹 추가
	if ((iter != T[r][c].end()) && (iter->age == 1)) iter->cnt += cnt;
	else T[r][c].insert(iter, { age, cnt });
}


void Input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}

	int r, c, age;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> age;
		Add_Tree(r, c, age, 1);
	}

	// transposed range 에러: cin >> N 하고 fill 하자..!!
	// N = 0인 상태에서 F[1][1] ~ F[0][1] 까지 초기화하니까 에러..
	fill(&F[1][1], &F[N][N + 1], 5); // 초기 양분은 모두 5
}

void SpringSummer() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int dead = 0;

			// 봄: 나무 나이만큼 양분 먹기 or 양분 부족시 죽음
			for (auto it = T[i][j].begin(); it != T[i][j].end(); ) {
				if (F[i][j] >= (it->cnt * it->age)) {
					F[i][j] -= (it->cnt * it->age);
					it->age++;
					it++;
				}
				else {
					// 현재 양분으로 살릴 수 있는 나무만 살리기
					int cnt_live = F[i][j] / it->age; // F[i][j] < age 이면 cnt_live = 0
					int cnt_dead = it->cnt - cnt_live;

					// 죽은 나무들의 나이->양분 증가량을 미리 계산
					dead += (it->age / 2) * cnt_dead;
					sol -= cnt_dead;

					// 일부 생존한 나무들만 양분 먹고 나이 +1
					F[i][j] -= (cnt_live * it->age);
					it->cnt = cnt_live;
					it->age++;

					// 현재 나이 그룹이 전부 죽었거나,
					// 나이가 더 많은 그룹인 경우 it->cnt = 0이다.
					if (it->cnt == 0) it = T[i][j].erase(it); // 죽은 나무 제거
					else it++; // it->cnt > 0 : 현재 나이 그룹 중 일부 나무 생존
				}
			}

			// 여름: 죽은 나무들 나이/2 -> 양분 추가
			if (dead) F[i][j] += dead;
		}
	}
}

void FallWinter() {
	static int dr[] = { -1,-1,-1,0,0,1,1,1 };
	static int dc[] = { -1,0,1,-1,1,-1,0,1 };

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			// 가을: 나이가 5의 배수인 나무 그룹만 번식
			for (auto it = T[r][c].begin(); it != T[r][c].end(); it++) {
				if (it->age % 5) continue;

				for (int i = 0; i < 8; i++) {
					int nr = r + dr[i];
					int nc = c + dc[i];
					if (nr < 1 || nr > N || nc < 1 || nc > N) continue;

					// 나이 5인 나무가 3그루면 it->cnt = 3인 상태
					// 3그루 전부 인접영역에 번식하므로 나이 1인 나무 3그루씩 추가
					Add_Tree(nr, nc, 1, it->cnt);
				}
			}

			// 겨울: 모든 땅에 양분 추가
			F[r][c] += A[r][c];
		}
	}
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();

	for (int y = 1; y <= K; y++) {
		SpringSummer();
		FallWinter();
		if (!sol) break; // 모든 나무가 죽은 경우 중단
	}

	cout << sol << " ";
}
