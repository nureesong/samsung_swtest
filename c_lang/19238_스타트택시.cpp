/******************************************************/
// [19238] 스타트 택시 (골드3)
// BFS & PQ - 4ms
// 19:50 ~ 22:20 (2시간 30분)
//
// ** 주의사항 **  
// PQ를 사용해서 최단거리 승객을 찾는 과정에서 
// for문 안에서 다음 위치가 목표 상태인지 확인해서 틀림.
// pop 했을 때 현위치가 목표 도달인지 확인해야, 
// 여러 개의 목표에 동시에 도달했을 때 최우선순위를 선택하는 것이다!
/*****************************************************/

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, M, R;   // R : 택시 남은 연료
int passenger; // 택시에 탑승 중인 승객 번호
int arr[20 + 2][20 + 2]; // 0: 빈칸, -1:벽, 1~M: 승객 출발지
int vis[20 + 2][20 + 2];

struct POS {
	int r, c;
};
POS T;
POS P[400 + 1][2]; // 승객 출발지, 목적지

struct STATUS {
	int r, c, d;
};
struct COMP {
	bool operator()(STATUS &a, STATUS &b) {
		if (a.d == b.d && a.r == b.r) return a.c > b.c;
		if (a.d == b.d) return a.r > b.r;
		return a.d > b.d;
	}
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;


void Input() {
	cin >> N >> M >> R;
	int n;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> n;
			if (n) arr[i][j] = -1;
		}
	}
	cin >> T.r >> T.c;
	for (int i = 1; i <= M; i++) {
		cin >> P[i][0].r >> P[i][0].c >> P[i][1].r >> P[i][1].c;
		arr[P[i][0].r][P[i][0].c] = i; // 맵에 승객 출발지 표시
	}

	// 테투리에 벽(-1) 두르기
	for (int i = 1; i <= N; i++) {
		arr[i][0] = arr[i][N + 1] = arr[0][i] = arr[N + 1][i] = -1;
	}
}

int BFS(int sr, int sc) {
	static int dr[] = { -1,1,0,0 };
	static int dc[] = { 0,0,-1,1 };
	memset(vis, 0, sizeof(vis));
	pq = {};
	
	pq.push({ sr,sc,0 });
	vis[sr][sc] = 1;

	int dest_r = P[passenger][1].r; // 승객 없으면 0
	int dest_c = P[passenger][1].c;

	while (!pq.empty()) {
		STATUS cur = pq.top(); pq.pop();
		
		if (!passenger && arr[cur.r][cur.c]) { // 승객 발견 -> 연료 충분하면 이동 후 승객 태우기
			if (R < cur.d) return -1;
			T = { cur.r,cur.c };
			R -= cur.d;
			passenger = arr[cur.r][cur.c];
			arr[cur.r][cur.c] = 0;
			return 1;
		}
		else if (passenger && cur.r == dest_r && cur.c == dest_c) { // 목적지 발견 -> 연료 충분하면 이동 후 하차
			if (R < cur.d) return -1;
			T = { cur.r,cur.c };
			passenger = 0;
			R += cur.d;
			return 1;
		}

		int nd = cur.d + 1;
		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (arr[nr][nc] < 0 || vis[nr][nc]) continue; // 벽.재방문
			if (R < nd) continue; // 여기서 return -1 하면 틀림!!!

			pq.push({ nr,nc,nd });
			vis[nr][nc] = 1;
		}
	}
	// 승객 발견X or 목적지 도착 불가 (벽에 막힘, 연료 부족)
	return -1;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Input();

	int ret;
	while (M) {
		// 승객 찾기
		ret = BFS(T.r, T.c);
		if (ret < 0) break;

		// 승객의 목적지로 이동
		ret = BFS(T.r, T.c);
		if (ret < 0) break;
		M--; // 이동 성공
	}

	cout << ((ret < 0) ? -1 : R) << "\n";
}
