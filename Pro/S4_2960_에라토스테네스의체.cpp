/***********************************/
// [2960] 에라토스테네스의 체 (실버4)
// 0ms, 2024KB
/***********************************/

#include <iostream>
using namespace std;

int N, K;             // 1 <= K < N <= 1000
int flag[1001 + 10];  // 1: 지워짐. 0: 남아있음
int rem;              // 지운 수의 개수

void Input() {
    cin >> N >> K;
}

int MinPrime() {
    int i = 2;
    while (flag[i]) i++;
    if (i == N+1) return -1;
    return i;
}

int Solve() {
    flag[0] = flag[1] = 1;
    
    // ====  do ~ while문  ====
    int p; // 소수
    do {
        p = MinPrime(); // 디폴트 = 2
        for (int i = p; i <= N; i+=p) {
            if (!flag[i]) {
                flag[i] = 1;
                rem++;
            }
            if (rem == K) return i;
        }
    } while (p != -1);
    return -1;

    // ======  while문  ======
    // int p = MinPrime();  // 소수
    // while (p != -1) {
    //     for (int i = p; i <= N; i+=p) {
    //         if (!flag[i]) {
    //             flag[i] = 1;
    //             rem++;
    //         }
    //         if (rem == K) return i;
    //     }
    //     p = MinPrime();
    // }
    // return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    Input();
    cout << Solve() << "\n";
}
