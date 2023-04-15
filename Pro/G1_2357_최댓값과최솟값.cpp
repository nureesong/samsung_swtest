/*****************************************************/
// [2357] 최솟값과 최댓값 (골드1)
// - 세그먼트 트리: 120ms 4484KB
// - 인덱스 트리: 80ms 4076KB
/*****************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#define INF (1000000001)
using namespace std;

int N, M;
int n_leaf;
vector<int> arr;
vector<int> treeMin, treeMax;

// 세그먼트 트리
#if 0
int MakeTreeMin(int s, int e, int idx) {
    if (s == e) return treeMin[idx] = arr[s];
    int m = (s + e) / 2;
    int l = MakeTreeMin(s, m, 2*idx);
    int r = MakeTreeMin(m+1, e, 2*idx+1);
    return treeMin[idx] = ((l < r) ? l : r);
}

int MakeTreeMax(int s, int e, int idx) {
    if (s == e) return treeMax[idx] = arr[s];
    int m = (s + e) / 2;
    int l = MakeTreeMax(s, m, 2*idx);
    int r = MakeTreeMax(m+1, e, 2*idx+1);
    return treeMax[idx] = ((l > r) ? l : r);
}

int Minimum(int s, int e, int idx, int qs, int qe) {
    if (qs > e || qe < s) return INF;
    if (qs <= s && e <= qe) return treeMin[idx];
    int m = (s + e)/2;
    int l = Minimum(s, m, 2*idx, qs, qe);
    int r = Minimum(m+1, e, 2*idx+1, qs, qe);
    return (l < r) ? l : r;
}

int Maximum(int s, int e, int idx, int qs, int qe) {
    if (qs > e || qe < s) return -1;
    if (qs <= s && e <= qe) return treeMax[idx];
    int m = (s + e)/2;
    int l = Maximum(s, m, 2*idx, qs, qe);
    int r = Maximum(m+1, e, 2*idx+1, qs, qe);
    return (l > r) ? l : r;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);

    cin >> N >> M;
    arr.resize(N);
    int depth = (int)ceil(log2(N));
    treeMin.resize(1 << depth + 1);
    treeMax.resize(1 << depth + 1);

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    MakeTreeMin(0, N-1, 1);
    MakeTreeMax(0, N-1, 1);

    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        if (a > b) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        cout << Minimum(0, N-1, 1, a-1, b-1) << " ";
        cout << Maximum(0, N-1, 1, a-1, b-1) << "\n";
    }
}
#endif


// 인덱스 트리
#if 1
void MakeTree() {
    for (int i = n_leaf-1; i > 0; i--) {
        treeMin[i] = (treeMin[2*i] < treeMin[2*i+1]) ? treeMin[2*i] : treeMin[2*i+1];
        treeMax[i] = (treeMax[2*i] > treeMax[2*i+1]) ? treeMax[2*i] : treeMax[2*i+1];
    }
}

int Minimum(int s, int e) {
    int min = INF;
    while (s <= e) {
        if (s % 2) min = (treeMin[s] < min) ? treeMin[s] : min;
        if (e % 2 == 0) min = (treeMin[e] < min) ? treeMin[e] : min;
        s = (s + 1) / 2;
        e = (e - 1) / 2;
    }
    return min;
}

int Maximum(int s, int e) {
    int max = 0;
    while (s <= e) {
        if (s % 2) max = (treeMax[s] > max) ? treeMax[s] : max;
        if (e % 2 == 0) max = (treeMax[e] > max) ? treeMax[e] : max;
        s = (s + 1) / 2;
        e = (e - 1) / 2;
    }
    return max;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("input.txt", "r", stdin);

    cin >> N >> M;
    for (n_leaf = 1; n_leaf < N; n_leaf <<= 1);
    treeMin.resize(n_leaf * 2);
    treeMax.resize(n_leaf * 2);

    for (int i = 0; i < n_leaf; i++) {
        if (i < N) {
            cin >> treeMin[i + n_leaf];
            treeMax[i + n_leaf] = treeMin[i + n_leaf];
        }
        else treeMin[i + n_leaf] = INF;
    }
    MakeTree();

    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        cout << Minimum(a-1+n_leaf, b-1+n_leaf) << " ";
        cout << Maximum(a-1+n_leaf, b-1+n_leaf) << "\n";
    }
}
#endif
