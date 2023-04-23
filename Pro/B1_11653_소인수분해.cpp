/*****************************************************/
// [11653] 소인수분해 (브론즈1)
// 소수판별 - 에라토스테네스의 체: 104ms, 9516KB 
/*****************************************************/

#include <iostream>
#include <vector>
using namespace std;

int N;
vector<bool> chk;
vector<int> primes;

void FindPrimes() {
    chk.resize(N+1);
    for (int i = 2; i <= N; i++) {
        if (chk[i]) continue;
        primes.push_back(i);

        int num = 2*i;
        while (num <= N) {
            chk[num] = true;
            num += i;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    if (N == 1) return 0;
    
    FindPrimes();
    for (int p : primes) {
        while (N >= p && N % p == 0) {
            cout << p << "\n";
            N /= p;
        }
    }
}
