/*****************************************************/
// [1725] 히스토그램 (플래티넘5)
// - 스택: 36ms, 2944KB
// int끼리 곱한 뒤, long long 변수에 할당해봤자 이미 오버플로우 발생한 상태
/*****************************************************/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int N;
vector<int> arr;

long long Solve() {
    stack<int> s;
    long long maxArea = 0;
    s.push(0);

    for (int i = 1; i <= N+1; i++) {
        while (!s.empty() && arr[i] < arr[s.top()]) {
            int cur = s.top(); s.pop();
            // 오버플로우 주의!!
            long long area = (long long)arr[cur] * (i - s.top() - 1);
            maxArea = (area > maxArea) ? area : maxArea;
        }
        s.push(i);
    }
    return maxArea;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (cin >> N) {
        if (N == 0) break;
        arr.clear();
        arr.resize(N+2, 0);
        for (int i = 1; i <= N; i++) cin >> arr[i];
        cout << Solve() << "\n";
    }
}
