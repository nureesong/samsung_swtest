/**************************************************/
// [14502] 연구소 (골드4)
// 벽을 3개 세워 안전영역을 최대로 확보하기
// DFS - 빈 칸 중 벽 세울 3칸 선택하는 모든 경우에 대하여 (조합)
// BFS - 모든 바이러스를 동시에 퍼트린 후 남은 안전영역 구하기
/**************************************************/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int arr[8 + 2][8 + 2];  // 0:빈 칸, 1:벽, 2:바이러스(2 ~ 10개) -> 원본 보존!!
int vis[8 + 2][8 + 2];

struct Point {
    int r, c;
};
vector<Point> V;  // 바이러스 좌표 저장
vector<Point> E;  // 빈 칸 좌표 저장
queue<Point> q;

int n_empty;      // 원본 빈 칸 개수
int max_safe = 0; // 최대 안전영역 크기


int BFS() {
    static int dr[] = {-1,1,0,0};
    static int dc[] = {0,0,-1,1};

    // Init
    fill(&vis[0][0], &vis[9][10], 0);
    int n_safe = n_empty - 3; // 벽 3개 세우고 남은 빈 칸 수
    for (auto v : V) q.push(v);

    while (!q.empty()) {
        Point cur = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];

            if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
            if (vis[nr][nc] || arr[nr][nc] != 0) continue;

            q.push({nr,nc});
            vis[nr][nc] = 1;
            n_safe--;
        }
    }   
    return n_safe;
}

// s번째 빈 칸부터 벽 세울 곳 cnt개 선택
void DFS(int s, int cnt) {
    if (cnt == 3) {
        // 벽 3군데 세우기 완료 -> BFS 돌려서 안전영역 크기 구하기
        int ret = BFS();
        if (ret > max_safe) max_safe = ret;
        return;
    }

    for (int i = s; i < n_empty; i++) {
        arr[E[i].r][E[i].c] = 1; // i번째 빈 칸에 벽 세우기
        DFS(i+1, cnt+1);
        arr[E[i].r][E[i].c] = 0; // 빈 칸으로 복원
    }
}
 
void Input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 0) E.push_back({i,j});
            else if (arr[i][j] == 2) V.push_back({i,j});
        }
    }
    n_empty = E.size();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    DFS(0, 0);
    cout << max_safe << "\n";
}
