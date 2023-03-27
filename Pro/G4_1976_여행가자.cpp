/***********************************/
// [1976] 여행가자 (골드4)
// - 유니온파인드. 재귀호출
// - 0ms 2316KB
/***********************************/

#include <iostream>
#include <set>
#include <vector>
using namespace std;

int N, M;
int A[200][200];  // Adjacency matrix (symmetric)
int root[200];
set<int> s; // Journey plan (오름차순 정렬)
vector<int> v; // 중복도시 제거 및 오름차순 정렬한 여행계획

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
    // Initialize
    for (int i = 1; i < N; i++) {
        root[i] = i;
    }
    for (int n : s) {
        v.push_back(n);
    }
    s.clear();
}

int find_root(int n) {
    if (n == root[n]) return n;
    root[n] = find_root(root[n]);
    return root[n];
}

void Union(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a < b) root[b] = a;
    else root[a] = b;
}

string Solve() {
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) { // upper triangular
            if (A[i][j] && root[i] != root[j]) {
                Union(i,j);
            }
        }
    }
    // 여행계획 Query
    // 현재 포인터가 가리키는 위치의 값과 그 다음 값을 같이 가져와서 isUnion 하고 싶은데
    // 둘이 같이 가져올 수 있나..?  -> 모르겠다 일단 벡터로 하자!
    int sz = v.size() - 1;
    string ans = "YES";
    for (int i = 0; i < sz; i++) {
        if (find_root(v[i]) != find_root(v[i+1])) { // <주의> root 배열에 최종 루트노드가 담겨있지 않음!
            ans = "NO";
            break;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    cout << Solve() << "\n";
}
