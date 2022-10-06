/*****************************************************/
// [17143] 낚시왕 (골드1)
// 구현 - 12ms ~ 16ms, 2680K
// 공간의 가장자리 도착 시 방향 전환! → 
// 한 칸씩 s번 이동하면 시간초과
// 2(R-1), 2(C-1)칸 이동 시 제자리 → s %= 2(R-1) or 2(C-1)
// 2시간 38분 소요
/****************************************************/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstring>
using namespace std;

int R, C, M;
int arr[100 + 2][100 + 2]; // (1,1)
int flag[100 + 2];    // 컬럼별 상어가 존재하는 최저행 번호 기록
int rev[4] = { 1,0,3,2 };  // 상하우좌 -> 하상좌우

struct SHARK {
	int r, c; // 위치
	int d, s; // 방향, 속력
};
unordered_map<int, SHARK> S; // 크기 - 상어정보
vector<int> smaller;  // 상어 위치 겹칠 시 잡아먹힐 상어 크기 기록


void Input() {
	memset(flag, 0x7f, sizeof(flag));
	cin >> R >> C >> M;
	int r, c, s, d, z;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> s >> d >> z;
		d--;
		if (d <= 1) s %= (2 * (R - 1));
		else s %= (2 * (C - 1));
		
		S.insert({ z, {r,c,d,s} });
		arr[r][c] = z;

		if (r < flag[c]) flag[c] = r;
	}
}

void MoveShark() {
	memset(arr, 0, sizeof(arr));
	memset(flag, 0x7f, sizeof(flag));
	static int dr[] = { -1,1,0,0 }; // 상하우좌
	static int dc[] = { 0,0,1,-1 };
	smaller.clear();

	// 상어 이동 - 겹칠 때 잡아먹기!!
	for (auto it = S.begin(); it != S.end(); it++) {
		int sz = it->first;
		int r = it->second.r, c = it->second.c;
		int d = it->second.d, s = it->second.s;

		// s칸 전진
		// 1~R / 1~C 범위를 넘어가면 반대편으로 뒤집어주기 (16ms)
		if (d <= 1) { // 상하 (행) -> 두 방향 한꺼번에 하느라 if문 3개
			int nr = r + s * dr[d];
			if (nr < 1) {
				nr = 2 - nr; d = rev[d];
			}
			if (nr > R) {
				nr = 2 * R - nr; d = rev[d];
			}
			if (nr < 1) {
				nr = 2 - nr; d = rev[d];
			}
			r = nr;
		}
		else { // 좌우 (열)
			int nc = c + s * dc[d];
			if (nc < 1) {
				nc = 2 - nc; d = rev[d];
			}
			if (nc > C) {
				nc = 2 * C - nc; d = rev[d];
			}
			if (nc < 1) {
				nc = 2 - nc; d = rev[d];
			}
			c = nc;
		}

		// 최대 s = 0 ~ C-1(R-1) => 최대 100번 loop (140ms)
		/*for (int i = 0; i < s; i++) {
			int nr = r + dr[d];
			int nc = c + dc[d];
			if (nr <= 0 || nr > R || nc <= 0 || nc > C) {
				d = rev[d];
				nr = r + dr[d];
				nc = c + dc[d];
			}
			r = nr;
			c = nc;
		}*/

		if (!arr[r][c]) {
			arr[r][c] = sz;
			it->second = { r,c,d,s };
			if (r < flag[c]) flag[c] = r;
		}
		else { // 다른 상어와 겹치면 크기 비교
			int other = arr[r][c];
			if (sz > other) {
				smaller.push_back(other);
				arr[r][c] = sz;
				it->second = { r,c,d,s };
				if (r < flag[c]) flag[c] = r;
			}
			else smaller.push_back(sz); // 잡아먹힐 상어 기록
		}
	}

	// 위의 for문 안에서 크기가 작은 상어를 제거했더니 iterator가 망가짐!
	// 잡아먹힐 상어의 크기를 기록해놨다가 한번에 제거
	for (int s : smaller) {
		S.erase(s); M--;
	}
}

int Solve() {
	int sum = 0;
	for (int c = 1; c <= C; c++) {
		if (!M) break;

		// Find Shark
		int minr = flag[c];
		if (minr < 101) {
			sum += arr[minr][c];
			S.erase(arr[minr][c]);
			M--;
		}

		if (M) MoveShark();
	}
	return sum;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Solve() << "\n";
}
