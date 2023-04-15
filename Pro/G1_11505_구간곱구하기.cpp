/*****************************************************/
// [11505] 구간 곱 구하기 (골드1)
// 인덱스 트리: 124ms 18408KB
// (a*b) % N == ((a%N) * (b%N)) % N
/*****************************************************/

#include <iostream>
#include <vector>
#define D (1000000007)
using namespace std;

int N, M, K;
int n_leaf;
vector<long long> tree;

void MakeTree() {
    for (int i = n_leaf-1; i > 0; i--) {
        tree[i] = ((tree[2*i] % D) * (tree[2*i+1] % D) % D);
    }
}

void Update(int i, int num) {
    tree[i] = num;
    while (i > 1) {
        i >>= 1;
        tree[i] = ((tree[2*i] % D) * (tree[2*i+1] % D) % D);
    }
}

int Product(int s, int e) {
    int rem = 1;
    while (s <= e) {
        if (s % 2) rem = (rem * (tree[s] % D)) % D;
        if (e % 2 == 0) rem = (rem * (tree[e] % D)) % D;
        s = (s + 1) / 2;
        e = (e - 1) / 2;
    }
    return rem;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;
    for (n_leaf = 1; n_leaf < N; n_leaf <<= 1);
    tree.resize(n_leaf * 2);

    for (int i = 0; i < n_leaf; i++) {
        if (i < N) cin >> tree[i+n_leaf];
        else tree[i+n_leaf] = 1;
    }
    MakeTree();

    int a, b; long long c;
    for (int i = 0; i < M+K; i++) {
        cin >> a >> b >> c;
        if (a == 1) Update(b-1+n_leaf, c);
        else cout << Product(b-1+n_leaf, c-1+n_leaf) << "\n";
    }
}
