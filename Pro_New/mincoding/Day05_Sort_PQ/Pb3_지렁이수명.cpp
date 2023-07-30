#include <queue>
#include <unordered_map>
using namespace std;

int Y;
typedef pair<int,int> PAIR;
unordered_map<int, PAIR> hm;  // [id]: { 생존연도,생존여부 }
priority_queue<PAIR> pq;      // { -liveYear,id }

void init() {
    Y = 0;
    hm.clear();
    pq = {};
}

void add(int id, int life) {
    auto itend = hm.end();
    auto it = hm.find(id);
    if (it == itend || (it != itend && !it->second.second)) {
        life += Y;  // 수명 대신 생존이 끝나는 연도를 저장
        hm[id] = make_pair(life, 1);
        pq.push(make_pair(-life, id));
    }
}

int span(int year) {
    Y += year;
    while (!pq.empty()) {
        PAIR cur = pq.top();
        if (-cur.first <= Y) {
            pq.pop();
            hm[cur.second].second = 0;
        }
        else break;
    }
    return pq.size();
}

int getLife(int id) {
    auto it = hm.find(id);
    if (it != hm.end() && hm[id].second) {
        if (hm[id].first > Y) return hm[id].first - Y;
    }
    return -1;
}

/////////////////////////////////////////////////////////////////
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init();
extern void add(int id, int life);
extern int span(int year);
extern int getLife(int id);

#define CMD_ADD 1
#define CMD_SPAN 2
#define CMD_GET_LIFE 3

static bool run() {

    int numQuery;
    int userAns, ans;
    int cmd, id, life, year;
    bool isCorrect = true;

    scanf("%d", &numQuery);

    init();

    for (int q = 0; q < numQuery; q++) {
        scanf("%d", &cmd);
        switch (cmd) {
            case CMD_ADD:
                scanf("%d %d", &id, &life);
                add(id, life);
                //printf("[ADD] size = %d\n", hm.size());
                break;
            case CMD_SPAN:
                scanf("%d", &year);
                userAns = span(year);
                scanf("%d", &ans);
                //printf("[SPAN] ret = %d, ans = %d\n", userAns, ans);
                if (userAns != ans)
                    isCorrect = false;
                break;
            case CMD_GET_LIFE:
                scanf("%d", &id);
                userAns = getLife(id);
                scanf("%d", &ans);
                //printf("[GET] ret = %d, ans = %d\n", userAns, ans);
                if (userAns != ans)
                    isCorrect = false;
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
