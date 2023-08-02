// Parametric Search
// M개의 통신탑 사이의 간격이 모두 m 이상이 되는 m을 [1, 양끝 건물 사이 거리] 범위에서 탐색
#include <map>
#include <unordered_map>
using namespace std;

map<int, int> Loc2Id;           // <location, id>
unordered_map<int, int> Id2Loc; // <id, location>

void init(int N, int mId[], int mLocation[]) {
    Loc2Id.clear();
    Id2Loc.clear();
    for (int i = 0; i < N; i++) {
        Loc2Id[mLocation[i]] = mId[i];
        Id2Loc[mId[i]] = mLocation[i];
    }
}

int add(int mId, int mLocation) {
    if (Id2Loc.find(mId) != Id2Loc.end()) Loc2Id.erase(Id2Loc[mId]); // 철거
    Id2Loc[mId] = mLocation;
    Loc2Id[mLocation] = mId;
    return Id2Loc.size();
}

int remove(int mStart, int mEnd) {
    auto it_lb = Loc2Id.lower_bound(mStart);
    auto it_ub = Loc2Id.upper_bound(mEnd);

    for (auto it = it_lb; it != it_ub; it++) {
        Id2Loc.erase(it->second);
    }
    Loc2Id.erase(it_lb, it_ub);
    return Id2Loc.size();
}

int Test(int step, int goal) {
    auto it_end = Loc2Id.end();
    auto it = Loc2Id.begin();
    int cur = it->first; // 간격을 최대화 하려면 첫번째 건물을 무조건 선택해야 함!
    int cnt = 1;

    while (it != it_end) {
        int next = (++it)->first;
        if (cur + step <= next) {
            cur = next;
            cnt++;
            if (cnt >= goal) return 1;
        }
    }
    return 0;
}

// Parametric Search: 통신탑 사이 간격 (1 ~ 양끝 건물 사이 거리)
int install(int M) {
    int s = 1;
    int e = Loc2Id.rbegin()->first - Loc2Id.begin()->first;
    while (s <= e) {
        int m = (s + e) / 2;
        if (Test(m, M)) s = m + 1;
        else e = m - 1;
    }
    return e;
}

//////////////////////////////////////////////////
// *** main.cpp ***
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
extern void init(int N, int mId[], int mLocation[]);
extern int add(int mId, int mLocation);
extern int remove(int mStart, int mEnd);
extern int install(int M);

#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_REMOVE 3
#define CMD_INSTALL 4

static bool run() {
    int q;
    scanf("%d", &q);

    int n, mid, mloc, mstart, mend, m;
    int midArr[100], mlocArr[100];
    int cmd, ans, ret = 0;
    bool okay = false;

    for (int i = 0; i < q; ++i) {
        scanf("%d", &cmd);
        switch (cmd) {
            case CMD_INIT:
                scanf("%d", &n);
                for (int j = 0; j < n; ++j) {
                    scanf("%d %d", &midArr[j], &mlocArr[j]);
                }
                init(n, midArr, mlocArr);
                okay = true;
                break;
            case CMD_ADD:
                scanf("%d %d %d", &mid, &mloc, &ans);
                ret = add(mid, mloc);
                if (ans != ret)
                    okay = false;
                break;
            case CMD_REMOVE:
                scanf("%d %d %d", &mstart, &mend, &ans);
                ret = remove(mstart, mend);
                if (ans != ret)
                    okay = false;
                break;
            case CMD_INSTALL:
                scanf("%d %d", &m, &ans);
                ret = install(m);
                //printf("ret = %d ans = %d\n", ret, ans);
                if (ans != ret)
                    okay = false;
                break;
            default:
                okay = false;
                break;
        }
    }
    return okay;
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
