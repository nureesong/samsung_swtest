/************************************/
// [17779] 게리맨더링2 (골드3)
// 구현 - 12ms, 2024KB
// 2시간 25분 소요
// 초기화를 잘 하자..!!
/************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int N;
int A[20 + 1][20 + 1];
int S[20 + 1][20 + 1]; // 5구역 경계선 표시
int P[5 + 1];  // 각 구역 인구수
int total_sum; // 전체 인구수

void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
			total_sum += A[i][j];
		}
	}
}

void Section5(int x, int y, int d1, int d2) {
	// 경계선에 5번 선거구 표시
	for (int i = 0; i < d1; i++) { // 우상향 대각선
		S[x + i][y - i] = 5;
		S[x + d2 + 1 + i][y + d2 - 1 - i] = 5;
	}
	for (int i = 0; i < d2; i++) { // 우하향 대각선
		S[x + d1 + i][y - d1 + i] = 5;
		S[x + 1 + i][y + 1 + i] = 5;
	}

	// 경계선 내부 5로 채우기
	for (int i = x + 1; i < x + d1 + d2; i++) {
		// 5가 처음 나오는 열 찾기
		int j = y - d1;
		while (S[i][j] != 5) j++;

		// 그 다음 열부터다시 5가 나올 때까지 5로 채우기
		j++;
		while (S[i][j] != 5) {
			S[i][j] = 5; j++;
		}
	}
}

// 1~4번 선거구 인구수 계산
int Split(int x, int y, int d1, int d2) {
	for (int r = 1; r < x + d1; r++) {
		for (int c = 1; c <= y; c++) {
			if (S[r][c] == 5) break;
			P[1] += A[r][c];
		}
	}
	P[5] -= P[1];

	for (int r = 1; r <= x + d2; r++) {
		for (int c = y + 1; c <= N; c++) {
			if (S[r][c] == 5) continue;
			P[2] += A[r][c];
		}
	}
	P[5] -= P[2];

	for (int r = x + d1; r <= N; r++) {
		for (int c = 1; c < y - d1 + d2; c++) {
			if (S[r][c] == 5) break;
			P[3] += A[r][c];
		}
	}
	P[5] -= P[3];

	for (int r = x + d2 + 1; r <= N; r++) {
		for (int c = y -d1 + d2; c <= N; c++) {
			if (S[r][c] == 5) continue;
			P[4] += A[r][c];
		}
	}
	P[5] -= P[4];

	int maxp = 0, minp = 0x7fffffff;
	for (int i = 1; i <= 5; i++) {
		maxp = (P[i] > maxp) ? P[i] : maxp;
		minp = (P[i] < minp) ? P[i] : minp;
	}
	return maxp - minp;
}

int Solve() {
	int mindiff = 0x7fffffff;

	for (int x = 1; x <= N - 2; x++) {
		for (int y = 2; y <= N - 1; y++) {

			for (int d1 = 1; d1 <= y + 1; d1++) {
				for (int d2 = 1; d2 <= N - y; d2++) {
					if (d1 + d2 > N - x) break;
					
                    memset(S, 0, sizeof(S));
                    memset(P, 0, sizeof(P));
                    P[5] = total_sum;
					
                    Section5(x, y, d1, d2);

					int ret = Split(x, y, d1, d2);
					mindiff = (ret < mindiff) ? ret : mindiff;
				}
			}
			
		}
	}
	return mindiff;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	cout << Solve() << "\n";
}
