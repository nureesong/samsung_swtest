// N: 10의 배수, M = N / 10 
// N*N 공간을 10*10으로 분할하여 2차원 배열로 나타낸다. (한 칸 당 M*M)

#include <vector>
#define LM (20003)
using namespace std;

struct Rect {
    int r, c, sz, id;
};
vector<Rect> map[10][10];

int M;
int P[LM], CNT[LM]; // 부모 사각형, 자식 사각형 개수
int Owner[LM];    // i번 사각형이 누구 소유인지
int playerCnt[3]; // 각 플레이어가 소유한 영역 수
int rectID; // 사각형 번호 부여

int dr[9] = {0,-1,1,0,0,-1,-1,1,1}; // 가운데 > 상하좌우 > 대각선 순서
int dc[9] = {0,0,0,-1,1,-1,1,-1,1};


int Find(int x) {
    if (P[x] == x) return x;
    return P[x] = Find(P[x]);
}

// x번 사각형을 y번 사각형 하위로 통합
void Union(int x, int y, int pid) {
    x = Find(x); // 지금 추가된 사각형 (pid 플레이어의 영역)
    y = Find(y); // 원래 있던 사각형
    if (x == y) return;

    P[x] = y; // y가 루트, x가 자식
    if (Owner[y] != pid) { // y가 상대 플레이어 영역이었다면 뺏어온다
        Owner[y] = pid;
        playerCnt[3 - pid] -= CNT[y];
        playerCnt[pid] += CNT[y];
    }
    CNT[y] += CNT[x]; // x의 자식 사각형 흡수
    CNT[x] = 1;
}

void init(int N, int MM) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            map[i][j].clear();
        }
    }
    for (int i = 0; i < LM; i++) {
        P[i] = i;
        CNT[i] = 1;
    }
    playerCnt[1] = playerCnt[2] = 0;
    rectID = 0;
    M = MM;
}

int Add(int row, int col, int size, int pid) {
    playerCnt[pid]++;
    Owner[rectID] = pid;

    // 지금 사각형 놓인 영역과 인접 8칸을 보면서 겹치는 사각형은 Union
    int r = row / M;
    int c = col / M;
    for (int d = 0; d < 9; d++) {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (nr < 0 || nr >= 10 || nc < 0 || nc >= 10) continue;

        for (auto cur : map[nr][nc]) {
            if (cur.r - size < row && row < cur.r + cur.sz
                && cur.c - size < col && col < cur.c + cur.sz) {
                Union(rectID, cur.id, pid);
            }
        }
    }
    map[r][c].push_back({ row,col,size,rectID++ });
    return playerCnt[pid];
}

int Get(int row, int col) {
    int r = row / M;
    int c = col / M;

    for (int d = 0; d < 9; d++) {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (nr < 0 || nr >= 10 || nc < 0 || nc >= 10) continue;

        for (Rect cur : map[nr][nc]) {
            if (cur.r <= row && row < cur.r + cur.sz
            && cur.c <= col && col < cur.c + cur.sz) {
                return Owner[Find(cur.id)];
            }
        }
    }
    return 0;
}

//////////////////////// *** main.cpp *** /////////////////////////
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>

extern void init(int, int);
extern int Add(int, int, int, int);
extern int Get(int, int);

static unsigned int seed = 5;
static int pseudo_rand(void) {
    seed = seed * 214013 + 2531011;
    return (seed >> 16) & 0x7FFF;
}

static int board_size, area_size, query_cnt;

static int run(int score) {
    scanf("%d%d%d%d", &seed, &board_size, &area_size, &query_cnt);
    init(board_size, area_size);

    for (int q = 0; q < query_cnt; q++) {
        int r, c, size, user_ans, correct_ans;
        printf("\n[Query %d]\n", q);
        for (int i = 1; i <= 2; i++) {
            size = (pseudo_rand() * pseudo_rand()) % area_size + 1;
            r = (pseudo_rand() * pseudo_rand()) % (board_size - size + 1);
            c = (pseudo_rand() * pseudo_rand()) % (board_size - size + 1);
            //printf("i = %d, r = %d, c = %d, sz = %d\n", i, r, c, size);

            user_ans = Add(r, c, size, i);
            scanf("%d", &correct_ans);
            //printf("[Add] %d %d\n", user_ans, correct_ans);
            if (user_ans != correct_ans) score = 0;
        }

        r = (pseudo_rand() * pseudo_rand()) % (board_size);
        c = (pseudo_rand() * pseudo_rand()) % (board_size);
        user_ans = Get(r, c);
        scanf("%d", &correct_ans);
        //printf("[Get] %d %d\n", user_ans, correct_ans);
        if (user_ans != correct_ans) score = 0;
    }
    return score;
}

int main() {
    setbuf(stdout, NULL);
    //freopen("input.txt", "r", stdin);
    int tc, score;
    scanf("%d%d", &tc, &score);
    for (int t = 1; t <= tc; t++) {
        int t_score = run(score);
        printf("#%d %d\n", t, t_score);
    }
    return 0;
}
