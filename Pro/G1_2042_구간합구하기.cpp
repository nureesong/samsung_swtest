/*****************************************************/
// [2042] 구간 합 구하기 (골드1)
// 인덱스 트리: O(N + Q*logN)  204ms, 18729KB
// N = 10^6 = 2^20 --> tree 최대크기 = 2^21
// 처음부터 tree에 입력받으면 arr 배열 필요없음!
// 2의 제곱수: 1부터 왼쪽으로 비트 한칸씩 이동 (<< 1)
// 2로 나눈 몫: 오른쪽으로 비트 한칸 이동 (>> 1)
/*****************************************************/

#include <iostream>
#include <vector>
using namespace std;

int N, M, K;
int n_leaf;  // 리프노드 시작인덱스 = 2^ceil(log2 N)
vector<long long> tree; //
struct QUERY {
    int a, b;
    long long c;
}Q[20000];


void Input() {
    cin >> N >> M >> K;
    // N보다 큰, 가장 작은 2의 제곱수
    for (n_leaf = 1; n_leaf < N; n_leaf <<= 1);  // O(logN)
    tree.resize(n_leaf * 2); // 트리 전체 노드수 = 리프노드 수 * 2

    for (int i = 0; i < N; i++) {
        cin >> tree[i + n_leaf];
    }
    for (int i = 0; i < M+K; i++) {
        cin >> Q[i].a >> Q[i].b >> Q[i].c;
    }
}

// [트리 생성] Bottom-up 방식 O(N)
void MakeTree() {
    for (int i = n_leaf-1; i > 0; i--) {
        tree[i] = tree[2*i] + tree[2*i + 1];
    }
}

// O(logN)
void update(int i, long long num) {
    long long diff = num - tree[i];
    while (i >= 1) {
        tree[i] += diff;
        i >>= 1;
    }
}

// range query : O(logN)
long long interval_sum(int s, int e) {
    long long sum = 0;
    while (s <= e) {
        if (s % 2) sum += tree[s];       // 시작 인덱스가 홀수이면 리프노드값 더하기
        if (e % 2 == 0) sum += tree[e];  //  끝 인덱스가 짝수이면 리프노드값 더하기
        s = (s + 1) / 2;  // s의 오른쪽 노드의 부모노드
        e = (e - 1) / 2;  // e의 왼쪽 노드의 부모노드
    }
    return sum;
}

void Solve() {
    for (int i = 0; i < M+K; i++) {
        if (Q[i].a == 1) update(Q[i].b-1 + n_leaf, Q[i].c);
        else cout << interval_sum(Q[i].b-1 + n_leaf, Q[i].c-1 + n_leaf) << "\n";
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
