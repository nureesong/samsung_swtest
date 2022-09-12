/****************************************/
// [14503] 로봇 청소기 (골드5)
// 단순 구현: 0ms
/****************************************/

#include <iostream>
using namespace std;

int N, M;
int r, c, d;               // 로봇 청소기 시작 지점과 시작 방향
int arr[50 + 10][50 + 10]; // 0: 빈칸, 1: 벽, 2: 청소완료
int dr[] = {-1, 0, 1, 0};  // 북동남서
int dc[] = {0, 1, 0, -1};


int NextDirection(int r, int c, int d) {
    int nr, nc, nd;
    
    // 현재 방향을 기준으로 왼쪽부터 탐색 (서남동북)
    for (int k = 1; k <= 4; k++) {
        nd = (d - k + 4) % 4;
        nr = r + dr[nd];
        nc = c + dc[nd];

        // 청소하지 않은 공간 발견 시 다음 방향 리턴
        if (arr[nr][nc] == 0) return nd;
    }
    
    return -1;  // 청소할 공간 없음
}

int Solve() {
    int cnt = 0;
    
    while (arr[r][c] != 1) {
        // 1. 현재 위치가 빈 칸이면 청소한다.
        if (arr[r][c] == 0) {
            arr[r][c] = 2;
            cnt++;
        }

        // 2. 현재 방향을 기준으로 왼쪽부터 탐색 (서남동북)
        int nd = NextDirection(r, c, d);
        if (nd != -1) { // 청소하지 않은 공간 존재
            d = nd;     // 그 방향으로 회전
            r += dr[d]; // 한 칸 전진
            c += dc[d];
            continue;   // 다시 1번부터 진행
        }
        
        // 2-3. 네 방향 모두 청소 되어있거나 벽인 경우 (nd = -1)
        if (arr[r - dr[d]][c - dc[d]] != 1) { // 현재 방향에서 뒷칸이 벽이 아니면
            r -= dr[d]; // 한 칸 후진
            c -= dc[d];
        }
        else return cnt; // 뒷칸이 벽이면 후진 불가하므로 작동 멈추기

    }

    return -1;
}

void Input() {
    cin >> N >> M;
    cin >> r >> c >> d;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
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
