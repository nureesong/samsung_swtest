#include <string>
#include <map>
#include <unordered_map>
#include <set>
using namespace std;

struct INFO {
    int group, score;
};
unordered_map<int, INFO> D; // [학생ID]: {그룹ID,점수}
map<int, set<int>> G[6];    // [학년&성별 그룹]: map<점수,ID집합>

void init() {
    D.clear();
    for (int i = 0; i < 6; i++) G[i].clear();
}

int GroupID(int grade, string gender) {
    return (grade - 1) * 2 + (gender == "male" ? 0 : 1);
}

int addScore(int id, int grade, char gender[], int score) {
    string str = gender;
    int group = GroupID(grade, str);
    D[id] = { group,score };
    G[group][score].insert(id);
    return *(G[group].rbegin()->second.rbegin()); // 최고점수 중 최대ID (set의 마지막 요소)
}

int removeScore(int id) {
    auto it = D.find(id);
    if (it == D.end()) return 0;
    int group = it->second.group;
    int score = it->second.score;
    D.erase(it);

    if (G[group][score].size() == 1) G[group].erase(score); // key 통째로 제거
    else G[group][score].erase(id); // 해당 ID만 제거

    if (G[group].empty()) return 0;
    return *(G[group].begin()->second).begin(); // 최저점수 중 최저ID (set의 첫번째 요소)
}

int get(int gradeCnt, int grades[], int genderCnt, char genders[][7], int score) {
    int minScore = 0x7fffffff;
    int minID = 0;

    for (int i = 0; i < gradeCnt; i++) {
        int grade = grades[i];
        for (int j = 0; j < genderCnt; j++) {
            string str = genders[j];
            int group = GroupID(grade, str);

            auto it = G[group].lower_bound(score); // 그룹 중 점수가 score 이상 조회
            if (it == G[group].end()) continue;    // score 이상인 점수 없음
            int curScore = it->first;
            if (curScore > minScore) continue;

            int curID = *(it->second.begin());
            if (curScore < minScore) {
                minScore = curScore;
                minID = curID;  // 최저점수 중 최저ID
            } else if (curID < minID) { // 동률이면 ID 비교
                minID = curID;
            }
        }
    }
    return minID;
}


/////////////////////////////////////////////////////////////////////////
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init();
extern int addScore(int id, int grade, char gender[], int score);
extern int removeScore(int id);
extern int get(int gradeCnt, int grade[], int genderCnt, char gender[][7], int score);

#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_REMOVE 300
#define CMD_GET 400

static bool run() {
    int q;
    scanf("%d", &q);

    int id, grade, score;
    char gender[7];
    int cmd, ans, ret;
    bool okay = false;

    for (int i = 0; i < q; ++i) {
        scanf("%d", &cmd);
        switch (cmd) {
            case CMD_INIT:
                init();
                okay = true;
                break;
            case CMD_ADD:
                scanf("%d %d %s %d %d", &id, &grade, gender, &score, &ans);
                ret = addScore(id, grade, gender, score);
                //printf("[ADD] ret = %d ans = %d\n", ret, ans);
                if (ans != ret)
                    okay = false;
                break;
            case CMD_REMOVE:
                scanf("%d %d", &id, &ans);
                ret = removeScore(id);
                //printf("[REM] ret = %d ans = %d\n", ret, ans);
                if (ans != ret)
                    okay = false;
                break;
            case CMD_GET: {
                int gradeCnt, genderCnt;
                int gradeArr[3];
                char genderArr[2][7];
                scanf("%d", &gradeCnt);
                if (gradeCnt == 1) scanf("%d %d", &gradeArr[0], &genderCnt);
                else if (gradeCnt == 2) scanf("%d %d %d", &gradeArr[0], &gradeArr[1], &genderCnt);
                else scanf("%d %d %d %d", &gradeArr[0], &gradeArr[1], &gradeArr[2], &genderCnt);
                
                if (genderCnt == 1) scanf("%s %d %d", genderArr[0], &score, &ans);
                else scanf("%s %s %d %d", genderArr[0], genderArr[1], &score, &ans);

                ret = get(gradeCnt, gradeArr, genderCnt, genderArr, score);
                //printf("[GET] ret = %d ans = %d\n", ret, ans);
                if (ans != ret)
                    okay = false;
                break;
            }

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
