#include <iostream>
#include <queue>
using namespace std;

int N;
priority_queue<long long, vector<long long>, greater<long long>> pq;

long long Solve() {
    long long cnt = 0;
    while (N > 1) {
        long long sum = pq.top(); pq.pop();
        sum += pq.top(); pq.pop();
        pq.push(sum);
        cnt += sum;
        N--;
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++) {
        long long num;
        cin >> num;
        pq.push(num);
    }
    cout << Solve() << "\n";
}
