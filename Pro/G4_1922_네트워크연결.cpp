/***********************************************/
// [1922] 네트워크 연결 (골드4)
// - MST (Minimum Spanning Tree)
//   모든 노드를 포함하면서 사이클이 존재하지 않는다. 간선은 항상 (N-1)개
// - Kruskal 알고리즘 (Greedy approach)
//   1. 비용 오름차순으로 엣지 정렬
//   2. 엣지 선택시 사이클이 발생하지 않으면(루트노드 다르면) MST에 추가(union 연산)
//   => MST에 포함된 엣지 (N-1)개의 비용 총합이 최소비용이다.
// - O(E*logE): 32ms 4460KB
/***********************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;  // N: 10^3, M: 10^5
struct EDGE {
    int a, b, cost;
};
vector<EDGE> E;
int p[1000];

void Input() {
    cin >> N >> M;
    int a, b, c;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;
        E.push_back({--a,--b,c});
    }
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

bool comp(EDGE &e1, EDGE &e2) {
    return e1.cost < e2.cost;  // 오름차순
}

int Kruskal() {
    // Initialize
    for (int i = 1; i < N; i++) {
        p[i] = i;
    }

    // 1. 비용 오름차순으로 엣지 정렬
    sort(E.begin(), E.end(), comp);

    // 2. 현재 엣지 선택시 사이클 발생 확인 -> 발생하지 않으면 MST에 포함시키기
    int sum = 0, cnt = 0;
    for (auto e : E) {
        if (e.a == e.b) continue;
        if (find_root(e.a) == find_root(e.b)) continue;

        Union(e.a, e.b);
        sum += e.cost;
        cnt++;
        if (cnt == N-1) break;
    }
    return sum;
}


int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   cout.tie(0);

   Input();
   cout << Kruskal() << "\n";
}
