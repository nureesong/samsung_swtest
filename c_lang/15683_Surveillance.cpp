/**************************************************************/
// [15683] 감시 (골드4)
// 16ms, 2024KB
// * CCTV 종류별 최대 4번 회전시 감시 방향에 대한 Lookup Table 만들어 놓기
// 1) CCTV별 회전 횟수에 대한 모든 경우의 수를 DFS(중복순열)로 구한다.
// 2) 경우의 수 하나 완성할 떄마다, 원본맵을 복사한 chk 배열에 감시영역 체크
//
// [시도해본 것들]
// 5번 CCTV는 4방향 다 감시하므로 회전시킬 필요가 없어서 원본맵에 감시영역을 고정 표시해놓고
// 4~1번 CCTV 순으로 회전하면서 감시영역 체크 후 사각지대 크기 계산 -> 똑같이 16ms 걸림
/**************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int arr[8][8]; // 0:빈칸(사각지대), 1~5:CCTV, 6:벽 (원본보존)
int chk[8][8]; // 모든 경우의 수에 대해 감시 영역 마킹하면서 최대값 찾기

int cnt_cctv;  // CCTV 개수
struct CCTV {
    int t;     // 종류(1~5)
    int r, c;  // 위치
}C[8];         
bool comp(CCTV &a, CCTV &b) {
    return a.t > b.t;
}

// CCTV 종류별 최대 4번 회전시 감시방향 Lookup table (2중 리스트)
vector<vector<int>> LUT[5+1] = {
    {},
    {{0}, {1}, {2}, {3}},
    {{0,1}, {2,3}},
    {{0,3}, {3,1}, {1,2}, {2,0}},
    {{2,0,3}, {0,3,1}, {3,1,2}, {1,2,0}},
    {{0,1,2,3}}
};
int dr[4] = {-1,1,0,0}; // 상하좌우(0123)
int dc[4] = {0,0,-1,1};
int pick[8];  // 회전횟수 순열

int area0;    // 초기 빈칸 개수
int max_surv; // 감시영역 최대크기


void Input() {
    int n;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> n;
            arr[i][j] = n;
            if (n > 0 && n < 6) C[cnt_cctv++] = {n,i,j};
            else if (n == 0) area0++;
        }
    }
    //sort(C, C+cnt_cctv, comp); // 정렬해도 시간 똑같다..
}

// n번째 CCTV를 pick[n]번 회전 후 감시영역 표시 및 크기 리턴
int Check(int n) {
    int cctv_type = C[n].t;     // n번째 CCTV 종류
    int r = C[n].r, c = C[n].c; // 위치
    int cnt = 0;

    for (int d : LUT[cctv_type][pick[n]]) {
        int nr = r + dr[d];
        int nc = c + dc[d];
        while ((nr >= 0 && nr < N) && (nc >= 0 && nc < M)) {
            if (chk[nr][nc] == 6) break;
            // 다른 CCTV와 중복 감시하지 않게 마킹
            if (chk[nr][nc] == 0) {
                chk[nr][nc] = cctv_type; 
                cnt++;
            }
            nr += dr[d]; 
            nc += dc[d];
        }
    }
    return cnt;
}

// n번째 CCTV의 회전횟수 선택
void DFS(int n) {
    // 가지치기
    if (max_surv == area0) return;

    if (n >= cnt_cctv) {
        // 선택한 횟수만큼 CCTV 회전 후 감시영역을 chk에 표시
        copy(&arr[0][0], &arr[N-1][M], &chk[0][0]);
        
        int sum = 0;
        for (int j = 0; j < cnt_cctv; j++) {
            sum += Check(j);
        }
        
        max_surv = (sum > max_surv) ? sum : max_surv;
        return;
    }

    int n_rotate = LUT[C[n].t].size();
    for (int i = 0; i < n_rotate; i++) {
        pick[n] = i;
        DFS(n + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    
    DFS(0); // 각각의 CCTV 회전횟수에 대한 순열 만들기

    cout << area0 - max_surv << "\n";
    return 0;
}
