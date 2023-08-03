#define MAX_N 100
#include <queue>
#include <deque>
#include <cstring>
using namespace std;

int N;
struct CELL {
    int b, e;  // 박테리아(0:빈칸, 1:A, 2:B), 에너지소비량
}arr[101][101];
int vis[101][101];
int C[3]; // 박테리아 개수

int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
struct STATUS {
    int r, c, e;
};
struct COMP {
    bool operator()(STATUS &a, STATUS &b) {
        if (a.e == b.e) {
            if (a.r == b.r) return a.c > b.c;
            return a.r > b.r;
        }
        return a.e < b.e;
    }
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;

void init(int mN, int Dish[MAX_N][MAX_N]) {
    N = mN;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i+1][j+1] = { 0,Dish[i][j] };
        }
    }
    memset(vis, 0, sizeof(vis));
    C[1] = C[2] = 0;
    pq = {};
}

// 솔루션
#if 1
int dropMedicine(int target, int sr, int sc, int energy) {
    int bacteria = arr[sr][sc].b;
    if (bacteria && bacteria != target) return C[target];
    if (!bacteria) {
        arr[sr][sc].b = target; // 박테리아 생성시 에너지 차감
        energy -= arr[sr][sc].e;
        C[target]++;
    }

    deque<pair<int,int>> q;
    q.push_back({sr,sc});  // 활성화된 박테리아만 담기!
    memset(vis, 0, sizeof(vis));
    vis[sr][sc] = 1;

    pq = {}; // 번식 후보지

    // 번식이 끝날 때까지 활성화 FF 계속 진행
    while (energy > 0) {
        // 1. 활성화 FF
        while (!q.empty()) {
            pair<int,int> cur = q.front(); q.pop_front();
            for (int i = 0; i < 4; i++) {
                int nr = cur.first + dr[i];
                int nc = cur.second + dc[i];
                if (nr < 1 || nr > N || nc < 1 || nc > N) continue;
                if (vis[nr][nc]) continue;
                if (arr[nr][nc].b && arr[nr][nc].b != target) continue; // 다른타입
                if (!arr[nr][nc].b) pq.push({ nr,nc,arr[nr][nc].e }); // 빈칸은 번식 후보지에 추가
                else q.push_back({nr, nc}); // 같은 타입의 박테리아
                vis[nr][nc] = 1; // 빈칸.박테리아 모두 방문처리
            }
        }

        // 2. 최고 우선순위 "한 칸"만 번식 후 바로 활성화
        if (pq.empty()) break; // 번식할 곳 없으면 종료
        STATUS cur = pq.top(); pq.pop();
        arr[cur.r][cur.c].b = target;
        C[target]++;
        energy -= arr[cur.r][cur.c].e;

        q.push_back({ cur.r,cur.c }); // 다시 활성화 FF 진행
    }
    return C[target];
}
#endif

// 번식+활성화 동시에 진행해서 틀린 코드... 로직 못 고칠까...??
#if 0
int dropMedicine(int target, int sr, int sc, int energy) {
    int bacteria = arr[sr][sc].b;
    if (bacteria && bacteria != target) return C[target];
    if (!bacteria) {
        arr[sr][sc].b = target;
        energy -= arr[sr][sc].e;
        C[target]++;
        if (energy < 0) return C[target];
    }

    memset(vis, 0, sizeof(vis));
    pq = {};
    pq.push({ sr,sc,arr[sr][sc].e });
    vis[sr][sc] = 1;

    while (energy > 0 && !pq.empty()) {
        STATUS cur = pq.top(); pq.pop(); // 빈칸/활성화 박테리아
        int r = cur.r, c = cur.c;
        if (!arr[r][c].b) {
            arr[r][c].b = target; // 빈칸이면 번식
            energy -= arr[r][c].e;
            C[target]++;
            if (energy <= 0) return C[target];
        }
        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];
            if (nr < 1 || nr > N || nc < 1 || nc > N) continue;
            if (vis[nr][nc]) continue;
            if (arr[nr][nc].b & arr[nr][nc].b != target) continue;
            pq.push({ nr,nc,arr[nr][nc].e }); // 빈칸/활성화 일단 담아
            vis[nr][nc] = 1;
        }
    }
    return C[target];
}
#endif

int cleanBacteria(int sr, int sc) {
    int tar = arr[sr][sc].b;
    if (!tar) return -1;

    deque<pair<int,int>> q;
    q.push_back({ sr,sc });
    arr[sr][sc].b = 0;
    C[tar]--;

    while (!q.empty()) {
        pair<int,int> cur = q.front(); q.pop_front();
        for (int i = 0; i < 4; i++) {
            int nr = cur.first + dr[i];
            int nc = cur.second + dc[i];
            if (nr < 1 || nr > N || nc < 1 || nc > N) continue;
            if (arr[nr][nc].b != tar) continue;
            q.push_back({ nr,nc });
            arr[nr][nc].b = 0;
            C[tar]--;
        }
    }
    return C[tar];
}

/////////////////////  *** main.cpp ***  ////////////////////
#define _CRT_SECURE_NO_WARNINGS
#ifndef _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#define MAX_N 100

extern void init(int N, int Dish[MAX_N][MAX_N]);
extern int dropMedicine(int targetType, int R, int C, int totalEnergy);
extern int cleanBacteria(int R, int C);

#define CMD_INIT 100
#define CMD_DROP 200
#define CMD_CLEAN 300

static bool run() {
    int query_num;
    scanf("%d", &query_num);
    int ret, ans;
    bool ok = false;
    static int dish[MAX_N][MAX_N];

    for (int q = 0; q < query_num; q++) {
        int query;
        scanf("%d", &query);

        if (query == CMD_INIT) {
            int N;
            scanf("%d", &N);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    scanf("%d", &dish[i][j]);
                }
            }
            init(N, dish);
            ok = true;
        }
        else if (query == CMD_DROP) {
            int targetType;
            int R, C;
            int totalEnergy;
            scanf("%d %d %d %d", &targetType, &R, &C, &totalEnergy);
            ret = dropMedicine(targetType, R, C, totalEnergy);
            scanf("%d", &ans);
            if (ans != ret) ok = false;
        }
        else if (query == CMD_CLEAN) {
            int R, C;
            scanf("%d %d", &R, &C);
            ret = cleanBacteria(R, C);
            scanf("%d", &ans);
            printf("[CLEAN] ret = %d, ans = %d\n", ret, ans);
            if (ans != ret) ok = false;
        }
    }
    return ok;
}

int main() {
    setbuf(stdout, NULL);
    //freopen("input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);
    for (int tc = 1; tc <= T; tc++) {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}
