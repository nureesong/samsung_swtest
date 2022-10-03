/***********************************/
// [1767] 프로세서 연결하기 
// DFS - 중복순열
// 14:10 ~ 15:25 (1시간 15분 소요)
// 코어 하나 방향 선택할 때마다 원본 맵에 마킹하면서 개수를 세려고 했는데,
// 리턴하고 돌아와서 복원하는 과정에서 남아있는 문제가 해결이 안 됨..
// 일단, 모든 코어의 방향 다 선택한 후 전선 안 겹치게 설치 가능한지 확인했다.
/***********************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int arr[12+2][12+2]; // 0:빈칸, 1:코어, 2:전선
int cop[12+2][12+2]; // 복사본
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};

struct POS {
    int r,c;
};
vector<POS> Core; // 전원 연결되지 않은 코어의 위치
int n_core; // 전원 연결되지 않은 코어 개수

int sol;
int pick[12];


void Input() {
    // Init
    Core.clear();
    sol = 0x7fffffff;

    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
            if (!arr[i][j]) continue;
            if (i == 0 || i == N-1 || j == 0 || j == N-1) continue;
            Core.push_back({i,j});
        }
    }
    n_core = Core.size();
}

// n번째 코어의 전선을 d 방향으로 설치한 개수 구하기 (불가능 시 0)
int SetCore(int n, int d) {
    int r = Core[n].r + dr[d];
    int c = Core[n].c + dc[d];
    int cnt = 0;

    while (r >= 0 && r < N && c >= 0 && c < N) {
        if (cop[r][c]) return 0; // 다른 코어/전선과 겹치면 불가능
        cop[r][c] = 2;
        cnt++;
        r += dr[d];
        c += dc[d];
    }
    return cnt;
}

// n번째 코어의 전선 방향 선택
void DFS(int n) {
    if (n == n_core) {
        copy(&arr[0][0], &arr[N-1][N], &cop[0][0]);

        int sumlen = 0;
        for (int i = 0; i < n_core; i++) {
            int ret = SetCore(i, pick[i]);
            if (!ret) return;
            sumlen += ret;
        }
        
        sol = (sumlen < sol) ? sumlen : sol;
        return;    
    }

    for (int i = 0; i < 4; i++) {
        pick[n] = i;
        DFS(n+1);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        Input();
        DFS(0);
        cout << "#" << i << " " << sol << "\n";
    }
}
