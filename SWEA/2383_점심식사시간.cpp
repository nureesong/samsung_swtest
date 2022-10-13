/*****************************************************/
// [2383] 점심 식사시간
// DFS - 22ms, 13568KB (2시간 30분 소요)
// 계단 입구 도착한 시간이 빠른 사람부터 처리하기 위해 PQ 사용
// 강사님 솔루션: list에 저장하고 복사해서 정렬한다. 
//            (복사 안하면 DFS 백트래킹 시 문제있음)
// 모든 데이터를 훑어야 될 때는 벡터/덱/리스트로 접근하는 게 빠른 듯! 
/****************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int N;
int arr[10][10];
struct POS {
    int r, c;
};
vector<POS> S; // 계단 입구 2개
vector<POS> P; // 사람 위치
int cntp;      // 사람 수

int D[10][2]; // 사람 - 계단 사이 거리
int pick[10]; // 사람별 계단 고르기 - 중복순열
int sol;      // 이동완료 최소시간

priority_queue<int, vector<int>, greater<int>> pq[2]; // 경우의 수 완성 후, 사람들이 계단 입구에 도착한 시간순으로 정렬
queue<int> q;  // 계단 내려가고 있는 사람의 이동완료 예정시각 담기 (최대 3명)
 
void Input() {
    S.clear();
    P.clear();
    sol = 0x7fffffff;

    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 1) P.push_back({ i,j });
            else if (arr[i][j]) S.push_back({ i,j });
        }
    }
    cntp = P.size();
}

void CalcDist() {
    for (int i = 0; i < cntp; i++) {
        for (int j = 0; j < 2; j++) {
            D[i][j] = abs(P[i].r - S[j].r) + abs(P[i].c - S[j].c);
        }
    }
}

// n번 계단 사람 이동
int Move(int n) {
    if (pq[n].empty()) return 0;

    q = {}; // 계단 내려가고 있는 사람의 이동완료 예정시각 담기 (최대 3명)
    int k = arr[S[n].r][S[n].c]; // n번 계단의 길이

    while (!pq[n].empty()) {
        int cur = pq[n].top(); pq[n].pop();
        int s = cur + 1; // 계단 입구 도착 1분 후 이동 가능
        
        // 현재 사람이 계단 입구에 도착하기 전에 계단 다 내려간 사람들 제거하기
        while (!q.empty() && s >= q.front()) q.pop();
        
        if (q.size() < 3) q.push(s + k);
        else {
            s = q.front(); // 맨앞 사람 계단 다 내려갈 때까지 기다렸다가, 완료와 동시에 입장
            q.pop();
            q.push(s + k);
        }        
    }

    return q.back();  // 제일 마지막 계단 내려간 사람의 완료시각
}

void DFS(int n) {
    if (n == cntp) {
        pq[0] = {};  // empty일 때까지 돌리니까 항상 비어있을 듯?
        pq[1] = {};  // 가지치기를 해서 안 비어있을지도 몰라..!
        for (int i = 0; i < cntp; i++) {
            int n = pick[i];
            pq[n].push(D[i][n]);
        }

        int t0 = Move(0); // 0번 계단 이동완료 시각
        if (t0 > sol) return; // 가지치기

        int t1 = Move(1); // 1번 계단 이동완료 시각
        int cur = max(t0, t1);
        sol = (cur < sol) ? cur : sol;
        return;
    }

    for (int i = 0; i < 2; i++) {
        pick[n] = i;
        DFS(n + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        Input();
        CalcDist();
        DFS(0);
        cout << "#" << i << " " << sol << "\n";
    }
}
