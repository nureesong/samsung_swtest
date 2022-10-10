/*******************************************/
// [2382] 미생물 격리
// 구현 - 1870ms, 13736KB (1시간 20분 소요)
// PQ를 사용하여 미생물 수가 큰 군집부터 이동시킨다.
// 같은 위치에 도착한 다른 군집은 미생물 수가 더 작으므로 병합 후 제거
/*******************************************/

#include <iostream>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

int N, M, K;
int arr[100][100];
int dr[] = {-1,1,0,0}; // 상하좌우
int dc[] = {0,0,-1,1};
int rev[] = {1,0,3,2}; // 하상우좌

struct GROUP {
    int r, c, cnt, d;
};
unordered_map<int, GROUP> G; // key: 그룹ID(1부터), value: 위치,미생물수,이동방향

struct STATUS {
    int id, cnt;
};
struct COMP {
    bool operator()(STATUS &a, STATUS &b) {
        return a.cnt < b.cnt;
    }
};
priority_queue<STATUS, vector<STATUS>, COMP> pq; // 미생물 수가 클수록 우선순위 높다

int sol; // 미생물 수 총합


void Input() {
    sol = 0;
    G.clear();

    cin >> N >> M >> K;
    int r, c, cnt, d;
    for (int i = 1; i <= K; i++) {
        cin >> r >> c >> cnt >> d;
        d--;
        G.insert({i, { r,c,cnt,d }});
        sol += cnt;
    }
}

void Init() {
    memset(arr, 0, sizeof(arr));
    pq = {};
    for (auto it = G.begin(); it != G.end(); it++) {
        pq.push({ it->first, it->second.cnt });
    }
}

void Move() {
    while (!pq.empty()) {
        STATUS cur = pq.top(); pq.pop();
        int d = G[cur.id].d;
        int nr = G[cur.id].r + dr[d];
        int nc = G[cur.id].c + dc[d];
        
        G[cur.id].r = nr;
        G[cur.id].c = nc;

        // 약품 칠해진 셀에 도착
        if (nr == 0 || nr == N-1 || nc == 0 || nc == N-1) {
            G[cur.id].cnt /= 2;
            if (G[cur.id].cnt == 0) G.erase(cur.id);
            G[cur.id].d = rev[d];
            sol -= (cur.cnt + 1) / 2;
            continue;
        }

        // 내부에서 이동하는 경우
        // 다른 군집과 위치가 겹치면, 현재 군집이 더 작으므로 병합시킨 뒤 군집 삭제
        int bigger = arr[nr][nc];
        if (bigger) { // 
            G[bigger].cnt += cur.cnt;
            G.erase(cur.id);
        }
        else arr[nr][nc] = cur.id;
    }
}

void Simulation() {
    for (int t = 1; t <= M; t++) {
        Init();
        Move();
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
        Simulation();
        cout << "#" << i << " " << sol << "\n";
    }
}
