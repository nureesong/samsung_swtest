/*****************************************************/
// [11659] 구간 합 구하기4 (실버3)
// 1차원 Prefix sum, DP: 40ms, 3192KB
/*****************************************************/

#include <iostream>
using namespace std;

int N, M;
int psum[100001];
struct QUERY {
    int s, e;
}Q[100000];

void Input() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> psum[i];
        psum[i] += psum[i-1];
    }
    for (int i = 0; i < M; i++) {
        cin >> Q[i].s >> Q[i].e;
    }
}

void Solve() {
    for (int i = 0; i < M; i++) {
        cout << psum[Q[i].e] - psum[Q[i].s - 1] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    Solve();
}
