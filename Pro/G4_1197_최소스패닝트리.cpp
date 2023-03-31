/***********************************************/
// [1197] 최소 스패닝 트리 (골드4)
// - MST: O(E*logE) 40ms 4496KB
/***********************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int V, E;
struct EDGE {
    int a,b,c;
};
vector<EDGE> edge;
int p[10001]; // parent node (노드 시작번호 1번)

void Input() {
    cin >> V >> E;
    int A, B, C;
    for (int i = 0; i < E; i++) {
        cin >> A >> B >> C;
        edge.push_back({A,B,C});
    }
}

bool comp(EDGE &e1, EDGE &e2) {
    return e1.c < e2.c;
}

int find_root(int x) {
    if (x == p[x]) return x;
    return p[x] = find_root(p[x]);
}

void Union(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a < b) p[b] = a;
    else p[a] = b;
}

int Kruskal() {
    // Initialize
    for (int i = 1; i <= V; i++) {
        p[i] = i;
    }
    int sum = 0, cnt = 0;
    sort(edge.begin(), edge.end(), comp);

    for (EDGE e : edge) {
        if (find_root(e.a) == find_root(e.b)) continue;

        Union(e.a, e.b);
        sum += e.c;
        cnt++;
        if (cnt == V-1) break;
    }
    return sum;
}

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   cout.tie(0);

   freopen("input.txt", "r", stdin);

   Input();
   cout << Kruskal() << "\n";
}
