#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int N, M;
char arr[200][200];
struct NODE {
    int r, c;
};
vector<NODE> V;
int cnt[2]; // A,B 개체수

deque<NODE> q;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

int FloodFill(int sr, int sc, char target) {
    arr[sr][sc] = '_'; // 방문 시 세포 제거
    q.push_back({ sr,sc });
    int sz = 1;

    while (!q.empty()) {
        NODE cur = q.front(); q.pop_front();
        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];
            if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
            if (arr[nr][nc] != target) continue;
            arr[nr][nc] = '_';
            q.push_back({ nr,nc });
            sz++;
        }
    }
    return sz;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
            if (arr[i][j] != '_') V.push_back({i,j});
        }
    }

    int maxSize = 0;
    for (auto node : V) {
        char cell = arr[node.r][node.c];
        if (cell == '_') continue;
        cnt[cell-'A']++;
        int sz = FloodFill(node.r, node.c, cell);
        maxSize = sz > maxSize ? sz : maxSize;
    }
    cout << cnt[0] << " " << cnt[1] << "\n";
    cout << maxSize << "\n";
}
