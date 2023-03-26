/*************************************/
// [1717] 집합의 표현 (골드5)
// - 유니온파인드. 재귀호출
// - 인접한 부모노드 기록: 63%에서 시간초과
// - 루트노드 기록: 36ms, 7496KB
/*************************************/

#include <iostream>
#include <vector>
using namespace std;

int N, M;       // N: 10^6, M: 10^5
int p[1000001]; // 루트노드 저장
struct QUERY{
    int q, a, b;
}Q[100000];

void Input() {
    cin >> N >> M;
    int q,a,b;
    for (int i = 0; i < M; i++) {
        cin >> q >> a >> b;
        Q[i] = {q,a,b};
    }
    // Initialize root node
    for (int i = 1; i <= N; i++) {
        p[i] = i;
    }
}

int findRoot(int x) {
    if (x == p[x]) return x;
    p[x] = findRoot(p[x]); // 부모의 부모를 재귀적으로 탐색하여 찾은 루트노드를 p 배열에 저장
    return p[x];
}

void Union(int a, int b) {
    a = findRoot(a);  // a의 루트노드
    b = findRoot(b);  // b의 루트노드
    // 루트노드 번호가 작은 쪽으로 합친다.
    if (a < b) p[b] = a;
    else p[a] = b;
}

void Solve() {
    for (int i = 0; i < M; i++) {
        if (Q[i].q) {
            cout << (findRoot(Q[i].a) == findRoot(Q[i].b) ? "YES\n" : "NO\n");
        }
        else {
            if (Q[i].a == Q[i].b) continue;
            Union(Q[i].a, Q[i].b);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    Solve();
}
