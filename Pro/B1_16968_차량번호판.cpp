/***********************************/
// [16968] 차량번호판 (브론즈1)
// 고등수학 조합론
/***********************************/

#include <iostream>
#include <string>
using namespace std;

string S;

void Input() {
    cin >> S;
}

int Solve() {
    int sol = 1;
    char prev = 'a';
    
    for (char cur : S) {
        int n = (cur == 'd') ? 10 : 26;
        if (cur == prev) n--;
        sol *= n;
        prev = cur;
    }
    return sol;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    Input();
    cout << Solve() << "\n";
}
