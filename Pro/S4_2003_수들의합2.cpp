/***********************************/
// [2003] 수들의 합2 (실버4)
// - 완전탐색 O(N^2): 24ms 2060KB
// - 투포인터 O(N)  :  0ms 2060KB
/***********************************/
// 10 5
// 1 2 3 5 1 4 2 3 1 5
// ----  답 3  -----
// 10 5
// 1 2 3 4 1 5 3 1 1 2
// ----  답 4  -----


#include <iostream>
using namespace std;

int N, M;
int A[10000];

void Input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
}

int Solve() {
    int cnt = 0;
    
    // Brute-force : O(N^2)
    // for (int i = 0; i < N; i++) {
    //     int sum = 0;
    //     for (int j = i; j < N; j++) {
    //         sum += A[j];
    //         if (sum == M) cnt++;
    //         if (sum >= M) break;
    //     }
    // }

    // Two Pointer : O(N)
    int i = 0, j = 0, sum = 0;

    while (i < N) {
        if (i == j) sum = A[i];
        if (sum == M) cnt++;

        if (sum >= M || j >= N-1) {
            sum -= A[i];
            i++;
        }
        else {
            j++;
            sum += A[j];
        }

        if (i > j) j = i;
    }
    return cnt;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    Input();
    cout << Solve() << "\n";
}
