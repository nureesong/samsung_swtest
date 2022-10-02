/***********************************/
// [12100] 2048 Easy (골드2)
//  12ms, 2028KB
// 14:13 ~ 15:49 (1시간 36분 소요)
/***********************************/

#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
#define MAXMOVE (5)

int N;
int sol;
int arr[20][20]; // 0:빈칸, 2의제곱수:블록 -> 원본 보존!
int cop[20][20]; // 원본맵 복사해서 이동한 결과 기록
int pick[5];     // 이동 방향 선택 - 중복순열
deque<int> deq;

// 상하 방향: 열 고정, 행 훑기
void MoveUD(int d) {
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            if (!cop[i][j]) continue;
            if (d == 0) deq.push_back(cop[i][j]);
            else deq.push_front(cop[i][j]);
            cop[i][j] = 0;
        }

        int a = 0, b = 0;
        int i = (d == 0) ? 0 : N-1;
        while (!deq.empty()) {
            if (a == 0) {
                a = deq.front(); deq.pop_front();
                continue;
            }

            b = deq.front(); deq.pop_front();
            if (a == b) {
                cop[i][j] = a + b;
                a = 0; b = 0;
            }
            else {
                cop[i][j] = a;
                a = b; b = 0;
            }
            sol = (cop[i][j] > sol) ? cop[i][j] : sol;
            if (d == 0) i++;
            else i--;
        }

        if (a || b) {
            cop[i][j] = a + b;
            sol = (cop[i][j] > sol) ? cop[i][j] : sol;
        }
    }
}


// 좌우 방향: 행 고정, 열 훑기
void MoveLR(int d) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!cop[i][j]) continue;
            if (d == 2) deq.push_back(cop[i][j]);
            else deq.push_front(cop[i][j]);
            cop[i][j] = 0;
        }

        int a = 0, b = 0;
        int j = (d == 2) ? 0 : N-1;
        while (!deq.empty()) {
            if (a == 0) {
                a = deq.front(); deq.pop_front();
                continue;
            }

            b = deq.front(); deq.pop_front();
            if (a == b) {
                cop[i][j] = a + b;
                a = 0; b = 0;
            }
            else {
                cop[i][j] = a;
                a = b; b = 0;
            }
            sol = (cop[i][j] > sol) ? cop[i][j] : sol;
            if (d == 2) j++;
            else j--;
        }

        if (a || b) {
            cop[i][j] = a + b;
            sol = (cop[i][j] > sol) ? cop[i][j] : sol;
        }
    }
}

// cnt: 현재까지 선택한 이동횟수
void DFS(int cnt) {
    if (cnt == MAXMOVE) {
        copy(&arr[0][0], &arr[N-1][N], &cop[0][0]);

        for (int i = 0; i < MAXMOVE; i++) {
            if (pick[i] <= 1) MoveUD(pick[i]); // up down
            else MoveLR(pick[i]); // left right
        }
        return;
    }

    // 이동할 방향 경우의 수: 상하좌우(0123)
    for (int i = 0; i < 4; i++) {
        pick[cnt] = i;
        DFS(cnt + 1);
    }
}

void Input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    if (N == 1) cout << arr[0][0] << "\n";
    else {
        DFS(0);
        cout << sol << "\n";
    }
}
