/*****************************************************/
// [13251] 조약돌 꺼내기 (실버3)
// 시간초과
/*****************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, K;
int arr[50];
vector<int> v;

int Combination(int n, int r) {
    v.resize(n, 1);
    for (int i = 0; i < r; i++) v[i] = 0;
    int cnt = 0;

    do {
        cnt++;
    }while (next_permutation(v.begin(), v.end()));
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    setbuf(stdout, NULL);

    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> arr[i];
        N += arr[i];
    }
    cin >> K;

    int numerator = 0;
    for (int i = 0; i < M; i++) {
        if (arr[i] < K) continue;
        numerator += Combination(arr[i], K);
    }
    cout.precision(10);
    cout << (double)numerator / Combination(N, K) << "\n";
}
