// [방법1] (혼혈국가쌍, 인원수)를 해시맵으로 저장 -> O(N * M^2)  (N: 사람 수, M: 혼혈국가 수)
//  -> 해시맵을 만들어두기만 하면, 쿼리가 여러번 들어와도 조회 O(1)
// 이중 HashMap (188ms 2MB)
// 국가명 2개 연결시 중복 있다고 가정하면 이중 해시맵!
// 단일 HashMap (문자열 concat: 164ms 3MB)
// 국가명 2개 연결시 중복 없다고 가정하는 경우 A+B를 key로 설정
#if 1
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

int N;
// 국가명 2개 연결시 중복 없다고 가정하는 경우 A+B를 key로 설정
//unordered_map<string, int> hm;
// 국가명 2개 연결시 중복 있다고 가정하면 이중 해시맵!
unordered_map<int, unordered_map<int, int>> hm;
unordered_map<string, int> ID; // 국가명,번호
int id;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int n = 0; n < N; n++) {
        int num;
        cin >> num;
        vector<string> C;
        for (int j = 0; j < num; j++) {
            string s;
            cin >> s;
            C.push_back(s);
        }
        sort(C.begin(), C.end());

        for (int i = 0; i < num-1; i++) {
            string A = C[i];
            if (ID.find(A) == ID.end()) ID.insert({A, id++});
            int idA = ID[A];

            for (int j = i+1; j < num; j++) {
                string B = C[j];
                //string AB = A + B;
                //hm.find(AB) == hm.end() ? hm[AB] = 1 : hm[AB]++;
                if (ID.find(B) == ID.end()) ID.insert({ B,id++ });
                int idB = ID[B];
                hm[idA].find(idB) == hm[idA].end() ? hm[idA][idB] = 1 : hm[idA][idB]++;
            }
        }
    }

    string A, B;
    cin >> A >> B;
    if (A > B) swap(A,B);
    //cout << hm[A+B] << "\n";
    cout << hm[ID[A]][ID[B]] << "\n";
}
#endif

// [방법2] 사람별 [국가]: {혼혈국가 리스트}를 만들어놓고 쿼리 국가쌍에 해당하는 사람 세기 -> O(N * MlogM * Q)
// -> 쿼리가 들어올 때마다 O(N * MlogM)만큼 조회가 발생한다.
// Vector (for문 가지치기: 45ms, 16MB)
// Vector (find 함수: 42ms, 16MB) -> 같은 find()를 사용해도 벡터가 제일 빠르다.
// Set (find 함수: 55ms, 27MB)
#if 0
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int N;
vector<string> V[50000];
//set<string> S[50000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        while (num--) {
            string country;
            cin >> country;
            V[i].push_back(country);
            //S[i].insert(country);
        }
    }

    string A, B;
    cin >> A >> B;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
//        int chkA = 0;
//        int chkB = 0;
//        for (string country : V[i]) {
//            if (country == A) chkA++;
//            if (country == B) chkB++;
//            if (chkA == 1 && chkB == 1) {
//                cnt++;
//                break;
//            }
//        }

        auto it_begin = V[i].begin();
        auto it_end = V[i].end();
        if ((find(it_begin, it_end, A) != it_end) && (find(it_begin, it_end, B) != it_end)) cnt++;

//        auto it_end = S[i].end();
//        if (S[i].find(A) != it_end && S[i].find(B) != it_end) cnt++;
    }
    cout << cnt << "\n";
}
#endif
