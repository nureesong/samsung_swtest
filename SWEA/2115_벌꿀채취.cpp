/***********************************/
// [2115] 벌꿀채취
// DFS - 조합: 13ms, 13536KB
// 16:00 ~ 17:28 (1시간 28분 소요)
/***********************************/

#include <iostream>
#include <algorithm>
using namespace std;

int N, M, C;
int w, n_rect;
int arr[10][10];

int r, c, maxsum;
int sol;

void Input() {
    cin >> N >> M >> C;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }
    w = N - M + 1; // 한 행에 Mx1 직사각형 w개 존재
    n_rect = N * w; // 전체 직사각형 개수
    sol = 0;
}

// DFS - 조합 (직사각형 M개의 칸 중 m번째 칸 선택/미선택)
// 총 C 이하의 꿀을 채취했을 때 최대 수익 찾기
void DFS(int m, int curh, int sqsum) {
    // 종료조건
    if (m == M) {
        maxsum = (sqsum > maxsum) ? sqsum : maxsum;
        return;
    }

    // 총 꿀의 양이 C 이하이면 m번째 칸 채취
    int h = arr[r][c + m];
    if (curh + h <= C) DFS(m+1, curh + h, sqsum + h*h);

    // 미선택
    DFS(m+1, curh, sqsum);
}

void Solve() {
    // i,j: 두 일꾼이 선택한 직사각형 번호
    for (int i = 0; i < n_rect - 1; i++) {
        int r1 = i / w;
        int c1 = i % w;
        // 현재 직사각형에서 꿀 채취 & 수익 계산
        r = r1; c = c1; maxsum = 0;
        DFS(0, 0, 0);
        int p1 = maxsum;

        for (int j = i+1; j < n_rect; j++) {
            int r2 = j / w;
            int c2 = j % w;
            // 다른 일꾼이랑 겹치는 직사각형 선택 불가
            if (r1 == r2 && abs(c1 - c2) < M) continue;

            // 꿀 채취 & 수익 계산
            r = r2; c = c2; maxsum = 0;
            DFS(0, 0, 0);
            int p2 = maxsum;
            
            int sump = p1 + p2; // 두 일꾼 수익의 합
            sol = (sump > sol) ? sump : sol;
            // cout << sump << " " << sol << "\n";
        }
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
        Solve();
        cout << "#" << i << " " << sol << "\n";
    }
}
