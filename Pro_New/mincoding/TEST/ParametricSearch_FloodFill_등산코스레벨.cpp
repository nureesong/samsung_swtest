#include <iostream>
#include <deque>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M;
int arr[500][500]; // 해발 높이
int way[500][500]; // 웨이포인트 여부
typedef pair<int,int> PAIR;
int SR, SC, W;  // 웨이포인트 출발위치, 전체 웨이포인트 개수
int vis[500][500];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
deque<PAIR> q;

int FloodFill(int sr, int sc, int m) {
    q.clear();
    memset(vis, 0, sizeof(vis));

    q.push_back({sr,sc});
    vis[sr][sc] = 1;
    int cnt = 1;

    while (!q.empty()) {
        PAIR cur = q.front(); q.pop_front();
        int r = cur.first;
        int c = cur.second;
        int h = arr[r][c];
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
            if (vis[nr][nc] || abs(arr[nr][nc] - h) > m) continue;
            if (way[nr][nc]) cnt++;
            q.push_back({nr,nc});
            vis[nr][nc] = 1;
        }
    }
    return cnt == W;
}

int PS(int s, int e) {
    while (s <= e) {
        int m = (s + e) / 2;
        if (FloodFill(SR, SC, m)) e = m - 1;
        else s = m + 1;
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    int maxH = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int n;
            cin >> n;
            arr[i][j] = n;
            maxH = maxH < n ? n : maxH;
        }
    }
    SR = SC = -1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> way[i][j];
            if (!way[i][j]) continue;
            W++;
            if (SR < 0) {
                SR = i;
                SC = j;
            }
        }
    }
    cout << PS(0, maxH) << "\n";
}
