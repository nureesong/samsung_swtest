/* 설국열차 솔루션- */
//#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N, M, J;
int numTrain;
int P[100000], Where[100000];
vector<int> Job[100000]; // 직업별 승객ID 리스트

typedef pair<int, int> PAIR;
priority_queue<PAIR> pq[10]; // { point, -id }
priority_queue<PAIR, vector<PAIR>, greater<PAIR>> rev[10]; // 역박향


void init(int NN, int MM, int JJ, int Point[], int JobID[]) {
    for (int i = 0; i < 10; i++) {
        pq[i] = {};
        rev[i] = {};
    }
    N = NN; M = MM; J = JJ;
    numTrain = N / M;
    if (N % M) numTrain++;

    for (int i = 0; i < N; i++) {
        P[i] = Point[i];
        int tID = i / M; // i번 승객이 탑승한 객차번호
        Where[i] = tID;
        Job[JobID[i]].push_back(i);
        pq[tID].push(make_pair(P[i], i));
        rev[tID].push(make_pair(P[i], i));
    }
}

void destroy() {

}

int update(int uID, int Point) {
    P[uID] += Point;
    // id번 승객의 포인트가 바뀌면서 객차 내 순위 역시 바뀐다.
    // 하지만 PQ에 이미 들어가있는 승객의 정보는 수정 불가
    // 업데이트된 정보를 쑤셔넣는다.
    pq[Where[uID]].push({P[uID], -uID});
    rev[Where[uID]].push({P[uID], -uID});

    return P[uID];
}

int updateByJob(int JobID, int Point) {
    int sum = 0;
    for (int uID : Job[JobID]) {
        sum += update(uID, Point);
    }
    return sum;
}

int move(int num) {
    // 객차별로 포인트 상위 num명,하위 num명 탑승객 선발
    // 객차 이동시킨 후, 이동한 탑승객들의 포인트 합을 리턴
    vector<int> q[numTrain]; // 이동시킬 승객들 임시 저장 대기열

    for (int t = 0; t < numTrain; t++) {
        for (int i = 0; i < num; i++) {
            //상위 num명
            //update에서 전부 쑤셔넣어서 PQ에서 뽑은 num명이 전부 실존하는 승객이 아닐 수 있다.
            while (true) {
                if (t == 0) break; // 0번 객차는 상위num명 뽑지 않는다.

                PAIR cur = pq[t].top(); pq[t].pop();
                int id = -cur.second;
                // 실제로 t번 객차에 존재하는 승객인지 과거에 존재했던 승객인지
                if (Where[id] != t || P[id] != cur.first) continue;
                // 실존한다면 앞 객차로 이동시키기
                q[t-1].push_back(id);
                Where[id] = -1;
                break; // 한 명 빠지면 멈춰
            }

            //하위 num명
            //update에서 전부 쑤셔넣어서 PQ에서 뽑은 num명이 전부 실존하는 승객이 아닐 수 있다.
            while (true) {
                if (t == numTrain-1) break; // 마지막 객차는 하위 num명 뽑지 않는다.

                PAIR cur = rev[t].top(); rev[t].pop();
                int id = -cur.second;
                // 실제로 t번 객차에 존재하는 승객인지 과거에 존재했던 승객인지
                if (Where[id] != t || P[id] != cur.first) continue;
                // 실존한다면 뒷 객차로 이동시키기
                q[t+1].push_back(id);
                Where[id] = -1;
                break; // 한 명 빠지면 멈춰
            }

        }
    }

    int sum = 0;
    for (int t = 0; t < numTrain; t++) {
        for (int id : q[t]) {
            Where[id] = t; // 이제 id 승객은 t번 객차에 존재
            sum += update(id, 0); // 승객이 이동했으므로 객차의 우선순위도 바뀔 수 있다.
        }
    }
    return sum;
}

/////////////////////////////////////////////////
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_DESTROY 200
#define CMD_UPDATE 300
#define CMD_UPDATE_JOB 400
#define CMD_MOVE 500

extern void init(int N, int M, int J, int Point[], int JobID[]);
extern void destroy();
extern int update(int uID, int Point);
extern int updateByJob(int JobID, int Point);
extern int move(int num);
#define MAX_N 100000

static int Point[MAX_N];
static int JobID[MAX_N];

static int run()
{
    int isOK = 0;
    int N;
    int cmd, result, check;

    int mN, mM, mJ;
    int mID, mJobID;
    int mPoint, mNum;

    scanf("%d", &N);

    for (int c = 0; c < N; ++c)
    {
        scanf("%d", &cmd);
        switch (cmd)
        {
            case CMD_INIT:
                scanf("%d %d %d", &mN, &mM, &mJ);
                for (int i = 0; i < mN; i++) scanf("%d", &Point[i]);
                for (int i = 0; i < mN; i++) scanf("%d", &JobID[i]);
                init(mN, mM, mJ, Point, JobID);
                isOK = 1;
                break;

            case CMD_UPDATE:
                scanf("%d %d", &mID, &mPoint);
                result = update(mID, mPoint);
                scanf("%d", &check);

                printf("[300] %d %d\n", result, check);
                if (result != check)
                    isOK = 0;
                break;

            case CMD_UPDATE_JOB:
                scanf("%d %d", &mJobID, &mPoint);
                result = updateByJob(mJobID, mPoint);
                scanf("%d", &check);

                printf("[400] %d %d\n", result, check);
                if (result != check)
                    isOK = 0;
                break;

            case CMD_MOVE:
                scanf("%d", &mNum);
                result = move(mNum);
                scanf("%d", &check);

                printf("[500] %d %d\n", result, check);
                if (result != check)
                    isOK = 0;
                break;

            default:
                isOK = 0;
                break;
        }
    }
    destroy();
    return isOK;
}

int main() {
    setbuf(stdout, NULL);
    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        if (run()) printf("#%d %d\n", tc, MARK);
        else printf("#%d %d\n", tc, 0);
    }
    return 0;
}
