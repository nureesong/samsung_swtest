/********************************/
// [16637] 괄호 추가하기 (골드4)
// 0ms, 2020KB
/********************************/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int N;
int arr[19];
int flag[19];         // 괄호 연산 선택 여부
int maxsum = INT_MIN; // 정수 최솟값 - 2^31 - 1
vector<int> eq; // 괄호 먼저 연산 후 최종적으로 계산할 수식

void Input() {
    char c;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> c;
        switch (c) {
        case '+':
            arr[i] = 0; break;
        case '-':
            arr[i] = 1; break;
        case '*':
            arr[i] = 2; break;
        default:
            arr[i] = c - '0';
        }
    }
}

int Calc(int a, int b, int op) {
    if (op == 0) return a + b;
    if (op == 1) return a - b;
    return a * b;
}

int AddParen() {
    eq.clear();

    for (int op = 1; op <= N-2; op += 2) {
        // 괄호 추가한 연산자는 먼저 연산해서 푸시
        if (flag[op]) eq.push_back(Calc(arr[op-1], arr[op+1], arr[op]));
        else {
            // 1번째 연산자 미선택 시 앞 숫자 arr[0]도 푸시!!
            if (op == 1) eq.push_back(arr[0]);
            // 미선택 연산자와 그 뒷 숫자는 그대로 푸시
            eq.push_back(arr[op]);
            if (!flag[op + 1]) eq.push_back(arr[op + 1]);
        }
    }

    int sum = eq[0];
    int sz = eq.size();
    for (int i = 1; i < sz; i += 2) {
        sum = Calc(sum, eq[i+1], eq[i]);
    }
    return sum;
}

// n번째 연산자 선택/미선택 하는 경우의 수 탐색
void DFS(int n) {
    if (n > N-2) return;

    // 1) n번째 연산자 선택O
    flag[n - 1] = flag[n] = flag[n + 1] = 1;
    int ret = AddParen();  // 괄호 추가할 때마다 수식을 계산하고, 최댓값과 비교
    maxsum = (ret > maxsum) ? ret : maxsum;
    
    DFS(n + 4);  // n번째 연산 자 선택시 n+2번째 연산자 선택 불가 (괄호 중첩)
    flag[n - 1] = flag[n] = flag[n + 1] = 0; // 복원
    
    // 2) n번쨰 연산자 선택X
    DFS(n + 2);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();

    if (N == 1) cout << arr[0] << "\n"; // 연산자 없이 숫자 1개만 있 경우
    else {
        DFS(1);
        cout << maxsum << "\n";
    }
}
