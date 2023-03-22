/***************************************/
// [1837] 암호제작 (브론즈3)
// 소수 판별: 에라토스테네스의 체 O( Nlog(logN) )
// 큰 수 나눗셈: 맨 앞부터 한 자리씩 떼서 하기!
/***************************************/

#include <iostream>
#include <cmath>
using namespace std;

string P; // 10^100 -> long long 초과 → 문자열로 처리
int K;    // 10^6
int flag[1000001]; // 0:소수, 1:합성수


// 에라토스테네스의 체로 K-1까지의 소수 구해놓기
void FindPrime() {
    for (int p = 2; p <= sqrt(K); p++) {
        if (flag[p]) continue;

        // p의 배수를 모두 지운다.
        int n = 2*p;
        while (n < K) {
            flag[n] = 1;
            n += p;
        }
    }
}

string Divide() {
    for (int p = 2; p < K; p++) {
        if (flag[p]) continue;

        // 문자열 한 자리씩 나눗셈
        int n = 0;
        for (char c : P) {
            n = (n * 10 + c-'0') % p;
        }
        if (!n) return "BAD " + to_string(p);
    }
    return "GOOD";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> P >> K;
    FindPrime();
    cout << Divide() << "\n";
    return 0;
}
