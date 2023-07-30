// Vector + Sort -> 60ms 3MB
// PQ -> 59ms 3MB

// Vector + Sort
#if 0
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, Q;
struct TREE {
    int id, x1, x2;
};
vector<TREE> tree;
int group;
int G[100000];

bool comp(TREE &a, TREE &b) {
    if (a.x1 == b.x1) return a.x2 < b.x2;
    return a.x1 < b.x1;
}

void Solve() {
    int cur = tree[0].x2;
    for (int i = 0; i < N-1; i++) {
        TREE next = tree[i+1];
        if (cur < next.x1) group++;
        if (cur <= next.x2) cur = next.x2;
        G[next.id] = group;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        int x1, x2, y;
        cin >> x1 >> x2 >> y;
        tree.push_back({ i,x1,x2 });
    }
    sort(tree.begin(), tree.end(), comp);
    Solve();

    while (Q--) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << (G[a] == G[b]) << "\n";
    }
}
#endif

// PQ
#if 1
#include <iostream>
#include <queue>
using namespace std;

int N, Q;
struct STATUS {
    int x1, x2, id;
};
struct COMP {
    bool operator()(STATUS &a, STATUS &b) {
        if (a.x1 == b.x1) return a.x2 > b.x2;
        return a.x1 > b.x1;
    }
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;
int G[100001];
int group;

void Jump() {
    int pos = pq.top().x2; pq.pop();

    while (!pq.empty()) {
        STATUS next = pq.top(); pq.pop();
        if (pos < next.x1) group++;
        if (pos < next.x2) pos = next.x2;
        G[next.id] = group;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> Q;
    int x1, x2, y;
    for (int i = 1; i <= N; i++) {
        cin >> x1 >> x2 >> y;
        pq.push({ x1,x2,i });
    }
    Jump();

    int a, b;
    while (Q--) {
        cin >> a >> b;
        cout << (G[a] == G[b]) << "\n";
    }
}
#endif
