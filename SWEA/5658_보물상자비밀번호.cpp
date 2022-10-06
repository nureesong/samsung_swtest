/******************************************/
// [5658] 보물상자 비밀번호
// 6ms, 13556KB - set을 통해 중복값 제거 및 내림차순 정렬
// substr 함수로 문자열을 N/4자리씩 끊기!
// std::stoi : str -> int (디폴트 10진수. 2,16진수 설정 가능) 
// 문자열의 표현범위가 int 범위에 맞아야 함!!
// ex) str -> long long: stoll 함수 사용하기
// 55분 소요
/******************************************/

#include <iostream>
#include <string>
#include <set>
using namespace std;

int N, K, L;
string inputS;
set<string, greater<string>> s;

void Input() {
	cin >> N >> K >> inputS;
}

int Solve() {
	s.clear();
	L = N / 4; // 숫자 길이

	for (int i = 0; i < L; i++) { // 시작 위치 (회전하는 효과)
		// i위치부터 L개씩 끊어서 숫자 4개로 분리
		for (int j = 0; j < 4; j++) {
			s.insert(inputS.substr(i + j*L, L));
		}
		inputS += inputS[i];
	}
  // k-1 번째로 큰 문자열 찾기
	auto it = s.begin();
	int cnt = K - 1;
	while (cnt--) it++;  
	return stoi(*it, nullptr, 16);  // 문자열 -> 16진수
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Input();
		cout << "#" << i << " " << Solve() << "\n";
	}
}
