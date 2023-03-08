/***********************************/
// [2748] 피보나치 수2 (브론즈1)
// - DP: 자나깨나 long long 주의! (0ms)
// - Recursion: 시간초과
/***********************************/

#include <iostream>
using namespace std;

int N;

void Input() {
    cin >> N;
}

long long DP() {
    long long a = 0, b = 1, c = 0;
    
    if (N == 1) c = 1;
    else {
        for (int i = 2; i <= N; i++) {
            c = a + b;
            a = b;
            b = c;
        }
    }
    return c;
}

long long fibo(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibo(n - 1) + fibo(n - 2);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    Input();
    cout << DP() << "\n";
    // cout << fibo(N) << "\n";  // 시간초과
}
