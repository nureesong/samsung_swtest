/***************************************/
// [23288] 주사위 굴리기2 (골드3)
// FloodFill, 구현 - 0ms, 2028KB (1시간 32분 소요)
// 주사위를 4방향으로 굴렸을 때의 모양 룩업테이블 활용
// 같은 숫자로 되어있는 인접영역 개수 = FloodFill
/***************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, M, K;
int arr[20][20];
int C[20][20]; // FloodFill 돌려서 같은 수 몇 칸인지 세기

int dr[4] = {-1,0,1,0}; // 북동남서(0123)
int dc[4] = {0,1,0,-1};
int rev[] = {2,3,0,1};

// 현재 주사위 상태: 바닥-천장, 좌-우, 앞-뒤 (마주보는 순서쌍)
int dice[6] = { 6,1,4,3,5,2 };
// 주사위 굴리는 방향에 따른 주사위 모양 룩업테이블
int LUT[4][6] = {
    { 5,4,2,3,0,1 }, // 북
    { 3,2,0,1,4,5 }, // 동
    { 4,5,2,3,1,0 }, // 남
    { 2,3,1,0,4,5 }  // 서
};

struct POS {
    int r, c;
};
queue<POS> q;

void Input() {
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
        }
    }
}

void BFS(int sr, int sc) {
    vector<POS> F;
    int vis[20][20] = {0,};

    int tar = arr[sr][sc];
    int cnt = 1;
    q.push({sr,sc});
    vis[sr][sc] = 1;
    F.push_back({sr,sc});
    
    while (!q.empty()) {
        POS cur = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];
            if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
            if (vis[nr][nc] || arr[nr][nc] != tar) continue;

            q.push({nr,nc});
            vis[nr][nc] = 1;
            F.push_back({nr,nc});
            cnt++;
        }
    }

    for (POS p : F) {
        C[p.r][p.c] = cnt;
    }
}

void FloodFill() {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (C[r][c]) continue;
            BFS(r, c);
        }
    }
}

int Simulation() {
    int score = 0;
    int r = 0, c = 0; // 초기 주사위 위치
    int d = 1;        // 초기 주사위 이동방향 = 동쪽
    
    for (int k = 1; k <= K; k++) {
        // 1. 이동방향으로 주사위 한 칸 굴리기 (벽이면 반대방향으로 굴리기)
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (nr < 0 || nr >= N || nc < 0 || nc >= M) {
            d = rev[d];
            nr = r + dr[d];
            nc = c + dc[d];
        }
        r = nr; c = nc;

        // 주사위 모양 바꾸기
        int tmp[6] = {0,};
        for (int i = 0; i < 6; i++) {
            tmp[i] = dice[LUT[d][i]];
        }
        memcpy(dice, tmp, sizeof(tmp));
        int A = dice[0]; // 주사위 바닥면

        // 2. 점수 계산
        int B = arr[r][c];
        score += B * C[r][c];
        
        // 3. 다음 이동방향 결정하기
        if (A > B) d = (d + 1) % 4;
        else if (A < B) d = (d + 3) % 4;
    }

    return score;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    FloodFill();
    cout << Simulation() << "\n";
}
