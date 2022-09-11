/**************************************/
// [16234] 인구 이동 (골드5)
// 484ms - BFS 함수 안에서 큐를 매번 생성하니까 오래걸림
// 140ms - 큐를 전역변수로 선언하고, memset으로 초기화
// 날짜가 바뀔 때마다 계속 (0,0)부터 BFS를 돌리는 게 비효율적...
// 날짜 바뀌면 vis도 초기화해야 하는 건 어쩔 수 없는 것 같고
// 전날 연합 맺은 정보로 BFS 탐색 시작하는 좌표를 정할 수 없을까??
/**************************************/

#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

int N, L, R;
int A[50 + 10][50 + 10];
bool vis[50 + 10][50 + 10];

struct STATUS{
    int r, c;
};
queue<STATUS> q; // BFS 함수 안에 있으면 반복 생성으로 오래 걸림
vector<STATUS> nbd;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// (i,j) 나라와 연합을 이룰 수 있는 나라가 있는지 탐색
bool BFS(int i, int j) {
    q.push({i, j});
    nbd.clear();
    nbd.push_back({i, j}); // (i,j)과 연합인 나라들 저장

    vis[i][j] = true;
    int sum = A[i][j];  // 연합국 인구 수

    while (!q.empty()) {
        STATUS cur = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];

            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (vis[nr][nc]) continue;

            // 인구 차이가 L명 이상 R명 이하가 아니면 탐색X
            int diff = abs(A[cur.r][cur.c] - A[nr][nc]);
            if (diff < L || diff > R) continue;
            
            q.push({nr, nc});
            nbd.push_back({nr, nc});
            vis[nr][nc] = true;
            sum += A[nr][nc];
        }

    }

    // (i,j) 나라와 연합을 이룰 나라가 있으면 인구수 계산 후 인구 이동
    if (nbd.size() == 1) return false;

    int newpop = sum / nbd.size();
    for (auto n : nbd) {
        A[n.r][n.c] = newpop;
    }
    return true;
}


int Solve() {
    int day;
    int cntmove; // 각 날짜별 인구 이동 횟수 (연합국 형성 갯수)

    for (day = 0; day < 2000; day++) {
        // Init
        memset(vis, 0, sizeof(vis));
        cntmove = 0;

        // (0, 0) 나라부터 주변 연합국을 탐색한다.
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (vis[i][j]) continue;   // 이미 다른 나라와 연합을 이룬 나라는 패스
                cntmove += BFS(i, j);
            }
        }

        if (cntmove == 0) return day;  // 인구 이동이 일어나지 않으면 종료
    }

    return -1;
}

void Input() {
    cin >> N >> L >> R;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    cout << Solve() << "\n";
}
