/*************************************************************/
// [5648] 원자 소멸 시뮬레이션
// 0.5초 단위로 충돌이 일어나므로 x,y좌표 2배해서 정수로 만들기!
// 원자 2개씩 골라서 몇 초에 충돌하는지 구한 뒤 우큐에 넣기
// 과거에 소멸한 원자를 또다시 충돌처리 하지 않도록, 
// 우큐에서 충돌시각이 가장 빠른 것부터 꺼내서 원자별로 가장 빠른 충돌시각을 기록
//
// 우큐 안 쓰면 문제가 되는 반례
// (1,2) 5초 - mint = [5 5 . .]
// (1,3) 4초 - mint = [4 5 4 .] 
//            1,2번 충돌은 취소되어야 하는데 여전히 5초로 기록되어 있음!!
// (2,4) 7초 - 이것이 7초의 충돌로 기록되어야 할 상황이지만 
//            2번의 충돌이 5초라고 기록되어 있는 상황 때문에 기록되지 못함
/**************************************************************/

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;
struct ATOM {
	int x, y, d, k;
}arr[1000];

int mint[1000]; // 충돌시각 최솟값

struct DATA {
    int a, b, t; // 충돌하는 두 원자번호, 충돌시각
};
struct COMP {
    bool operator()(DATA &a, DATA &b) {
        return a.t >  b.t;
    }
};
priority_queue<DATA, vector<DATA>, COMP> pq; // 충돌시각 기준 오름차순


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


void Simulation() {
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
            pq.push({i,j,t}); // 충돌하는 원자쌍 전부 저장
		}
	}
}

int Solve() {
    while (!pq.empty()) {
        DATA cur = pq.top(); pq.pop();
        
        // 기존 충돌 기록이 더 빠른 경우, 이미 소멸한 원자이므로 지금 충돌은 무의미
        if (mint[cur.a] < cur.t || mint[cur.b] < cur.t) continue;
        mint[cur.a] = mint[cur.b] = cur.t;
    }
	
    int sum = 0;
	for (int i = 0; i < N; i++) {
		if (mint[i] < 0x7fffffff) sum += arr[i].k;
	}
	return sum;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Input();
        Simulation();
		cout << "#" << i << " " << Solve() << "\n";
	}
}
