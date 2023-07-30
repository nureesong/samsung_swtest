#include <iostream>
//#include <map>
#include <set>
using namespace std;

int N, M;
set<int> Item; // set 쓰면 되는데 왜 map으로 하라 했지??

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    int num;
    for (int i = 0; i < M; i++) {
        cin >> num;
        Item.insert(num);
    }
    int cnt = 0;
    int level;
    for (int i = 0; i < N; i++) {
        cin >> level;
        auto it_upper = Item.upper_bound(level);  // level을 초과하는 값의 위치
        if (it_upper == Item.begin()) break;
        cnt++;
        Item.erase(--it_upper);
    }
    cout << cnt << "\n";
}


//============  Map 사용  ===========
#if 0
int N, M;
map<int, int, greater<int>> Item; // key: 제한레벨, value: 배급여부(1: 배급완료)
int Level[100000];

int Solve() {
    auto it_begin = Item.begin();
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        auto it_upper = Item.lower_bound(Level[i]);  // level 이상인 값이 처음 등장하는 위치
        
        int flag = 0;
        for (auto it = it_upper; it != Item.end(); it++) {
            if (!(*it).second) {
                it->second = 1;
                cnt++;
                flag = 1;
                break;
            }
        }
        if (!flag) return cnt;
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    int num;
    for (int i = 0; i < M; i++) {
        cin >> num;
        Item.insert({ num,0 });
    }
    for (int i = 0; i < N; i++) {
        cin >> Level[i];
    }
    cout << Solve() << "\n";
}
#endif
