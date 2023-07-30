#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int A[100000];
char C[100000];
struct DATA {
    int n;
    char c;
};
vector<DATA> V;

bool comp(DATA &a, DATA &b) {
    if (a.n % 2 == 0 && b.n % 2) return true;
    if (a.n % 2 && b.n % 2 == 0) return false;

    if (a.n == b.n) return a.c < b.c;
    return a.n < b.n;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) {
        cin >> C[i];
        V.push_back({ A[i],C[i] });
    }

    // [Type 1] 숫자 기준 오름차순 정렬
    sort(A, A+N);
    for (int i = 0; i < N; i++) cout << A[i] << " ";
    cout << "\n";
    // [Type 2] 숫자 기준 내림차순 정렬  
    for (int i = N-1; i >= 0; i--) cout << A[i] << " ";
    cout << "\n";

    // [Type 3] 짝수 우선 > 작은 수 우선 > 사전순 앞쪽 문자 우선
    sort(V.begin(), V.end(), comp);
    for (DATA v : V) cout << v.n << " ";
    cout << "\n";
    for (DATA v : V) cout << v.c << " ";
    cout << "\n";
}
