/***********************************************************/
// [21611] 마법사 상어와 블리자드 (골드1)
// 구현 - 12ms, 2188KB (3시간 15분 소요)
// ** 오답노트 **
// 로컬변수 초기화, 배열 인덱스 범위 초과하는지 잘 따져보기
// 구슬이 있는 곳에 얼음이 떨어졌을 때만 제거되는데, 제거된 구슬을 s개로 잘못 생각함
// 구슬 그룹으로 다시 채울 때 전체 칸수 넘어가면 자른다고 했다. 문제 잘 확인!!
/**********************************************************/

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M, Nsq;
struct POS { int r, c; }LUT[49 * 49 + 1];
struct MAGIC { int d, s; }magic[100];
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

// 시뮬레이션 돌릴 때 바뀌는 변수들
int ball[49][49]; // 0:빈칸, 1~3:구슬번호
int cntb;         // 구슬 개수
int sol[3 + 1];   // 번호별 폭발한 구슬 개수


void Input() {
	cin >> N >> M;
	Nsq = N * N;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> ball[r][c];
			if (ball[r][c]) cntb++;
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> magic[i].d >> magic[i].s;
		magic[i].d--;
	}
}

void MakeLUT() {
	int num[49][49] = { 0, }; // 칸 번호 표시 -> 로컬변수 초기화하자!!
	int dir[] = { 3,1,2,0 };  // 우하좌상
	int r = 0, c = -1, k = 0;

	for (int i = Nsq - 1; i >= 1; i--) {
		int nr = r + dr[dir[k]];
		int nc = c + dc[dir[k]];
		if (nr < 0 || nr >= N || nc < 0 || nc >= N || num[nr][nc]) {
			k = (k + 1) % 4;
			nr = r + dr[dir[k]];
			nc = c + dc[dir[k]];
		}
		num[nr][nc] = i;
		LUT[i] = { nr,nc };
		r = nr;
		c = nc;
	}
	LUT[0] = { N / 2,N / 2 };
}

int ThrowIce(int t) {
	int d = magic[t].d;
	int cnt = 0;
	for (int i = 1; i <= magic[t].s; i++) {
		int nr = LUT[0].r + i * dr[d];
		int nc = LUT[0].c + i * dc[d];
		if (ball[nr][nc]) {
			cnt++;
			ball[nr][nc] = 0;
		}
	}
	return cnt;
}

void Move() {
	for (int i = 1; i <= cntb; i++) {
		if (ball[LUT[i].r][LUT[i].c]) continue;

		// i: 빈칸, j: 다음 구슬 위치
		int j = i + 1;
		while (j <= Nsq && !ball[LUT[j].r][LUT[j].c]) j++;
		if (j > Nsq) continue; // 더이상 구슬 없음

		ball[LUT[i].r][LUT[i].c] = ball[LUT[j].r][LUT[j].c];
		ball[LUT[j].r][LUT[j].c] = 0;
	}
}

int Explode() {
	int sum = 0; // 폭발한 구슬 개수 총합
	int last = ball[LUT[1].r][LUT[1].c];
	int cnt = 1;
	// 마지막 구슬이 연속일 수 있으니까 구슬개수+1 까지!!
	for (int i = 2; i <= cntb + 1; i++) {
		int cur = ball[LUT[i].r][LUT[i].c];
		
		if (cur != last) {
			if (cnt >= 4) { // 앞 구슬까지 4개 이상 연속 -> 폭발
				for (int j = 1; j <= cnt; j++) {
					ball[LUT[i - j].r][LUT[i - j].c] = 0;
				}
				sol[last] += cnt;
				sum += cnt;
			}
			last = cur;
			cnt = 1;
		}
		else cnt++;
	}
	return sum;
}

void Arrange() {
	vector<int> tmp;
	int last = ball[LUT[1].r][LUT[1].c];
	int cnt = 1;
	// (마지막 구슬 + 1)칸까지!!
	for (int i = 2; i <= cntb + 1; i++) {
		int cur = ball[LUT[i].r][LUT[i].c];

		if (cur != last) {
			tmp.push_back(cnt);
			tmp.push_back(last);
			last = cur;
			cnt = 1;
		}
		else cnt++;
	}

	memset(ball, 0, sizeof(ball));
	cntb = min((int)tmp.size(), Nsq - 1); // 전체 칸 수보다 크면 자른다!!
	for (int i = 1; i <= cntb; i++) {
		ball[LUT[i].r][LUT[i].c] = tmp[i - 1];
	}
}

int Simulation() {
	for (int t = 0; t < M; t++) {
		// 1. 얼음 던지기, 빈칸 이동
		int ret1 = ThrowIce(t);
		Move();
		cntb -= ret1;

		// 2. 구슬 폭발, 빈칸 이동
		for (;;) {
			int ret2 = Explode();
			if (!ret2) break;
			Move();
			cntb -= ret2;
		}

		// 3. 구슬 그룹 지어서 다시 세팅
		Arrange();
	}
	return sol[1] + 2 * sol[2] + 3 * sol[3];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	MakeLUT();
	cout << Simulation() << "\n";
}
