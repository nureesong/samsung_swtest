/***********************************************************/
// [21610] 마법사 상어와 비바라기 (골드5)
// 구현 - 4ms, 2176KB (1시간 5분 소요)
// 구름은 한번에 소멸하니까 list말고 vector에 담기
// 벡터를 순회하며 요소값을 변경할 때는 iterator로 for문 돌리기
// 2차원 배열에 구름소멸 위치 표시하면 빠르기 확인 가능
/**********************************************************/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N, M;
int A[50][50];
int flag[50][50]; // 구름 소멸한 곳 표시
int dr[] = { 0,-1,-1,-1,0,1,1,1 };
int dc[] = { -1,-1,0,1,1,1,0,-1 };

struct CLOUD {
	int d, s;
}C[100];

struct POS {
	int r, c;
};
vector<POS> cloud;


void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> C[i].d >> C[i].s;
		C[i].d--;
		C[i].s %= N;
	}
}

void InitCloud() {
	cloud.push_back({ N - 2,0 });
	cloud.push_back({ N - 2,1 });
	cloud.push_back({ N - 1,0 });
	cloud.push_back({ N - 1,1 });
}

void MoveRain(int d, int s) {
	for (auto it = cloud.begin(); it != cloud.end(); it++) {
		it->r = (it->r + s * dr[d] + N) % N;
		it->c = (it->c + s * dc[d] + N) % N;
		A[it->r][it->c]++;
		flag[it->r][it->c] = 1;
	}
}

void CopyWater() {
	for (POS p : cloud) {
		int cnt = 0;
		for (int d = 1; d < 8; d += 2) {
			int nr = p.r + dr[d];
			int nc = p.c + dc[d];
			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
			if (A[nr][nc]) cnt++;
		}
		A[p.r][p.c] += cnt;
	}
	cloud.clear();
}

void AddCloud() {
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (A[r][c] < 2) continue;
			if (flag[r][c]) {
				flag[r][c] = 0; // 초기화
				continue;
			}
			
			A[r][c] -= 2;
			cloud.push_back({ r,c });
		}
	}
}

void Simulation() {
	InitCloud();

	for (int i = 0; i < M; i++) {
		MoveRain(C[i].d, C[i].s);
		CopyWater();
		AddCloud();
	}
}

int GetSum() {
	int sum = 0;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			sum += A[r][c];
		}
	}
	return sum;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();
	Simulation();
	cout << GetSum() << "\n";
}
