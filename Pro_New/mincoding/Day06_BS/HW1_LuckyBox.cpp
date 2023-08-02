// Parametric Search: 4ms, 2MB
// Prefix sum: 6ms, 9MB
#include <iostream>
using namespace std;

//========== Parametric Search ===========
int N, M, K;
struct RULE {
    int a, b, c;
}R[10000];

int CountCoupons(int m) {
    int cnt = 0;
    for (int i = 0; i < M; i++) {
        int boxEnd = m <= R[i].b ? m : R[i].b;
        int rangeLen = boxEnd - R[i].a;
        if (rangeLen < 0) continue;
        if (R[i].a <= m) cnt++;
        cnt += (rangeLen / R[i].c);
        if (cnt >= K) return 1;
    }
    return 0;
}


int BS_lower(int s, int e) {
    while (s <= e) {
        int m = (s + e) / 2;
        if (CountCoupons(m)) e = m - 1;
        else s = m + 1;
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        cin >> R[i].a >> R[i].b >> R[i].c;
    }
    cout << BS_lower(1, N) << "\n";
}

//============  Prefix sum  ==============
#if 0
int N, M, K;
int cnt[1000001];
int psum[1000001];

int BS_lower(int s, int e) {
    while (s <= e) {
        int m = (s + e) / 2;
        if (psum[m] >= K) e = m - 1;
        else s = m + 1;
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;
    int A, B, C;
    for (int i = 0; i < M; i++) {
        cin >> A >> B >> C;
        for (int i = A; i <= B; i += C) {
            cnt[i]++;
        }
    }
    for (int i = 1; i <= N; i++) {
        psum[i] = psum[i-1] + cnt[i];
    }
    cout << BS_lower(1, N) << "\n";
}
#endif
