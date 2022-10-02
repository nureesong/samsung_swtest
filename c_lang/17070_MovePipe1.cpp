/******************************************************/
// [17070] 파이프 옮기기1 (골드5)
// BFS - 652ms, 38288KB
// 09:22 ~ 10:30 (1시간 8분 소요)
// 파이프 모양: 가로, 대각선, 세로 (0,1,2) 
// => 방향순서도 우, 우하, 하 (0,1,2)
// 파이프 모양별 이동시 빈칸을 확인해야 하는 방향에 대한 Lookup Table 활용
// 모두 빈칸이면 파이프의 끝점을 Lookup Table의 0번째 위치로 옮기기
/*****************************************************/
// 왜이렇게 오래 걸리지????

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N;
int arr[16+2][16+2]; // (0,0) 시작. 0:빈칸, 1:벽

// 가로, 대각선, 세로 (0,1,2) -> 방향순서도 우, 우하, 하
int dr[3] = {0,1,1};
int dc[3] = {1,1,0};

// 파이프 모양별 이동시 확인해야 하는 방향 Lookup Table
vector<vector<int>> LUT[3] = {
    { {0}, {1,0,2} },      // 가로 모양 파이프: 우, 우하향으로 이동
    { {0}, {2}, {1,0,2} }, // 대각선 모양 파이프: 우, 하, 우하향으로 이동
    { {2}, {1,0,2} }       // 세로 모양 파이프: 하, 우하향으로 이동
};

struct STATUS {
    int d;   // 파이프 모양
    int r,c; // 파이프 끝점 위치
};
queue<STATUS> q;

// 현재 파이프모양과 위치에서 i 방향으로 이동할 수 있는지 체크
int Check(STATUS cur, int i) {
    for (int d : LUT[cur.d][i]) {
        int nr = cur.r + dr[d];
        int nc = cur.c + dc[d];
        if (nr >= N || nc >= N) return 0;
        if (arr[nr][nc]) return 0;
    }
    return 1;
}

int BFS() {
    int sol = 0;
    q.push({0,0,1});

    while (!q.empty()) {
        STATUS cur = q.front(); q.pop();

        int sz = LUT[cur.d].size();
        for (int i = 0; i < sz; i++) {
            if (!Check(cur, i)) continue;

            int nd = LUT[cur.d][i][0];
            int nr = cur.r + dr[nd];
            int nc = cur.c + dc[nd];

            if (nr == N-1 && nc == N-1) sol++;
            else q.push({nd,nr,nc});
        }
    }
    return sol;
}

void Input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    cout << BFS() << "\n";
}
