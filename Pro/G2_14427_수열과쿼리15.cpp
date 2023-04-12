/*****************************************************/
// [14427] 수열과 쿼리 15 (골드2)
// - 인덱스 트리: 40ms 4072KB
/*****************************************************/

#include <iostream>
#include <vector>
#define INF (1000000001)
using namespace std;

int N, M;
int n_leaf;
struct NODE {
    int v, i; // i: 0 ~ N-1 (원본수열의 인덱스)
};
vector<NODE> tree;


void MakeTree() {
    for (int i = N + n_leaf; i < tree.size(); i++) {
        tree[i] = {INF, i-n_leaf};
    }
    for (int i = n_leaf-1; i > 0; i--) {
        if (tree[2*i].v != tree[2*i+1].v) {
            tree[i] = (tree[2*i].v < tree[2*i+1].v) ? tree[2*i] : tree[2*i+1];
        }
        else { // 값이 같은 경우 더 작은 인덱스로!
            tree[i] = (tree[2*i].i < tree[2*i+1].i) ? tree[2*i] : tree[2*i+1];
        }
    }
}

void Update(int i) {
    while (i > 0) {
        if (tree[2*i].v != tree[2*i+1].v) {
            tree[i] = (tree[2*i].v < tree[2*i+1].v) ? tree[2*i] : tree[2*i+1];
        }
        else { // 값이 같은 경우 더 작은 인덱스로!
            tree[i] = (tree[2*i].i < tree[2*i+1].i) ? tree[2*i] : tree[2*i+1];
        }
        i >>= 1;
    }
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    cin >> N;
    for (n_leaf = 1; n_leaf < N; n_leaf <<= 1);
    tree.resize(2*n_leaf);
    for (int i = 0; i < N; i++) {
        int value;
        cin >> value;
        tree[i + n_leaf] = {value, i};
    }
    MakeTree();

    cin >> M;
    int n, i, v;
    for (int m = 0; m < M; m++) {
        cin >> n;
        if (n == 1) {
            cin >> i >> v;
            int idx = i-1 + n_leaf;
            tree[idx].v = v; // 리프노드 값 변경
            Update(idx/2);
        }
        else cout << tree[1].i + 1 << "\n";
    }
}
