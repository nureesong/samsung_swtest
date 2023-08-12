#include <vector>
#include <unordered_map>
#include <cstring>
#include <deque>
using namespace std;

int N;
int arr[20][20];
struct NODE {
    int r, c;
};
unordered_map<int, vector<NODE>> hm[6][2];

int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
int vis[20][20];
deque<NODE> q;


void FindH(int sr, int sc, int m) {
    int maxV = 0;
    for (int c = sc; c < sc+m; c++) {
        maxV = arr[sr][c] > maxV ? arr[sr][c] : maxV;
    }
    int key = 0, pow = 1;
    for (int c = sc+m-1; c >= sc; c--) {
        key += (maxV - arr[sr][c]) * pow;
        pow *= 10;
    }
    hm[m][0][key].push_back({sr,sc});
}

void FindV(int sr, int sc, int m) {
    int maxV = 0;
    for (int r = sr; r < sr+m; r++) {
        maxV = arr[r][sc] > maxV ? arr[r][sc] : maxV;
    }
    int key = 0, pow = 1;
    for (int r = sr+m-1; r >= sr; r--) {
        key += (maxV - arr[r][sc]) * pow;
        pow *= 10;
    }
    hm[m][1][key].push_back({sr,sc});
}

void FindAll() {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N-1; c++) {
            FindH(r, c, 2);
            FindV(c, r, 2);
        }
        for (int c = 0; c < N-2; c++) {
            FindH(r, c, 3);
            FindV(c, r, 3);
        }
        for (int c = 0; c < N-3; c++) {
            FindH(r, c, 4);
            FindV(c, r, 4);
        }
        for (int c = 0; c < N-4; c++) {
            FindH(r, c, 5);
            FindV(c, r, 5);
        }
    }
}

void init(int mN, int mMap[20][20]) {
    for (int i = 2; i <= 5; i++) {
        hm[i][0].clear();
        hm[i][1].clear();
    }

    N = mN;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = mMap[i][j];
        }
    }
    FindAll();
}

int count(int M, int mStructure[]) {
    int minV = 5;
    for (int i = 0; i < M; i++) {
        minV = mStructure[i] < minV ? mStructure[i] : minV;
    }
    int key = 0, rev = 0, pow = 1;
    for (int i = 0; i < M; i++) {
        key += (mStructure[i] - minV) * pow;
        rev += (mStructure[M-1-i] - minV) * pow;
        pow *= 10;
    }

    int cnt = 0;
    if (hm[M][0].find(key) != hm[M][0].end()) cnt += hm[M][0][key].size();
    if (hm[M][1].find(key) != hm[M][1].end()) cnt += hm[M][1][key].size();
    if (key != rev) {
        if (hm[M][0].find(rev) != hm[M][0].end()) cnt += hm[M][0][rev].size();
        if (hm[M][1].find(rev) != hm[M][1].end()) cnt += hm[M][1][rev].size();
    }
    return cnt;
}

int FloodFill(int dir) {
    memset(vis, 0, sizeof(vis));
    q.clear();

    if (dir % 2) {
        int col = dir == 1 ? N-1 : 0;
        for (int row = 0; row < N; row++) {
            q.push_back({row,col});
            vis[row][col] = 1;
        }
    }
    else {
        int row = !dir ? 0 : N - 1;
        for (int col = 0; col < N; col++) {
            q.push_back({row, col});
            vis[row][col] = 1;
        }
    }

    int cnt = N;
    while (!q.empty()) {
        NODE cur = q.front(); q.pop_front();
        int h = arr[cur.r][cur.c];
        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (vis[nr][nc] || arr[nr][nc] < h) continue;
            q.push_back({ nr,nc });
            vis[nr][nc] = 1;
            cnt++;
            //if (cnt >= minFF) return minFF; // 가지치기를 했어야 되는데..
        }
    }
    return cnt;
}

int maximize(int M, int mStructure[], int mDir) {
    int minV = 5;
    for (int i = 0; i < M; i++) {
        minV = mStructure[i] < minV ? mStructure[i] : minV;
    }
    int key = 0, rev = 0, pow = 1;
    for (int i = 0; i < M; i++) {
        key += (mStructure[i] - minV) * pow;
        rev += (mStructure[M-1-i] - minV) * pow;
        pow *= 10;
    }

    int minFF = 401;
    for (NODE node : hm[M][0][key]) {
        for (int i = 0; i < M; i++) {
            arr[node.r][node.c + i] += mStructure[i];  // 구조물 설치
        }
        int ret = FloodFill(mDir);
        minFF = ret < minFF ? ret : minFF;
        for (int i = 0; i < M; i++) {
            arr[node.r][node.c + i] -= mStructure[i];  // 구조물 제거
        }
    }
    for (NODE node : hm[M][1][key]) {
        for (int i = 0; i < M; i++) {
            arr[node.r + i][node.c] += mStructure[i];
        }
        int ret = FloodFill(mDir);
        minFF = ret < minFF ? ret : minFF;
        for (int i = 0; i < M; i++) {
            arr[node.r + i][node.c] -= mStructure[i];
        }
    }

    if (key != rev) {
        for (NODE node : hm[M][0][rev]) {
            for (int i = 0; i < M; i++) {
                arr[node.r][node.c + i] += mStructure[i];
            }
            int ret = FloodFill(mDir);
            minFF = ret < minFF ? ret : minFF;
            for (int i = 0; i < M; i++) {
                arr[node.r][node.c + i] -= mStructure[i];
            }
        }
        for (NODE node : hm[M][1][rev]) {
            for (int i = 0; i < M; i++) {
                arr[node.r + i][node.c] += mStructure[i];
            }
            int ret = FloodFill(mDir);
            minFF = ret < minFF ? ret : minFF;
            for (int i = 0; i < M; i++) {
                arr[node.r + i][node.c] -= mStructure[i];
            }
        }
    }
    return N*N - minFF;
}
