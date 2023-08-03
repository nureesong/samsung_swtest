#include <iostream>
#include <deque>
using namespace std;

int H,W,R,C,Y,X,N;
int arr[100][100]; // 0:빈칸 1:붉은색쫄 2:파란색차(목적지)
int dr[8] = {-3,-3,-2,2,3,3,-2,2};
int dc[8] = {-2,2,3,3,-2,2,-3,-3};
struct STATUS {
    int r, c, d;
};
deque<STATUS> q;
int vis[100][100];

int BFS() {
    q.push_back({ R,C,0 });
    vis[R][C] = 1;

    while (!q.empty()) {
        STATUS cur = q.front(); q.pop_front();
        for (int i = 0; i < 8; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];
            if (nr < 0 || nr >= H || nc < 0 || nc >= W) continue;
            if (vis[nr][nc] || arr[nr][nc] == 1) continue;
            int nd = cur.d + 1;
            if (arr[nr][nc] == 2) return nd;
            q.push_back({ nr,nc,nd });
            vis[nr][nc] = 1;
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> H >> W >> R >> C >> Y >> X >> N;
    arr[Y][X] = 2;
    for (int i = 0; i < N; i++) {
        int r, c;
        cin >> r >> c;
        arr[r][c] = 1;
    }
    cout << BFS() << "\n";
}
