/*********************************************************/
// [14428] 수열과 쿼리 16 (골드1)
// 인덱스트리: 52ms 4072KB
// 트리에 최소일 때의 인덱스를 저장한다.
// 좌우 자식노드 비교하여 부모노드를 결정할 때, 최솟값 + 인덱스 둘다 비교!
/*********************************************************/

#include <iostream>
#include <vector>
#define INF (1000000001)
using namespace std;

int N, M, n_leaf;
struct NODE {
    int num, idx;
};
vector<NODE> tree; // 인덱스 저장

void MakeTree() {
    for (int i = n_leaf-1; i > 0; i--) {
        int l = 2*i, r = 2*i + 1;
        tree[i] = (tree[l].num <= tree[r].num) ? tree[l] : tree[r];
    }
}

void Update(int idx, int value) {
    tree[idx].num = value;
    while (idx > 1) {
        idx >>= 1;
        int l = 2*idx, r = 2*idx + 1;
        tree[idx] = (tree[l].num <= tree[r].num) ? tree[l] : tree[r];
    }
}

int Find(int s, int e) {
    NODE ans = {INF, -1};
    while (s <= e) {
        if (s % 2) {
            if (tree[s].num < ans.num || (tree[s].num == ans.num && tree[s].idx < ans.idx)) {
                ans = tree[s];
            }
            s++;
        }
        if (e % 2 == 0) {
            if (tree[e].num < ans.num || (tree[e].num == ans.num && tree[e].idx < ans.idx)) {
                ans = tree[e];
            }
            e--;
        }
        s = (s+1) / 2;
        e = (e-1) / 2;
    }
    return ans.idx;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    n_leaf = 1;
    while (n_leaf < N) n_leaf <<= 1;
    tree.resize(2*n_leaf);

    for (int i = 0; i < N; i++) {
        cin >> tree[n_leaf + i].num;
        tree[n_leaf + i].idx = i+1;
    }
    for (int i = N; i <= n_leaf; i++) tree[i + n_leaf].num = INF;
    MakeTree();
    
    cin >> M;
    int a, b, c;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;
        if (a == 1) Update(b-1+n_leaf, c);
        else cout << Find(b-1+n_leaf, c-1+n_leaf) << "\n";
    }
}
