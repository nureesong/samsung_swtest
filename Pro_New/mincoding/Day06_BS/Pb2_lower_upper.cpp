#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, Q;
vector<int> arr;

int BS_lower(int s, int e, int num) {
    int idx = -1;
    while (s <= e) {
        int m = (s + e) / 2;
        if (arr[m] >= num) {
            e = m - 1;
            idx = m;
        }
        else s = m + 1;
    }
    return idx;
}

int BS_upper(int s, int e, int num) {
    int idx = -1;
    while (s <= e) {
        int m = (s + e) / 2;
        if (arr[m] <= num) {
            s = m + 1;
            idx = m;
        }
        else e = m - 1;
    }
    return idx;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    arr.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());

    int S, E;
    while (Q--) {
        cin >> S >> E;
        int lb = BS_lower(0, N-1, S);
        if (lb == -1) {
            cout << "0\n";
            continue;
        }
        int ub = BS_upper(0, N-1, E);
        if (ub == -1) cout << "0\n";
        else cout << ub - lb + 1 << "\n";
    }
}
