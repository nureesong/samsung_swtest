/****************************************************/
// [23289] 온풍기 안녕! (플래5)
// 구현 - 0ms, 2036KB (3시간 53분 소요)
// 온풍기 위치/방향 그리고 벽의 위치는 고정되어 있으므로
// 온풍기에 의해 증가하는 온도 역시 고정적이다. -> 룩업테이블 만들기
/***************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int R, C, K;
int arr[20][20];  // 해당칸의 온도
int LUT[20][20];  // 온풍기에 의해 증가하는 온도량
struct POS {
    int r, c;
};
vector<POS> chk;  // 온도 조사해야 되는 칸

struct HEAT {
    int r, c, d;
};
vector<HEAT> M; // 온풍기 위치, 방향

int W[20][20][4 + 1]; // 현위치 4방향 중 벽으로 막힌 방향에 1 표시
int dr[] = {0,0,0,-1,1}; // 우좌상하(1234)
int dc[] = {0,1,-1,0,0};


void Input() {
    cin >> R >> C >> K;
    int n;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> n;
            if (n == 5) chk.push_back({ i,j });
            else if (n) M.push_back({ i,j,n });
        }
    }
    int w, x, y, t;
    cin >> w;
    for (int i = 0; i < w; i++) {
        cin >> x >> y >> t;
        x--; y--;
        if (t == 0) {
            W[x-1][y][4] = 1; W[x][y][3] = 1; 
        }
        else {
            W[x][y][1] = 1; W[x][y+1][2] = 1;
        }
    }
}

void Print(int (*a)[20]) {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void MakeLUT(int sr, int sc, int d) {
    int tmp[20][20] = {0,};
    int x = sr + dr[d];
    int y = sc + dc[d];
    tmp[x][y] = 5;

    int n = 4;
    int lb, ub, limit;
    if (d == 1) { // 우
        lb = ub = x;
        limit = min(y + 3, C-2);
        for (int c = y; c <= limit; c++) {
            for (int r = lb; r <= ub; r++) {
                if (tmp[r][c] == 0) continue; // 이전에 바람이 오지 못한 곳

                // 직진, 상하 대각선 총 3방향 전부 체크
                if (!W[r][c][d]) tmp[r][c+1] = n;
                if (r > 0 && !W[r][c][3] && !W[r-1][c][d]) tmp[r-1][c+1] = n;
                if (r < R-1 && !W[r][c][4] && !W[r+1][c][d]) tmp[r+1][c+1] = n;
            }
            lb = max(lb-1, 0);
            ub = min(ub+1, R-1);
            n--;
        }
    }
    else if (d == 2) { // 좌
        lb = ub = x;
        limit = max(y - 3, 1);
        for (int c = y; c >= limit; c--) {
            for (int r = lb; r <= ub; r++) {
                if (tmp[r][c] == 0) continue; // 이전에 바람이 오지 못한 곳

                // 직진, 상하 대각선 총 3방향 전부 체크
                if (!W[r][c][d]) tmp[r][c-1] = n;
                if (r > 0 && !W[r][c][3] && !W[r-1][c][d]) tmp[r-1][c-1] = n;
                if (r < R-1 && !W[r][c][4] && !W[r+1][c][d]) tmp[r+1][c-1] = n;
            }
            lb = max(lb-1, 0);
            ub = min(ub+1, R-1);
            n--;
        }
    }
    else if (d == 3) { // 상
        lb = ub = y;
        limit = max(x - 3, 1);
        for (int r = x; r >= limit; r--) {
            for (int c = lb; c <= ub; c++) {
                if (tmp[r][c] == 0) continue; // 이전에 바람이 오지 못한 곳

                // 직진, 좌우 대각선 총 3방향 전부 체크
                if (!W[r][c][d]) tmp[r-1][c] = n;
                if (c > 0 && !W[r][c][2] && !W[r][c-1][d]) tmp[r-1][c-1] = n;
                if (c < C-1 && !W[r][c][1] && !W[r][c+1][d]) tmp[r-1][c+1] = n;
            }
            lb = max(lb-1, 0);
            ub = min(ub+1, C-1);
            n--;
        }
    }
    else { // 하
        lb = ub = y;
        limit = min(x + 3, R-2);
        for (int r = x; r <= limit; r++) {
            for (int c = lb; c <= ub; c++) {
                if (tmp[r][c] == 0) continue; // 이전에 바람이 오지 못한 곳

                // 직진, 좌우 대각선 총 3방향 전부 체크
                if (!W[r][c][d]) tmp[r+1][c] = n;
                if (c > 0 && !W[r][c][2] && !W[r][c-1][d]) tmp[r+1][c-1] = n;
                if (c < C-1 && !W[r][c][1] && !W[r][c+1][d]) tmp[r+1][c+1] = n;
            }
            lb = max(lb-1, 0);
            ub = min(ub+1, C-1);
            n--;
        }
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            LUT[i][j] += tmp[i][j];
        }
    }
}

void AddTemp() {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            arr[i][j] += LUT[i][j];
        }
    }
}

void ControlTemp() {
    int tmp[20][20] = {0,}; // 온도 변화량 기록

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            for (int i = 1; i <= 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                if (W[r][c][i]) continue;
                
                // 현위치보다 4도 이상 높은 칸만 찾는다.
                if (arr[r][c] + 4 <= arr[nr][nc]) {
                    int v = (arr[nr][nc] - arr[r][c]) / 4;
                    tmp[r][c] += v;   // 현위치가 온도를 나눠받음
                    tmp[nr][nc] -= v; // 인접칸은 온도를 나눠줌
                }
            }
        }
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            arr[i][j] += tmp[i][j];
        }
    }
}

void DecreaseBdry() {
    for (int i = 0; i < C; i++) {
        if (arr[0][i]) arr[0][i]--;
        if (arr[R-1][i]) arr[R-1][i]--;
    }
    for (int i = 1; i < R-1; i++) {
        if (arr[i][0]) arr[i][0]--;
        if (arr[i][C-1]) arr[i][C-1]--;
    }
}

int Check() {
    for (POS p : chk) {
        if (arr[p.r][p.c] < K) return 0;
    }
    return 1;
}

int Simulation() {
    int t = 0;
    while (t < 100) {
        AddTemp();
        ControlTemp();
        DecreaseBdry();
        t++;
        if (Check()) {
            // Print(arr);
            return t;
        }
    }
    return 101;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    for (HEAT m : M) {
        MakeLUT(m.r, m.c, m.d);
    }
    cout << Simulation() << "\n";
}
