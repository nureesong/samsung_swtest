#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
using namespace std;

set<string> W;            // 현재 단어 목록
vector<string> V;         // 현재 라운드에서 선택된 단어들
unordered_set<string> TW; // 전체 게임에서 선택된 단어들
set<int> P;               // 살아있는 플레이어 ID

void init(int N, int M, char words[50000][11]) {
    W.clear();
    TW.clear();
    P.clear();
    for (int i = 0; i < M; i++) {
        string word = words[i];
        W.insert(word);
    }
    for (int i = 1; i <= N; i++) P.insert(i);
}

// 한 라운드 진행 (1명 탈락)
int playGame(int playerId, char startChar) {
    auto it_id = P.lower_bound(playerId);
    auto it_end = P.end();
    V.clear();

    while (true) {
        auto it_word = W.lower_bound(string(1, startChar));
        if (it_word == W.end() || (*it_word)[0] != startChar) {
            P.erase(it_id);
            break;
        }
        // 목록에서 사용단어 제거, 시작문자 갱신, 다음 플레이어 찾기
        string word = *it_word;
        startChar = word.back();
        V.push_back(word);
        TW.insert(word);
        W.erase(word);
        it_id++;
        if (it_id == it_end) it_id = P.begin();
    }

    // 사용된 단어 뒤집어서 추가
    for (string w : V) {
        reverse(w.begin(), w.end());
        if (TW.find(w) == TW.end()) W.insert(w);
    }
    return *it_id;
}

////////////////////// *** main.cpp *** /////////////////////
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<string.h>

#define MAX_N 50000
#define MAX_M 50000
#define WORD_MAXLEN 11

extern void init(int N, int M, char words[][WORD_MAXLEN]);
extern int playGame(int playerId, char startCh);

static char words[MAX_M][WORD_MAXLEN];

static bool run() {
    bool ok = true;
    int N, M;
    int gameCnt;

    scanf("%d%d", &N, &M);
    for (int m = 0; m < M; m++) {
        scanf("%s", words[m]);
    }
    init(N, M, words);

    scanf("%d", &gameCnt); // 게임 라운드 수
    for (int i = 0; i < gameCnt; i++) {
        int playerId, ret, ans;
        char startChar[2];
        scanf("%d", &playerId);
        scanf("%s", startChar);
        ret = playGame(playerId, startChar[0]);
        scanf("%d", &ans);
        if (ret != ans) {
            ok = false;
        }
    }
    return ok;
}

int main() {
    setbuf(stdout, NULL);
    //freopen("input.txt", "r", stdin);
    int T, SUCCESS;
    scanf("%d%d", &T, &SUCCESS);
    for (int tc = 1; tc <= T; tc++) {
        int score = run() ? SUCCESS : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}
