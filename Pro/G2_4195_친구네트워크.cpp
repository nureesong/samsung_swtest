/*****************************************************/
// [4195] 친구 네트워크 (골드2)
// - 유니온파인드: 100ms 18912KB
// - 엣지수 최대 10만 -> 노드수 최대 20만
/*****************************************************/

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int F;
int p[200000], cnt[200000];
unordered_map<string, int> num;


int find_root(int i) {
    if (i == p[i]) return i;
    return p[i] = find_root(p[i]);
}

void Union(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b) return;
    if (a < b) {
        p[b] = a;
        cnt[a] += cnt[b] + 1;
    }
    else {
        p[a] = b;
        cnt[b] += cnt[a] + 1;
    }
}

void Print(int* arr, int N) {
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

void Solve() {
    string s1, s2;
    int N = 0;
    for (int i = 0; i < F; i++) {
        cin >> s1 >> s2;
        if (num.find(s1) == num.end()) num[s1] = N++;
        if (num.find(s2) == num.end()) num[s2] = N++;
        Union(num[s1], num[s2]);
        cout << cnt[find_root(num[s1])] + 1 << "\n";
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) {
        cin >> F;
        num.clear();
        for (int i = 0; i < 2*F; i++) {
            p[i] = i;
            cnt[i] = 0;
        }
        Solve();
    }
}
