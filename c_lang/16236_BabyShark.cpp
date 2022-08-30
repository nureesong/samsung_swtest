#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int arr[20 + 10][20 + 10];
int vis[20 + 10][20 + 10];

struct DATA {
    int d, r, c;
};
DATA shark;
DATA fish[400 + 10];
int sz = 2, cnt_fish;

queue<DATA> q;

void Input() {
    int tmp;

    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> tmp;

            if (tmp == 9) {
                shark = {0, i, j};
                tmp = 0;
            }
            arr[i][j] = tmp;
        }
    }
}

void Init() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            vis[i][j] = 0;
        }
    }
    for (int i = 0; i < cnt_fish; i++) {
        fish[i] = {0, 0, 0};
    }
    cnt_fish = 0;
}

bool is_valid(int r, int c) {
    return ((r >= 0) && (r < N) && (c >= 0) && (c < N));
}

bool comp(const DATA& a, const DATA& b) {
    if (a.d == b.d && a.r == b.r) return a.c < b.c;
    if (a.d == b.d) return a.r < b.r;
    return a.d < b.d;
}


DATA BFS(DATA shark) {
    DATA tmp;
    int d, r, c;
    int nr, nc;
    int dr[] = {-1, 0, 0, 1}; // 상좌우하
    int dc[] = {0, -1, 1, 0};

    Init();
    q.push(shark);

    while (!q.empty()) {
        tmp = q.front();
        d = tmp.d;
        r = tmp.r;
        c = tmp.c;
        q.pop();
        vis[r][c] = 1;

        for (int i = 0; i < 4; i++) {
            nr = r + dr[i];
            nc = c + dc[i];

            if (is_valid(nr, nc) && vis[nr][nc] == 0 && arr[nr][nc] <= sz) {
                q.push({d+1, nr, nc});
                vis[nr][nc] = 1;

                if (arr[nr][nc] > 0 && arr[nr][nc] < sz) {
                    fish[cnt_fish++] = {d+1, nr, nc};
                }
            }
        }
    }

    if (cnt_fish) {
        sort(fish, fish + cnt_fish, comp);
        return fish[0];
    }
    else return {-1, -1, -1};
}

int Solve() {
    int cnt = 0, total_dist = 0;
    DATA tmp;
    int d, r, c;
    
    do {
        tmp = BFS(shark);
        
        if (tmp.d > 0) {
            if (++cnt == sz) {
                sz++; cnt = 0;
            }
            total_dist += tmp.d;
            arr[tmp.r][tmp.c] = 0;
            shark = {0, tmp.r, tmp.c};
        }
    }
    while (tmp.d > 0);

    return total_dist;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    cout << Solve() << "\n";
}
