#define _CRT_SECURE_NO_WARNINGS

/************************************/
// [5648] 원자 소멸 시뮬레이션
//
// 원자 2개씩 비교해서 몇 초에 충돌하는지 구한 뒤 우큐에 넣기
// 우큐에서 충돌시간이 가장 빠른 것부터 꺼내서 처리
/************************************/
#if 1
#include <iostream>
#include <map>
#include <unordered_set>
#include <algorithm>
using namespace std;

int N;
struct ATOM {
	int x, y, d, k;
}arr[1000];

int mint[1000]; // 충돌시각 최솟값

// key: 충돌시각(오름차순), value: 충돌하는 원자들 번호
map<int, unordered_set<int>> rem;


void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i].x >> arr[i].y >> arr[i].d >> arr[i].k;
		arr[i].x *= 2;
		arr[i].y *= 2;
	}
	fill(mint, mint + N, 0x7fffffff);
}

// 두 원자의 충돌(반직선의 교차)여부 및 충돌시각 찾기
int Check(int i, int j) {
	ATOM A = arr[i];
	ATOM B = arr[j];
	int dx = B.x - A.x;
	int dy = B.y - A.y;
	int t = -1; // 충돌시각

	if (A.y == B.y) {  // 수평선
		if (A.d == 3 && B.d == 2) t = dx / 2;
	}
	else if (A.x == B.x) {  // 수직선
		if (A.d == 0 && B.d == 1) t = dy / 2;
	}
	else if (A.y < B.y) { // A->B 우상향 대각선
		if ((A.d == 3 && B.d == 1) || (A.d == 0 && B.d == 2)) {
			if (dx == dy) t = dx;
		}
	}
	else { // A->B 우하향 대각선
		dy = -dy;
		if ((A.d == 3 && B.d == 0) || (A.d == 1 && B.d == 2)) {
			if (dx == dy) t = dx;
		}
	}
	
	return t;
}


int Solve() {
	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			if (arr[i].d == arr[j].d) continue; // 방향이 같으면 절대 충돌X

			// x좌표가 더 작은 원자번호를 a, 큰 원자번호를 b로 두기
			// x좌표가 같으면 y좌표가 더 작은 원자번호를 a로 두기
			int a = i, b = j;
			if (arr[i].x > arr[j].x) {
				a = j; b = i;
			}
			else if (arr[i].x == arr[j].x && arr[i].y > arr[j].y) {
				a = j; b = i;
			}
			
			// 두 원자가 충돌하는지 확인
			int t = Check(a, b);
			if (t == -1) continue; // 충돌X

			// 두 원자가 t초보다 일찍 충돌한 적 있으면 지금 시점에는 소멸된 상태
			
			if (mint[i] < t || mint[j] < t) {

				continue;
			}
			
			// t초가 더 빠르면, 기존에 rem에 기록해놨던 거 삭제해야 함
			rem[mint[i]].erase(i);
			rem[mint[j]].erase(i);
			mint[i] = mint[j] = t;


			// 충돌O: 충돌시각에 원자 번호 추가
			//auto it = rem.find(t);
			//if (it != rem.end()) {  // t초에 충돌한 원자가 없으면 추가
			//	rem.insert({ t, {i,j} });
			//}
			//else {
			//	rem[t].insert(i);
			//	rem[t].insert(j);
			//}


			cout << (char)(i + 'A') << " " << (char)(j + 'A') << "  t = " << t << "\n";

		}
	}

	int sum = 0;
	for (int i = 0; i < N; i++) {
		if (mint[i] < 0x7fffffff) sum += arr[i].k;
		cout << mint[i] << " ";
	}
	cout << "\n\n";
	return sum;
}

//int Solve() {
//	int sum = 0;
//
//	for (auto it = rem.begin(); it != rem.end(); it++) {
//		int t = it->first; // 충돌시각
//
//		for (int n : it->second) {
//			sum += arr[n].k;
//		}
//	}
//	return sum;
//}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("in.txt", "r", stdin);

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Input();
		cout << "#" << i << " " << Solve() << "\n";
	}
}
#endif
