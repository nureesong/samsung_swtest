#include <map>
#include <string>
#include <cstring>
using namespace std;

map<int, string> tm;

void init() {
    tm.clear();
}

void addExam(int level, char name[100]) {
    auto it = tm.find(level);
    string s = name;
    if (it == tm.end()) tm.insert({ level,s });
}

void getCustomExam(int studyAmount, char name[100]) {
    auto it = tm.upper_bound(studyAmount);
    if (it == tm.begin()) strcpy(name, "noExam");
    else strcpy(name, (--it)->second.c_str());
}

int changeExamLevel(int prev, int after) {
    auto it_prev = tm.find(prev);
    if (it_prev == tm.end()) return -1;
    string name = it_prev->second;

    if (prev < after) {
        for (int i = after; i > prev; i--) {
            if (tm.find(i) == tm.end()) {
                tm.insert({ i,name });
                tm.erase(it_prev);
                return i;
            }
        }
    }
    else {
        for (int i = after; i < prev; i++) {
            if (tm.find(i) == tm.end()) {
                tm.insert({ i,name });
                tm.erase(it_prev);
                return i;
            }
        }
    }
    return prev;
}

void getMaxExam(char name[100]) {
    auto it = tm.end();
    strcpy(name, (--it)->second.c_str());
}

void getMinExam(char name[100]) {
    auto it = tm.begin();
    strcpy(name, it->second.c_str());
}

int countRangeExam(int A, int B) {
    auto it_low = tm.lower_bound(A);
    auto it_up = tm.upper_bound(B);
    return distance(it_low, it_up);
}


/////////////////////////////////////////////////
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<string.h>

#define CMD_INIT 100
#define CMD_ADDEXAM 200
#define CMD_CUSTOMEXAM 300
#define CMD_CHANGE 400
#define CMD_MAXEXAM 500
#define CMD_MINEXAM 600
#define CMD_RANGE 700

extern void init();
extern void addExam(int level, char name[100]);
extern void getCustomExam(int studyAmount, char name[100]);
extern int changeExamLevel(int prevLevel, int afterLevel);
extern void getMaxExam(char name[100]);
extern void getMinExam(char name[100]);
extern int countRangeExam(int A, int B);


int run()
{
    int n;
    scanf("%d", &n);
    int iscorrect = true;
    for (int i = 0; i < n; i++)
    {
        int cmd;
        scanf("%d", &cmd);
        int level,studyAmount,beforeLevel, afterLevel, A, B;
        char name[100] = "";
        char ans_str[100];
        int ans_int, ret;
        switch (cmd)
        {
            case CMD_INIT:
                init();
                break;

            case CMD_ADDEXAM:
                scanf("%d %s", &level, name);
                if (!iscorrect) continue;
                addExam(level, name);
                break;

            case CMD_CUSTOMEXAM:
                scanf("%d", &studyAmount);
                scanf("%s", ans_str);
                if (!iscorrect) continue;
                getCustomExam(studyAmount, name);
                //printf("[300] ret = %s ans = %s\n", name, ans_str);
                if (!strcmp(ans_str, name)) break;
                iscorrect = false;
                break;

            case CMD_CHANGE:
                scanf("%d%d", &level, &afterLevel);
                scanf("%d", &ans_int);
                if (!iscorrect) continue;
                ret = changeExamLevel(level, afterLevel);
                //printf("[400] ret = %d ans = %d\n", ret, ans_int);
                if (ret == ans_int) break;
                iscorrect = false;
                break;

            case CMD_MAXEXAM:
                scanf("%s", ans_str);
                if (!iscorrect) continue;
                getMaxExam(name);
                //printf("[500] ret = %s ans = %s\n", name, ans_str);
                if (!strcmp(name, ans_str)) break;
                iscorrect = false;
                break;

            case CMD_MINEXAM:
                scanf("%s", ans_str);
                if (!iscorrect) continue;
                getMinExam(name);
                //printf("[600] ret = %s ans = %s\n", name, ans_str);
                if (!strcmp(name, ans_str)) break;
                iscorrect = false;
                break;

            case CMD_RANGE:
                scanf("%d %d", &A, &B);
                scanf("%d", &ans_int);
                if (!iscorrect) continue;
                ret = countRangeExam(A, B);
                //printf("[700] ret = %d ans = %d\n", ret, ans_int);
                if (ret == ans_int) break;
                iscorrect = false;
                break;
        }

    }
    return iscorrect;
}

int main() {
    setbuf(stdout, NULL);
    int t, success;
    scanf("%d %d", &t, &success);
    for (int tc = 1; tc <= t; tc++) {
        int score = run() ? success : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}
