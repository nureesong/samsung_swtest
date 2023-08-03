// Parametric Search 
// O(log10억 * N) -> 30 * 10만 = 300만
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;       // N: 매점수 (10만)
long long M; // M: 사람수 (10억)
vector<long long> T; // 매점별 조리시간 (오름차순 정렬)

int Test(long long m) {
    long long cnt = 0;
    for (long long t : T) {
        cnt += m / t;
        if (cnt >= M) return 1;
    }
    return 0;
}

long long PS(long long s, long long e) {
    while (s <= e) {
        long long m = (s + e) / 2;
        if (Test(m)) e = m - 1;
        else s = m + 1;
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    T.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> T[i];
    }
    sort(T.begin(), T.end());
    cout << PS(1, 1000000000) << "\n";
}


//=======  PQ: 시간초과 O(M * logN) -> 10억 * 15  ========
#if 0
#include <iostream>
#include <queue>
using namespace std;

int N, M;
long long T[100000]; // 매점별 조리시간
typedef pair<long long, int> PAIR;
priority_queue<PAIR> pq; // <-누적조리시간,매점번호>

long long BFS() {
    PAIR cur;
    while (M--) {
        cur = pq.top(); pq.pop();
        pq.push({ cur.first-T[cur.second],cur.second });
    }
    return -cur.first;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> T[i];
        pq.push({-T[i],i});
    }
    cout << BFS() << "\n";
}
#endif
