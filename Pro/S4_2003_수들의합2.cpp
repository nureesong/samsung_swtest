/***********************************/
// [2003] 수들의 합2 (실버4)
// - 완전탐색 O(N^2): 2060KB, 24ms
// - 투포인터 O(N)  :  
/***********************************/

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
    for (int i = 0; i < N; i++) {
        int sum = 0;
        for (int j = i; j < N; j++) {
            sum += A[j];
            if (sum == M) cnt++;
            if (sum >= M) break;
        }
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
