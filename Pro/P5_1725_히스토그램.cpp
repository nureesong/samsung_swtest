/*****************************************************/
// [1725] 히스토그램 (플래티넘5)
// - 스택: 12ms, 2944KB
// arr size = N+2
// 맨 앞에 추가한 이유: 맨 첫번째 막대에 대한 직사각형 넓이 계산하기 위해
// 맨 뒤에 추가한 이유: 모든 막대가 증가 패턴일때 마지막에 감소를 발생시키기 위해
/*****************************************************/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int N;
vector<int> arr;
stack<int> s;

int Solve() {
    int maxArea = 0, area;
    s.push(0);
    for (int i = 1; i <= N+1; i++) {
        while (!s.empty() && (arr[i] < arr[s.top()])) {
            int cur = s.top();
            s.pop();
            area = arr[cur] * (i - s.top() - 1);
            maxArea = (area > maxArea) ? area : maxArea;
        }
        s.push(i);
    }
    return maxArea;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    arr.resize(N+2);
    for (int i = 1; i <= N; i++) cin >> arr[i];

    cout << Solve() << "\n";
}
