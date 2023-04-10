/*****************************************************/
// [5639] 이진 검색 트리 (골드5)
// - 트리 자료구조  : tree[현재노드] = {왼,오 자식 노드번호}
//   1) hash map: 36ms, 3280KB
//   2) 구조체 배열: 36ms, 10060KB
// - 데이터 무한개 입력
//   1) while (!cin.eof()) -> 벡터에 push_back 하니까 메모리 초과..
//   2) while (cin >> n)   -> Visual studio에서 안 될 수도?
/*****************************************************/

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> arr;
struct CHILD {
    int l, r;
};
unordered_map<int, CHILD> tree;

void Input() {
    int n;
    while (cin >> n) {
        arr.push_back(n);
    }
//    while (!cin.eof()) {
//        cin >> arr[N++];
//    }
}

// [s,e]에 대해 cur를 루트로 하는 서브트리 만들기
void Maketree(int s, int e, int cur) {
    if (s > e) return;

    int i = s; // i: 좌-우 서브트리 나눠지는 기점
    while (i <= e && arr[i] < cur) i++;

    // 왼쪽 서브트리가 존재하는 경우
    if (i > s) {
        tree[cur].l = arr[s];         // 왼쪽자식 추가
        tree.insert({arr[s], {0,0}}); // 왼쪽자식노드 키 생성
        Maketree(s+1, i-1, arr[s]); // 왼쪽자식을 루트로 갖는 서브트리 탐색
    }

    // 오른쪽 서브트리가 존재하는 경우
    if (i <= e) {
        tree[cur].r = arr[i];         // 오른쪽자식 추가
        tree.insert({arr[i], {0,0}}); // 오른쪽자식노드 키 생성
        Maketree(i+1, e, arr[i]); // 오른쪽자식을 루트로 갖는 서브트리 탐색
    }
}

void Postorder(int node) {
    if (tree[node].l) Postorder(tree[node].l);
    if (tree[node].r) Postorder(tree[node].r);
    cout << node << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    int root = arr[0];
    tree.insert({root, {0,0}}); // 루트노드 키 생성

    Maketree(1, arr.size()-1, root);
    Postorder(root);
}
