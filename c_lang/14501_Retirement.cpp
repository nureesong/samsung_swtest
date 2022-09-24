/***********************************/
// [14501] 퇴사 (실버3) - 삼성 기출
/***********************************/
// BFS + PQ
// 상담 총액이 클수록 우선순위 높다!
// chk[N+1] 에 N일까지 상담한 총액 중 최댓값을 기록한다.
// BFS 상태발전 for문에서 i = N+1 까지 돌림으로써 chk[N+1]에 최댓값이 저장하게 된다.
// (N+1일차 상담이 0일 소요, 비용 0원인 상담이라고 간주)
// [테케 1] 1,4,5일 상담 선택 -> 5,6,7일에 상담하고 8일 아침이 됐을 때가 최댓값이다.
// 
#if 1
#include <iostream>
#include <queue>
using namespace std;

int N;
struct DATA{
    int t, p; // 상담기간, 금액
}arr[15 + 2]; // 1일부터 시작

int chk[15 + 2]; // n일차 아침에 (n-1)일까지 상담한 총액 중 최댓값
struct STATUS{
    int d, sump;
};
struct COMP {
    bool operator()(STATUS &a, STATUS &b) {
        return a.sump < b.sump;
    }
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;


void Input() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i].t >> arr[i].p;
    }
}

int BFS() {
    pq.push({1,0});

    while (!pq.empty()) {
        STATUS cur = pq.top(); pq.pop();

        // 현재 날짜 이후의 모든 상담을 선택할 수 있다.
        // for문 i = N+1까지 돌리는 이유
        // N+1일차는 상담이 없지만, 0일 소요 0원짜리 상담이라고 간주한다.
        // N+1일차 상담 선택시 상담 총액(=현재 총액)의 최댓값을 chk[N+1]에 저장하기 위함!
        for (int i = cur.d; i <= N+1; i++) {
            int nd = i + arr[i].t; // i일차 상담 선택시 t일 소요 후 다음날 아침
            int nsump = cur.sump + arr[i].p;  // i일차 상담 선택시 상담 총액

            if (nd > N + 1) continue;
            if (nsump <= chk[nd]) continue; // 상담 총액이 더 작으면 상태발전X

            pq.push({nd, nsump});
            chk[nd] = nsump;
        }
    }
    return chk[N + 1];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    cout << BFS() << "\n";
    return 0;
}
#endif


// DFS: i일차 상담 선택/미선택에 따른 상태 발전
#if 0
#include <iostream>
using namespace std;

int N;
struct DATA{
    int t, p; // 상담기간, 금액
}arr[15 + 2]; // 1일부터 시작
int sol;

void Input() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i].t >> arr[i].p;
    }
}

// i일차 상담 선택/미선택에 따른 상태 발전
// sump : i일차 아침에 현재까지 상담 총액
void DFS(int i, int sump) {
    if (i > N) {
        sol = (sump > sol) ? sump : sol;
        return;
    }
    
    // 날짜상 i일차 상담 선택 가능한 경우에 상태 발전
    int next = i + arr[i].t;
    if (next <= N+1) DFS(next, sump + arr[i].p);
        
    // i일차 상담 선택X
    DFS(i+1, sump);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    DFS(1, 0);
    cout << sol << "\n";
    return 0;
}
#endif
