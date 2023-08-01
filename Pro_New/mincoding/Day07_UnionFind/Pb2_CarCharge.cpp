#include <iostream>
using namespace std;

int T, N;
int P[100001];

int find_root(int n) {
    if (P[n] == n) return n;
    return P[n] = find_root(P[n]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T >> N;
    for (int i = 1; i <= T; i++) P[i] = i;

    int skip = 0, car, cnt = 0;
    while (N--) {
        cin >> car;
        if (skip) continue;
        int possible = find_root(car);
        if (!possible) skip = 1;
        else {
            P[possible] = find_root(possible - 1);
            cnt++;
        }
    }
    cout << cnt << "\n";
}
