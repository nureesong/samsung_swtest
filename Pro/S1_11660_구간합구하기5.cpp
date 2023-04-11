/*****************************************************/
// [11660] 구간 합 구하기5 (실버1)
// 2차원 Prefix sum, DP: 128ms, 7688KB
// N^2 = 2^20, 한 칸 당 1000 = 약 2^10
// -> 총합 최대 2^30 -> int로 가능
/*****************************************************/

#include <iostream>
#include <vector>
using namespace std;

int N, M;
int psum[1025][1025];
struct QUERY {
    int x1, y1, x2, y2;
};
vector<QUERY> Q;

void Input() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> psum[i][j];
            psum[i][j] += (psum[i][j-1] + psum[i-1][j] - psum[i-1][j-1]);
        }
    }
    Q.resize(M);
    for (int i = 0; i < M; i++) {
        cin >> Q[i].x1 >> Q[i].y1 >> Q[i].x2 >> Q[i].y2;
    }
}

void Solve() {
    for (auto q : Q) {
        cout << psum[q.x2][q.y2] - psum[q.x1-1][q.y2] -psum[q.x2][q.y1-1] + psum[q.x1-1][q.y1-1] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    Solve();
}
