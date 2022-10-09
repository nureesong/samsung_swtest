/***************************************/
// [17144] 미세먼지 안녕! (골드4)
// 구현 - 36ms, 2032KB
// 행 범위!! [0, N-1] 아니라 공기청정기 위치까지!!
// 1시간 25분 소요
/***************************************/

#include <iostream>
#include <cstring>
using namespace std;

int R, C, T;
int A[50][50];
int dr[] = {-1,0,1,0}; // 상우하좌 (시계방향)
int dc[] = {0,1,0,-1}; 
int sol; // 남아있는 미세먼지의 양

struct POS {
    int r, c;
}M[2];  // 공기청정기 위치 (0: 위, 1: 아래)


void Input() {
    cin >> R >> C >> T;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> A[i][j];
            if (A[i][j] != -1) sol += A[i][j];
        }
    }
}

void Init() {
    for (int i = 1; i < R-1; i++) {
        if (A[i][0] == -1) {
            M[0] = { i,0 };
            M[1] = { i + 1,0 };
            return;
        }
    }
}

void MoveDust() {
    int tmp[50][50] = {0,};
    tmp[M[0].r][M[0].c] = -1;
    tmp[M[1].r][M[1].c] = -1;

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (A[r][c] == -1) continue;

            int v = A[r][c] / 5;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                if (A[nr][nc] == -1) continue;

                A[r][c] -= v;
                tmp[nr][nc] += v;
            }
            tmp[r][c] += A[r][c];
        }
    }
    memcpy(A, tmp, sizeof(tmp));
}

// n = 0 (위), n = 1 (아래)
void AirClean(int n) {
    // 공기청정기로 들어오는 부분부터 역방향으로 처리하면 A에 덮어써도 된다.
    //  위:  시계방향(1)으로 이동.   시작방향 = 상(0)
    // 아래: 반시계방향(-1)으로 이동. 시작방향 = 하(2)
    int m, d, lb, ub;
    if (n == 0) {
        m = 1; d = 0;
        lb = 0; ub = M[0].r;
    }
    else {
        m = -1; d = 2;
        lb = M[1].r; ub = R-1;
    }
    
    // 시작위치: 공기청정기에 흡입되는 곳!!
    int r = M[n].r + dr[d]; 
    int c = M[n].c + dc[d];
    sol -= A[r][c];
    
    // 공기청정기 위/아래(제자리)로 돌아올 때까지 이동
    for (;;) {
        int nr = r + dr[d];
        int nc = c + dc[d];
        
        // 행 범위!! [0, N-1] 아니라 공기청정기 위치까지!!
        if (nr < lb || nr > ub || nc < 0 || nc >= C) {
            d = (d + m + 4) % 4;
            nr = r + dr[d];
            nc = c + dc[d];
        }

        if (nr == M[n].r && nc == M[n].c) break;

        A[r][c] = A[nr][nc];
        r = nr; c = nc;
    }
    A[r][c] = 0;  // 바람이 부는 첫 칸은 모든 미세먼지가 이동했으므로 0
}

void Simulation() {
    for (int t = 0; t < T; t++) {
        MoveDust();  // 미세먼지 총량은 그대로
        AirClean(0); // 공기청정기에 흡입되는 양만큼 감소!
        AirClean(1); 
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    Init();

    Simulation();
    cout << sol << "\n";
}
