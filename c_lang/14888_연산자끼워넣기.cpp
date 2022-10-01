/************************************/
// [14888] 연산자 끼워넣기 (실버1)
// DFS - 순열 : 0ms, 2020KB
// 22:03 ~ 22:45 (42분 소요)
/************************************/

#include <iostream>
using namespace std;

int N;
int num[11]; // N개의 숫자
int cnt[4];  // +,-,x,/ 개수
int maxv = -0x7fffffff;
int minv = 0x7fffffff;

void Input() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> num[i];
    for (int i = 0; i < 4; i++) cin >> cnt[i];
}

// 현재까지 연산값, 선택한 연산자, 연산할 값(num[n])
int Calc(int cur, int op, int v) {
    switch (op) {
        case 0: return cur + v;
        case 1: return cur - v;
        case 2: return cur * v;
        default: return cur / v;
    }
}

// n번째 연산자 선택
// cur: 현재까지 선택한 연산자로 계산한 값 (연산자 1개 선택할 때마다 바로바로 계산한다)
void DFS(int n, int cur) {
    if (n == N) {
        maxv = (cur > maxv) ? cur : maxv;
        minv = (cur < minv) ? cur : minv;
        return;
    }

    // 연산자 선택하는 경우의 수: +,-,x,/ (0123)
    for (int i = 0; i < 4; i++) {
        if (!cnt[i]) continue; // 1개 이상 남았을 때만 선택
        
        cnt[i]--; // 개수 차감
        int ret = Calc(cur, i, num[n]); // 연산자 선택할 때마다 중간계산
        DFS(n+1, ret);
        cnt[i]++; // 복원
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    DFS(1, num[0]);
    cout << maxv << "\n" << minv << "\n"; 
}
