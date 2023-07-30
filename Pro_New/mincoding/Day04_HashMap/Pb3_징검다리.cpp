// 징검다리 2개씩 묶어서 모든 합을 해시맵에 저장 -> 합이 0이 되는 값 조회 
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int N[4];
vector<int> V[4];
unordered_map<int, int> hm[2];

void JumpBetween(int a, int b) {
    int idx = a / 2;
    for (int i = 0; i < N[a]; i++) {
        for (int j = 0; j < N[b]; j++) {
            int sum = V[a][i] + V[b][j];
            hm[idx].find(sum) == hm[idx].end() ? hm[idx][sum] = 1 : hm[idx][sum]++;
        }
    }
}

int Solve() {
    JumpBetween(0, 1);
    JumpBetween(2, 3);

    int cnt = 0;
    for (auto it = hm[0].begin(); it != hm[0].end(); it++) {
        int cur = it->first;
        auto it_find = hm[1].find(-cur);
        if (it_find != hm[1].end()) cnt += it->second * it_find->second;
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N[0] >> N[1] >> N[2] >> N[3];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < N[i]; j++) {
            int num;
            cin >> num;
            V[i].push_back(num);
        }
    }
    cout << Solve() << "\n";
}
