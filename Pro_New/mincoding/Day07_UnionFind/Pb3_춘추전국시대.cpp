#include <algorithm>
#define MAXN 26
using namespace std;

int P[MAXN], pop[MAXN]; // 부모국가, 인구 수
int num; // 총 연합국 수

void init(int N, int countries[MAXN]) {
    num = N;
    for (int i = 0; i < N; i++) {
        P[i] = i;
        pop[i] = countries[i];
    }
}

int find_root(int n) {
    if (P[n] == n) return n;
    return P[n] = find_root(P[n]);
}

int alliance(char A, char B) {
    int a = find_root(A - 'A');
    int b = find_root(B - 'A');
    if (a == b) return -1;
    if (!pop[a] || !pop[b]) return -1;

    P[b] = a; // a가 루트
    pop[a] += pop[b];
    pop[b] = 0;
    num--;
    return 1;
}

int war(char A, char B) {
    int a = find_root(A - 'A');
    int b = find_root(B - 'A');
    if (a == b) return -1;
    if (!pop[a] || !pop[b]) return -1;

    if (pop[a] == pop[b]) { // 둘 다 멸망
        pop[a] = pop[b] = 0;
        num -= 2;
        return 1;
    }

    // 문제에서는 인구가 더 많은 국가가 이긴다고 했지만
    // 어차피 하나의 연합이 되므로 항상 A연합군이 이긴걸로 해도 됨!
    P[b] = a;
    pop[a] = abs(pop[a] - pop[b]);
    num--;
    return 1;
}

int getCnt() {
    return num;
}

int getPopCnt(char A) {
    return pop[find_root(A - 'A')];
}


///////////////////////// *** main.cpp *** ///////////////////////////
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#define MAXN 26

extern void init(int N, int countries[MAXN]);
extern int alliance(char A, char B);
extern int war(char A, char B);
extern int getCnt();
extern int getPopCnt(char A);

#define CMD_INIT 1
#define CMD_ALLIANCE 2
#define CMD_WAR 3
#define CMD_GET_CNT 4
#define CMD_GET_POPCNT 5

static bool run() {
    int numQuery, userAns, ans;
    int cmd, N;
    char A, B;
    bool isCorrect = false;
    int countries[MAXN] = { 0, };
    
    scanf("%d", &numQuery);
    for (int q = 0; q < numQuery; q++) {
        scanf("%d", &cmd);
        switch (cmd) {
            case CMD_INIT:
                scanf("%d", &N);
                for (int i = 0; i < N; i++)
                    scanf("%d", &countries[i]);
                init(N, countries);
                isCorrect = true;
                break;
            case CMD_ALLIANCE :
                scanf(" %c %c", &A, &B);
                userAns = alliance(A, B);
                scanf("%d", &ans);
                //printf("[2 연합] ret = %d ans = %d\n", userAns, ans);
                if (userAns != ans) isCorrect = false;
                break;
            case CMD_WAR:
                scanf(" %c %c", &A, &B);
                userAns = war(A, B);
                scanf("%d", &ans);
                //printf("[3 전쟁] ret = %d ans = %d\n", userAns, ans);
                if (userAns != ans) isCorrect = false;
                break;
            case CMD_GET_CNT:
                userAns = getCnt();
                scanf("%d", &ans);
                //printf("[4 전체] ret = %d ans = %d\n", userAns, ans);
                if (userAns != ans) isCorrect = false;
                break;
            case CMD_GET_POPCNT:
                scanf(" %c ", &A);
                userAns = getPopCnt(A);
                scanf("%d", &ans);
                //printf("[5 인구] ret = %d ans = %d\n", userAns, ans);
                if (userAns != ans) isCorrect = false;
                break;
            default :
                isCorrect = false;
                break;
        }
    }
    return isCorrect;
}

int main() {
    setbuf(stdout, NULL);
    // freopen("input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);
    for (int tc = 1; tc <= T; tc++) {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}
