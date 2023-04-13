/*****************************************************/
// [10868] 최솟값 (골드1)
// - 세그먼트 트리: 80ms 3456KB
/*****************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#define INF (1000000001)
using namespace std;

int N, M;
vector<int> arr;
vector<int> tree;


int MakeTree(int s, int e, int idx) {
    if (s == e) return tree[idx] = arr[s];
    int m = (s + e) / 2;
    int l = MakeTree(s, m, 2*idx);
    int r = MakeTree(m+1, e, 2*idx+1);
    return tree[idx] = ((l < r) ? l : r);
}

int Minimum(int s, int e, int idx, int qs, int qe) {
    if (qs > e || qe < s) return INF;
    if (qs <= s && e <= qe) return tree[idx];
    int m = (s + e)/2;
    int l = Minimum(s, m, 2*idx, qs, qe);
    int r = Minimum(m+1, e, 2*idx+1, qs, qe);
    return (l < r) ? l : r;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    arr.resize(N);
    int depth = (int)ceil(log2(N));
    tree.resize(1 << depth + 1);

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    MakeTree(0, N-1, 1);

    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        cout << Minimum(0, N-1, 1, a-1, b-1) << "\n";
    }

}
