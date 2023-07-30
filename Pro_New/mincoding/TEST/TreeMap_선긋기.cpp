#include <map>
using namespace std;

map<int, int> M[101];
// key: 가로선의 y좌표
// value: 가로선이 연결된 x좌표 (x-1, x+1) 둘 중 하나!

void init() {
    for (int i = 0; i < 101; i++) M[i].clear();
}

void add(int x, int y) {
    M[x].insert({ y,x+1 });
    M[x+1].insert({ y,x });
}

void remove(int x, int y) {
    M[x].erase(y);
    M[x+1].erase(y);
}

int getCrossCnt(int ID) {
    if (M[ID].empty()) return 0;

    int x = ID;
    int y = 0;
    int cnt = 0;
    while (y < 1000000000) {
        auto it = M[x].upper_bound(y);
        if (it == M[x].end()) return cnt;  // 현재 아래로 가로선 없는 경우
        x = it->second;
        y = it->first;
        cnt++;
    }
    return cnt;
}

// (x,y)에서 사다리를 거꾸로 탄다. (시작점은 가로선 없음)
int getID(int x, int y) {
    if (M[x].empty()) return x;

    while (y > 0) {
        auto it = M[x].lower_bound(y);
        if (it == M[x].begin()) return x;  // 현재 위로 가로선 없는 경우
        it--;
        x = it->second;
        y = it->first;
    }
    return x;
}

///////////////////////////////////////////////////////////////
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_REMOVE 300
#define CMD_CROSS 400
#define CMD_LINE 500

extern void init();
extern void add(int x, int y);
extern void remove(int x, int y);
extern int getCrossCnt(int lineID);
extern int getID(int x, int y);

/////////////////////////////////////////////////////////////////////////

static bool run() {
    int numQuery;

    int x, y, ID;

    int userAns, ans;

    bool isCorrect = false;

    scanf("%d", &numQuery);

    for (int i = 0; i < numQuery; ++i) {
        int cmd;
        scanf("%d", &cmd);

        switch (cmd) {
            case CMD_INIT:
                init();
                isCorrect = true;
                break;
            case CMD_ADD:
                scanf("%d %d", &x, &y);
                add(x, y);
                break;
            case CMD_REMOVE:
                scanf("%d %d", &x, &y);
                remove(x, y);
                break;
            case CMD_CROSS:
                scanf("%d", &ID);
                userAns = getCrossCnt(ID);
                scanf("%d", &ans);
                //printf("[400] ret = %d ans = %d\n", userAns, ans);
                if (userAns != ans)
                {
                    isCorrect = false;
                }
                break;
            case CMD_LINE:
                scanf("%d %d", &x, &y);
                userAns = getID(x, y);
                scanf("%d", &ans);
                //printf("[500] ret = %d ans = %d\n", userAns, ans);
                if (userAns != ans)
                    isCorrect = false;
                break;
        }
    }
    return isCorrect;
}

int main() {
    //freopen("input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}
