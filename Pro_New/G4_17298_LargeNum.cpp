/*****************************/
// [17298] 오큰수 (골드4)
// - 스택: 244ms, 16MB
/*****************************/

#include <iostream>
#include <vector>
using namespace std;

int N;
int A[1000000];
vector<int> stack;
int R[1000000];

void Solve() {
    R[N-1] = -1;
    stack.push_back(A[N-1]);

    for (int i = N-2; i >= 0; i--) {
        int num = A[i];
        while (!stack.empty() && num >= stack.back()) {
            stack.pop_back();
        }
        R[i] = stack.empty() ? -1 : stack.back();
        stack.push_back(num);
    }

    for (int i = 0; i < N; i++) {
        cout << R[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    Solve();
}
