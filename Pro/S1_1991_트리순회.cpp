/*****************************************************/
// [1991] 트리 순회 (실버1)
// 0ms, 2020KB
// 전위순회: 루트 - 왼쪽자식 - 오른쪽자식
// 중위순회: 왼쪽자식 - 루트 - 오른쪽자식
// 후위순회: 왼쪽자식 - 오른쪽자식 - 루트
/*****************************************************/

#include <iostream>
#include <string>
using namespace std;

string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int N;
struct CHILD {
    int l, r;
}T[26];

void Input() {
    cin >> N;
    char a,b,c;
    for (int i = 0; i < N; i++) {
        cin >> a >> b >> c;
        a -= 'A';
        T[a].l = (b == '.') ? -1 : b-'A';
        T[a].r = (c == '.') ? -1 : c-'A';
    }
}

void Preorder(int node) {
    if (node == -1) return;
    cout << alphabet[node];
    Preorder(T[node].l);
    Preorder(T[node].r);
}

void Inorder(int node) {
    if (node == -1) return;
    Inorder(T[node].l);
    cout << alphabet[node];
    Inorder(T[node].r);
}

void Postorder(int node) {
    if (node == -1) return;
    Postorder(T[node].l);
    Postorder(T[node].r);
    cout << alphabet[node];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();

    // 루트노드는 항상 A
    Preorder(0);  cout << "\n";
    Inorder(0);   cout << "\n";
    Postorder(0); cout << "\n";
}
