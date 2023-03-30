/***********************************/
// [1976] 여행가자 (골드4)
// - 유니온파인드. 재귀호출
// - set iterator: 0ms 2180KB
// - vector: 0ms 2316KB
/***********************************/

#include <iostream>
#include <set>
#include <vector>
using namespace std;

int N, M;
int A[200][200]; // Adjacency matrix (symmetric)
int p[200];      // parent node
set<int> s;      // Journey plan (중복제거,오름차순 정렬)
// vector<int> v;   


void Input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }
    int x;
    while (!cin.eof()) {
        cin >> x;
        s.insert(--x);
    }
//     for (int n : s) {
//         v.push_back(n);
//     }
}

int find_root(int n) {
    if (n == p[n]) return n;
    return p[n] = find_root(p[n]);
}

void Union(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a < b) p[b] = a;
    else p[a] = b;
}

string Solve() {
    // Initialize
    for (int i = 1; i < N; i++) {
        p[i] = i;
    }
    // Edge Connection
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) { // upper triangular
            if (A[i][j] && p[i] != p[j]) {
                Union(i,j);
            }
        }
    }

    // 여행계획 Query
    // 첫번째 도시의 루트노드와 나머지 도시들의 루트노드가 같은지 비교
    // 1. set iterator
    set<int>::iterator it = s.begin();
    int first = find_root(*it++); // 첫번째 도시의 루트노드
    while (it != s.end() && first == find_root(*it)) {
        it++;
    }
    if (it != s.end()) return "NO";
    return "YES";

    // 2. vector
//    int sz = v.size();
//    int first = find_root(v[0]);
//    for (int i = 1; i < sz; i++) {
//        if (find_root(v[i]) != first) return "NO";
//    }
//    return "YES";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    cout << Solve() << "\n";
}
