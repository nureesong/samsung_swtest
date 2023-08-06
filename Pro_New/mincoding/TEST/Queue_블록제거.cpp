#include <deque>
#include <cstring>
using namespace std;

int R, C;
int total;
struct BLOCK {
    int t, s, e; // 투입시점, 시작~끝 컬럼 (원본)
    int cnt;     // 남은 블록 수
    int removed[10000]; // 제거된 블록의 컬럼번호 (vector보다 배열 훑다가 스킵하는게 더 빠름)
};
deque<BLOCK> q;
int vis[10000]; // 컬럼별 제거여부 표시

void init(int mR, int mC) {
    R = mR; C = mC;
    total = 0;
    q.clear();
}

// 투입 시점이 (현재시각 - R)이하인 블록들은 격자판 벗어나므로 제거
void MoveBlocks(int timestamp) {
    while (!q.empty()) {
        BLOCK block = q.front();
        if (block.t <= timestamp - R) {
            total -= block.cnt;
            q.pop_front();
        }
        else break; // 이후 블록은 더 윗쪽에 있으므로 전부 격자판에 남아있다.
    }
}

int dropBlocks(int timestamp, int col, int len) {
    MoveBlocks(timestamp);
    total += len;
    q.push_back({ timestamp,col,col+len,len,{0,} });
    return total;
}

int removeBlocks(int timestamp) {
    MoveBlocks(timestamp);

    memset(vis, 0, 4*C);
    auto it = q.begin();
    while (it != q.end()) {
        for (int col = it->s; col < it->e; col++) {
            if (it->removed[col]) continue;
            if (vis[col]) continue;
            vis[col] = 1;
            it->removed[col] = 1;
            it->cnt--;
            total--;
        }
        if (!it->cnt) it = q.erase(it);
        else it++;
    }
    return total;
}


////////////////////  main.cpp  ////////////////////
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
void init(int R, int C);
int dropBlocks(int timestamp, int col, int len);
int removeBlocks(int timestamp);

#define CMD_INIT 100
#define CMD_DROP 200
#define CMD_REMOVE 300

static bool run() {
    int query_num;
    scanf("%d", &query_num);
    int ret, ans;
    bool ok = false;
    for (int q = 0; q < query_num; q++) {
        int query;
        scanf("%d", &query);
        if (query == CMD_INIT) {
            int R, C;
            scanf("%d %d", &R, &C);
            init(R, C);
            ok = true;
        }
        else if (query == CMD_DROP) {
            int timestamp, col, len;
            scanf("%d %d %d", &timestamp, &col, &len);
            ret = dropBlocks(timestamp, col, len);
            scanf("%d", &ans);
            //printf("[DROP] ret = %d ans = %d\n\n", ret, ans);
            if (ans != ret) ok = false;
        }
        else if (query == CMD_REMOVE) {
            int timestamp;
            scanf("%d", &timestamp);
            ret = removeBlocks(timestamp);
            scanf("%d", &ans);
            printf("[REMOVE] ret = %d ans = %d\n\n", ret, ans);
            if (ans != ret) ok = false;
        }
    }
    return ok;
}

int main() {
    setbuf(stdout, NULL);
    int T, MARK;
    scanf("%d %d", &T, &MARK);
    for (int tc = 1; tc <= T; tc++) {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}
