#include <iostream>
#include <deque>
#include <cstring>
using namespace std;

int N;
char arr[20+2][20+2];
int vis[20+2][20+2];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
struct STATUS {
    int r, c, d;
};
deque<STATUS> q;
STATUS A[3]; // 민철->소화기 + 불->소화기
STATUS F;

// 출발지에서 모든 소화기까지 이동거리 계산
void BFS(int sr, int sc) {
    q = {};
    q.push_back({ sr,sc,0 });
    memset(vis, 0, sizeof(vis));
    vis[sr][sc] = 1;

    while (!q.empty()) {
        STATUS cur = q.front(); q.pop_front();
        int nd = cur.d + 1;
        for (int d = 0; d < 4; d++) {
            int nr = cur.r + dr[d];
            int nc = cur.c + dc[d];
            if (vis[nr][nc] || arr[nr][nc] == '#' || arr[nr][nc] == '$') continue;
            if (arr[nr][nc] != '_') { // 소화기 발견
                A[arr[nr][nc] - '0'].d += nd;
            }
            q.push_back({ nr,nc,nd });
            vis[nr][nc] = 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N+2; i++) {
        arr[0][i] = '#';
        arr[N+1][i] = '#';
        arr[i][0] = '#';
        arr[i][N+1] = '#';
    }
    int id = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 'A') {
                arr[i][j] = id + '0';
                A[id++] = {i,j,0};
            }
            else if (arr[i][j] == '$') F = {i,j,0};
        }
    }
    int Y, X;
    cin >> Y >> X;

    BFS(Y+1, X+1); // 민철 -> 소화기
    BFS(F.r, F.c); // 불 -> 소화기

    int min = 0x7fffffff;
    while (--id >= 0) {
        min = A[id].d < min ? A[id].d : min;
    }
    cout << min << "\n";
}
