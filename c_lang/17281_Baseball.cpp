/***********************************/
// [17281] Baseball⚾ (골드4)
// DFS - 순열: 264ms, 2024KB
// 16:24 ~ 17:25 (1시간 소요)
/***********************************/
// 모든 시작 인덱스 0으로!!
// 선수 번호: 0~8번
// 타순: 0~8번 타자(4번타자 -> 3번타자!)
// **3번 타자는 항상 0번 선수로 고정**

#include <iostream>
using namespace std;

int N;
// 행: 이닝, 열: 선수번호 -> 각 선수가 각 이닝에서 얻는 결과 
int arr[50][9]; // 0:아웃, 1~3:1~3루타, 4:홈런
int pick[9]; // 타순 
int vis[9];  // n번 선수의 타순 결정여부

int flag[4]; // 1,2,3루 주자 존재여부
int sol;     // 최대 점수

int PlayGame() {
    int s = 0; // 0번 타자부터 시작
    int score = 0;
    
    for (int i = 0; i < N; i++) {
        flag[3] = flag[2] = flag[1] = 0; // 이닝이 시작될 때는 주자가 없다.
        int out = 0;                     // 아웃 카운트 리셋
        
        while (out < 3) {
            int r = arr[i][pick[s]]; // 현재 타자의 결과
            
            if (r == 4) { // 홈런: 타자, 모든 주자 홈까지 진루
                score += (flag[3] + flag[2] + flag[1] + 1);
                flag[3] = flag[2] = flag[1] = 0;
            }
            else if (r == 3) {
                score += (flag[3] + flag[2] + flag[1]);
                flag[3] = 1;   // 타자는 3루까지 진루
                flag[2] = flag[1] = 0;
            }
            else if (r == 2) { 
                score += (flag[3] + flag[2]); // 2,3루 주자 홈 도착
                flag[3] = flag[1]; // 1루 주자는 3루에 도착
                flag[2] = 1;       // 타자는 2루에 도착
                flag[1] = 0;       // 1루는 비어있음
            }
            else if (r == 1) { // 1루씩 진루
                score += flag[3];
                flag[3] = flag[2];
                flag[2] = flag[1];
                flag[1] = 1;
            }
            else out++;  // 아웃: 주자는 그대로, 아웃 카운트+1
            s = (s + 1) % 9;
        }
    }
    return score;
}

void DFS(int n) {
    if (n == 9) {
        int ret = PlayGame();
        sol = (ret > sol) ? ret : sol;
        return;
    }

    if (n == 3) DFS(4);  // 3번 타자는 이미 결정 -> 4번 타자 고르기
    else {  
        // n번째 타자로 1~8번 선수 중 선택
        for (int i = 1; i < 9; i++) {
            if (vis[i]) continue;
        
            pick[n] = i;
            vis[i] = 1;
            DFS(n + 1);
            vis[i] = 0;
        }
    }
}

void Input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int n = 0; n < 9; n++) {
            cin >> arr[i][n];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();

    vis[0] = 1; // 3번 타자는 항상 0번 선수로 고정
    pick[3] = 0;
    DFS(0);
    cout << sol << "\n";
}
