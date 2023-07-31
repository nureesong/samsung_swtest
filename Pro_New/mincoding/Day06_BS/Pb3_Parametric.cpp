#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, K;
vector<int> arr;

int Chop(int L) {
    int cnt = 0;
    for (int i = N-1; i >= 0; i--) {
        if (arr[i] < L) break; // 가지치기: L 이상인 츄러스만 탐색
        cnt += arr[i] / L;
    }
    return cnt;
}

int BS_upper(int s, int e, int num) {
    int ans = -1;
    while (s <= e) {
        int m = (s + e) / 2;
        if (Chop(m) >= num) {
            s = m + 1;
            ans = m;
        }
        else e = m - 1;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    arr.resize(N);
    for (int i = 0; i < N; i++) cin >> arr[i];
    sort(arr.begin(), arr.end());

    cout << BS_upper(1, arr[N-1], K) << "\n";
}
