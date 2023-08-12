#include <iostream>
using namespace std;

int N, M;
int P[100001]; // 도킹 가능한 게이트 번호 기록

int Find(int n) {
	if (P[n] == n) return n;
	return P[n] = Find(P[n]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) P[i] = i;

	int p;
	int cnt = 0;
	while (M--) {
		cin >> p;
		int root = Find(p);
		if (!root) break;
		P[root] = Find(root - 1);
		cnt++;
	}
	cout << cnt << "\n";
}
