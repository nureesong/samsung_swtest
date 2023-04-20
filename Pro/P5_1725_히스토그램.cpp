/*****************************************************/
// [1725] 히스토그램 (플래티넘5)
// - 스택: 12ms, 2944KB
//   arr size = N+2
//   맨 앞에 0 추가: 스택 밑바닥에 0을 깔아두어 모든 요소가 push되게 한다.
//   맨 뒤에 0 추가: 끝까지 진행 시 스택에 쌓여있는 모든 원소를 pop되게 한다.
// - 세그먼트 트리 + 분할정복: 28ms, 6632KB
//   [s,e] 구간 내에서 가장 낮은 막대기를 찾아 구간 길이를 밑변으로 하는 직사각형 넓이 계산
//   Divide-Conquer(s,e): 쿼리구간에서 배열값이 최소인 인덱스를 찾고, 좌우로 나눠서 재귀적으로 탐색
/*****************************************************/

// 스택
#if 1
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
#endif 


// 세그먼트 트리 + Divide-Conquer
#if 0
#include <iostream>
#include <vector>
#include <cmath>
#define INF (100001)
using namespace std;

int N;
int arr[100000];
vector<int> tree;
int ans;

int MakeTree(int s, int e, int idx) {
    if (s == e) return tree[idx] = s;
    int m = (s + e) / 2;
    int left = MakeTree(s, m, 2*idx);
    int right = MakeTree(m+1, e, 2*idx+1);
    return tree[idx] = (arr[left] < arr[right] ? left : right);
}

int Minimum(int s, int e, int idx, int qs, int qe) {
    if (qe < s || qs > e) return INF;  // 겹치지 않는 경우
    if (qs <= s && e <= qe) return tree[idx];  // 포함되는 경우
    // 탐색구간과 쿼리구간이 일부 겹치는 경우
    int m = (s + e) / 2;
    int l = Minimum(s, m, 2*idx, qs, qe);
    int r = Minimum(m+1, e, 2*idx + 1, qs, qe);
    // 아래 두 줄 없으니까 시간초과,,, 가지치기 역할!
    if (l == INF) return r;
    if (r == INF) return l;
    return arr[l] < arr[r] ? l : r;
}

void Divide_Conquer(int qs, int qe) {
    if (qs > qe) return;
    int minidx = Minimum(0, N-1, 1, qs, qe);
    int area = arr[minidx] * (qe - qs + 1);
    ans = (area > ans) ? area : ans;
    Divide_Conquer(qs, minidx-1);
    Divide_Conquer(minidx+1, qe);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++) cin >> arr[i];

    int depth = (int)ceil(log2(N)) + 1;
    tree.resize((int)pow(2,depth));
    MakeTree(0, N-1, 1);

    Divide_Conquer(0, N-1);
    cout << ans << "\n";
}
#endif
