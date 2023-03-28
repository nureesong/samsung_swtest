/**************************************************/
// [20040] 사이클게임 (골드4)
// - 유니온파인드: 276ms 16388KB
// - 서로소 집합을 활용한 무방향 그래프 사이클 판별
//   (방향 그래프에서의 사이클 여부는 DFS로 판별)
// - 각각의 엣지에 대해 두 노드의 루트노드가
//   서로 다르면 Union 수행, 같으면 Cycle 발생!
/**************************************************/

#include <iostream>
#include <vector>
using namespace std;

int N, M;  // N: 50만, M: 100만
int p[500000];
struct QUERY {
    int a, b;
};
vector<QUERY> Q;

void Input() {
    cin >> N >> M;
    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        Q.push_back({a,b});
    }
    // Initialize
    for (int i = 1; i < N; i++) {
        p[i] = i;
    }
}

int find_root(int x) {
    if (x == p[x]) return x;
    return p[x] = find_root(p[x]); // 재귀호출 -> p[x] 갱신 -> 리턴
}

void Union(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a < b) p[b] = a;
    else p[a] = b;
}

int Solve() {
    int cycle = 0;  // cycle이 처음으로 만들어진 차례
    for (int i = 0; i < M; i++) {
        if (find_root(Q[i].a) == find_root(Q[i].b)) {
            cycle = i+1;
            break;
        }
        Union(Q[i].a, Q[i].b);
    }
    return cycle;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("input.txt", "r", stdin);

    Input();
    cout << Solve() << "\n";
}
