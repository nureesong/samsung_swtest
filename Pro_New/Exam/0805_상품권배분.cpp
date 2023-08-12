#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int N, total;
unordered_map<int, int> P; // <부서ID, 부모ID>
unordered_map<int, int> CNT; // <부서ID, 본인+하위 인원수>
unordered_map<int, int> CHILD; // <부서ID, 하위부서 개수>
int R[1000]; // 루트노드
vector<int> rootCNT;

void init(int mN, int mId[], int mNum[]) {
    N = mN;
    total = 0;
    P.clear(); P[0] = 0;
    CNT.clear();
    CHILD.clear();

    for (int i = 0; i < N; i++) {
        int id = mId[i];
        int n = mNum[i];
        P[id] = id;
        CNT[id] = n;
        CHILD[id] = 0;
        R[i] = id;
    }
}

int find_root(int n, int change) {
    if (P[n] == n) {
        total += change;
        return n;
    }
    CNT[P[n]] += change;
    return find_root(P[n], change);
}

int add(int mId, int mNum, int mParent) {
    if (CHILD[mParent] >= 3) return -1;

    P[mId] = mParent;
    CNT[mId] = mNum;
    find_root(mId, mNum);
    CHILD[mParent]++;
    CHILD[mId] = 0;
    return CNT[mParent];
}

int remove(int mId) {
    if (find_root(mId, 0) == 0) return -1;

    int ans = CNT[mId];
    find_root(mId, -ans);
    P[mId] = 0;
    CHILD[P[mId]]--;
    return ans;
}

int Test(int L, int K) {
    int totalCoupon = 0;
    for (int i = 0; i < N; i++) {
        int cur = rootCNT[i] > L ? L : rootCNT[i];
        totalCoupon += cur;
        if (totalCoupon > K) return 0;
    }
    return 1;
}

int distribute(int K) {
    rootCNT.clear();
    rootCNT.resize(N, 0);
    int maxC = 0;
    for (int i = 0; i < N; i++) {
        int cur = CNT[R[i]];
        rootCNT[i] = cur;
        maxC = cur > maxC ? cur : maxC;
    }
    if (total <= K) return maxC;

    sort(rootCNT.begin(), rootCNT.end(), greater<int>());
    int s = 0, e = K;
    while (s <= e) {
        int m = (s + e) / 2;
        if (Test(m, K)) s = m + 1;
        else e = m - 1;
    }
    return e;
}
