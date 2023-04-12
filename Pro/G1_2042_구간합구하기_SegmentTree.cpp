/*****************************************************/
// [2042] 구간 합 구하기 (골드1)
// 세그먼트 트리: O(N + Q*logN)  220ms, 26556KB
// 포화이진트리 (자식노드 2개 이하 -> 비대칭 모형)
/*****************************************************/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N, M, K;
vector<long long> arr;
vector<long long> tree;
struct QUERY {
    int a, b;
    long long c;
};
vector<QUERY> Q;


void Input() {
    cin >> N >> M >> K;
    arr.resize(N);
    Q.resize(M+K);
    int depth = (int)ceil(log2(N));
    int n_leaf = 1 << depth;     // N보다 큰, 가장 작은 2의 제곱수
    tree.resize(n_leaf * 2); // 트리 전체 노드수 = 리프노드 수 * 2

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < M+K; i++) {
        cin >> Q[i].a >> Q[i].b >> Q[i].c;
    }
}

// [트리 생성] Top-down 방식 O(logN)
long long MakeTree(int s, int e, int idx) {
    if (s == e) return tree[idx] = arr[s]; // leaf node
    int mid = (s + e) / 2;
    return tree[idx] = MakeTree(s, mid, 2*idx) + MakeTree(mid+1, e, 2*idx+1);
}

// O(logN)
void Update(int s, int e, int idx, int target, long long diff) {
    if (target < s || target > e) return;

    tree[idx] += diff; // top-down으로 위쪽부터 노드값 변경
    if (s == e) return;
    int mid = (s + e) / 2;
    Update(s, mid, 2*idx, target, diff);
    Update(mid+1, e, 2*idx+1, target, diff);
}

// Range query : O(logN)
// [s,e]: 탐색구간, idx: 탐색구간의 루트노드, [qs,qe]: 쿼리구간
long long Sum(int s, int e, int idx, int qs, int qe) {
    // 탐색구간이 쿼리구간과 겹치지 않는 경우
    if (qe < s || qs > e) return 0;
    // 탐색구간이 쿼리구간에 포함되는 경우
    if (qs <= s && qe >= e) return tree[idx];
    // 탐색구간과 쿼리구간과 일부 겹치는 경우
    int mid = (s + e) / 2;
    return Sum(s, mid, 2*idx, qs, qe) + Sum(mid+1, e, 2*idx+1, qs, qe);
}

void Solve() {
    for (auto q : Q) {
        if (q.a == 1) {
            Update(0, N-1, 1, q.b-1, q.c - arr[q.b-1]);
            arr[q.b-1] = q.c;
        }
        else cout << Sum(0, N-1, 1, q.b-1, q.c-1) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    MakeTree(0, N-1, 1);
    Solve();
}
