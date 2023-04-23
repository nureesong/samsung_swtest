/*****************************************************/
// [4195] 친구 네트워크 (골드2)
// - 유니온파인드
// - OutOfBounds 에러!!!
/*****************************************************/

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int F;
//vector<int> p, cnt;
int p[100001], cnt[100001];
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

//void Print(vector<int> v) {
//    for (auto i : v) {
//        cout << i << " ";
//    }
//    cout << "\n";
//}

void Print(int* arr, int N) {
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

void Solve() {
    string a, b;
    int N = 0;
    for (int i = 0; i < F; i++) {
        cin >> a >> b;
        if (num.find(a) == num.end()) num.insert({a, N++});
        if (num.find(b) == num.end()) num.insert({b, N++});
        Union(num[a], num[b]);
        cout << "Union " << num[a] << " " << num[b] << "\n";
        Print(p, N);
        Print(cnt, N);
        cout << cnt[find_root(num[a])] + 1 << "\n";
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("input.txt", "r", stdin);

    int T;
    cin >> T;
    while (T--) {
        cin >> F;
        num.clear();
//        p.clear(); p.resize(F+1);
//        cnt.clear(); cnt.resize(F+1);
        for (int i = 0; i < 100001; i++) {
            p[i] = i;
            cnt[i] = 0;
        }

        Solve();
    }
}
