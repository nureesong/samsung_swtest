/*** main.cpp ***/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>

#define MAX_N 50000
#define ABS(a) (((a) < 0) ? -(a) : (a))

extern void playGame(int N);
extern bool checkCards(int indexA, int indexB, int diff);

static int N;
static int cards[MAX_N * 2];
static bool found[MAX_N + 1];
static int foundCnt;
static bool ok;

bool checkCards(int indexA, int indexB, int diff) {
    if (!ok || indexA < 0 || indexA >= N * 2 || indexB < 0 || indexB >= N * 2) {
        ok = false;
        return false;
    }
    if (ABS(cards[indexA] - cards[indexB]) > diff) return false;

    int val = cards[indexA];
    if (diff == 0 && indexA != indexB && !found[val]) {
        foundCnt += 1;
        found[val] = true;
    }
    return true;
}

void init() {
    foundCnt = 0;
    ok = true;
    for (int i = 1; i <= N; i++) {
        found[i] = false;
    }
}

static bool run() {
    scanf("%d", &N);
    for (int i = 0; i < 2 * N; i++) {
        scanf("%d", &cards[i]);
    }
    init();
    playGame(N);
    return ok && foundCnt == N;
}

int main() {
    setbuf(stdout, NULL);
    int T, MARK;
    scanf("%d%d", &T, &MARK);
    for (int tc = 1; tc <= T; tc++) {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}

/////////////////////////////////////////////
/*** user.cpp ***/
#include <iostream>
#include <vector>
using namespace std;

extern bool checkCards(int indexA, int indexB, int diff);

int N2;
vector<int> DAT[50000];
int LUT[3][4] = {{0,1,2,3},
                 {0,2,1,3},
                 {0,3,1,2}};

int FindDiff(int s, int e, int a, int b) {
    int lb = -1;
    while (s <= e) {
        int m = (s + e) / 2;
        if (checkCards(a, b, m)) {
            e = m - 1;
            lb = m;
        }
        else s = m + 1;
    }
    return lb;
}

void playGame(int N) {
    N2 = 2 * N;
    for (int diff = 0; diff < 50000; diff++) DAT[diff].clear();

    // 0번 카드 기준으로 차이값 DAT를 만든다.
    for (int i = 1; i < N2; i++) {
        int d = FindDiff(0, N-1, 0, i); // Parametric Search (lower bound)
        DAT[d].push_back(i);
    }

    checkCards(0, DAT[0][0], 0);
    for (int d = 1; d < N; d++) {
        auto V = DAT[d];
        int sz = V.size();
        if (sz == 2) checkCards(V[0], V[1], 0);
        else if (sz == 4) { // 2,2개씩 매칭시키기
            for (int i = 0; i < 3; i++) {
                if (checkCards(V[LUT[i][0]], V[LUT[i][1]], 0)) {
                    checkCards(V[LUT[i][2]], V[LUT[i][3]], 0);
                    break;
                }
            }
        }
    }
}
