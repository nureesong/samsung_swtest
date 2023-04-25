/*****************************************************/
// [1735] 분수합 (실버3)
// - 유클리드 호제법: 최대공약수(GCD) 구하는 알고리즘
// - 최소공배수 = 두 수의 곱 / 최대공약수
// - 오버플로우!! -> long long 연산
/*****************************************************/

#include <iostream>
using namespace std;

int A, B, C, D;

long long GCD(long long a, long long b) {
    while (b) {
        long long tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> A >> B >> C >> D;

    // 1. 기약분수 만들기 (최대공약수)
    int g1 = GCD(A,B); // 첫번째 분수
    if (g1 > 1) {
        A /= g1; B /= g1;
    }
    int g2 = GCD(C,D); // 두번째 분수
    if (g2 > 1) {
        C /= g2; D /= g2;
    }

    // 2. 통분하기 (최소공배수) -> Overflow 주의!!
    long long lcm = B * D / GCD(B, D);     // 통분 후 분자 (최소공배수)
    long long numer = (A * lcm / B) + (C * lcm / D); // 통분 후 분자의 합

    // 3. 기약분수로 약분하기
    long long gcd = GCD(numer, lcm);
    if (gcd > 1) {
        numer /= gcd; lcm /= gcd;
    }
    cout << numer << " " << lcm << "\n";
}
