/*****************************************************/
// [13251] 조약돌 꺼내기 (실버3)
// - 독립사건의 확률: P(A ∩ B) = P(A) * P(B)
// - 0ms 2020KB
// - 순열조합(next_permutation)으로 시도했을 때 시간초과
/*****************************************************/

#include <iostream>
using namespace std;

int N, M, K;
int arr[50];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> arr[i];
        N += arr[i];
    }
    cin >> K;

    double ans = 0.0;
    for (int i = 0; i < M; i++) {
        if (arr[i] < K) continue;

        int den = N;      // 분모
        int num = arr[i]; // 분자
        double p = 1.0;
        for (int k = 0; k < K; k++) {
            p *= (double)num / den;
            den--; num--;
        }
        ans += p;
    }
    cout.precision(10);
    cout << ans << "\n";
}
