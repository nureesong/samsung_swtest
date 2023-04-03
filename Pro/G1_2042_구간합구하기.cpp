/*****************************************************/
// [2042] 구간 합 구하기 (골드1)
// - 인덱스 트리, 세그먼트 트리 (둘이 같은건가??)
// int(4B): 2^31, long long(8B): 2^63
// 2의 제곱수: 1부터 왼쪽으로 비트 한칸씩 이동 (<< 1)
// 2로 나눈 몫: 오른쪽으로 비트 한칸 이동 (>> 1)
// Out of Bounds 에러남....
/*****************************************************/

#include <iostream>
#include <vector>
using namespace std;

int N, M, K;
vector<long long> arr; // 8B * 100만 = 800MB?? 메모리 초과 아닌가??
int n_leaf;
vector<long long> tree;
struct QUERY {
    int a, b;
    long long c;
}Q[10000];


void Input() {
    cin >> N >> M >> K;
    arr.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < M+K; i++) {
        cin >> Q[i].a >> Q[i].b >> Q[i].c;
    }
}

void Print() {
    for (auto i : tree) {
        cout << i  << " ";
    }
    cout << "\n";
}

void MakeTree() {
    // 1. leaf node의 개수 = N보다 큰, 가장 작은 2의 제곱수
    n_leaf = 1;
    while (n_leaf < N) {
        n_leaf <<= 1;
    }
    tree.resize(n_leaf * 2); // 트리의 노드수 = 리프노드 수 * 2

    // 2. 구간 합 계산 : O(N * logN)
    // n_leaf = 리프노드의 시작 인덱스
    for (int i = 0; i < N; i++) {
        long long num = arr[i];
        int idx = n_leaf + i;

        while (idx >= 1) {
            tree[idx] += num;
            idx >>= 1;  // 2로 나누는 것과 동일!
        }
    }
}

void update(int i, long long num) {
    int idx = i + n_leaf;
    long long diff = num - arr[i];
    while (idx >= 1) {
        tree[idx] += diff;
        idx >>= 1;
    }
}

long long interval_sum(int s, int e) {
    s += n_leaf;
    e += n_leaf;

    long long sum = 0;
    while (s <= e) {
        if (s % 2) sum += tree[s]; // 시작인덱스가 홀수면 리프노드값 더하기
        if (e % 2 == 0) sum += tree[e]; // 끝인덱스가 짝수면 리프노드값 더하기
        s = (s + 1) / 2;  // 오른쪽 리프노드의 부모노드
        e = (e - 1) / 2;  // 왼쪽 리프노드의 부모노드
    }
    return sum;
}

void Solve() {
    int sz = M + K;
    for (int i = 0; i < sz; i++) {
        if (Q[i].a == 1) {
            update(Q[i].b-1, Q[i].c);
        }
        else {
            cout << interval_sum(Q[i].b-1, Q[i].c-1) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    MakeTree();
    Solve();
}
