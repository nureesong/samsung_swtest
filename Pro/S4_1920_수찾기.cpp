/*************************************************/
// [1920] 수 찾기 (실버4)
// - 배열값의 범위: -2^31 ~ 2^31 --> flag 배열 사용불가
// - 이분탐색: O(NlogN + M) --> 52ms 2800KB
/*************************************************/

#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int arr[100000];
int Q[100000];


void Input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> Q[i];
    }
}

int BS(int s, int e, int num) {
    while (s <= e) {
        int m = (s + e) / 2;
        if (arr[m] > num) e = m-1;
        else if (arr[m] < num) s = m+1;
        else return 1;
    }
    return 0;
}

void Solve() {
    sort(arr, arr+N);
    for (int i = 0; i < M; i++) {
        cout << BS(0, M-1, Q[i]) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    Solve();
}
