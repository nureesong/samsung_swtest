/**********************************/
// [14889] 스타트와 링크 (실버2) - 조합
// DFS ("10819. 차이를 최대로"와 비슷)
// 1번 사원은 반드시 스타트 팀에 고정
// 68ms : 스타트 팀원이 전부 결정된 후에 각 팀의 능력치 계산
// 8ms : 팀원이 추가될 때마다 기존 팀원들과의 능력치 합산하기
/**********************************/

// 스타트 팀원 전부 결정된 후 마지막에 능력치 계산
#if 0
#include <iostream>
#include <cmath>
using namespace std;

int N;
int arr[20 + 5][20 + 5]; // (1,1)부터 시작

int vis[20 + 5];  // 1: 스타트팀, 0: 링크팀
int mindiff = 0x7fffffff; // 두 팀의 능력치 차이

void DFS(int s, int cnt) {
    if (mindiff == 0) return;

    if (cnt == N/2) {
        int sumS = 0, sumL = 0;

        for (int i = 1; i < N; i++) {
            for (int j = i+1; j <= N; j++) {
                if (vis[i] && vis[j]) {
                    sumS += arr[i][j];
                }

                if (!vis[i] && !vis[j]) {
                    sumL += arr[i][j];
                }
            }
        }

        if (abs(sumS - sumL) < mindiff) mindiff = abs(sumS - sumL);
        return;
    } 

    //if (s > N) return; // cnt 조건문 앞에 두면 min 갱신 안돼서 틀림!!
    // 사실 필요 없음: 어차피 for문 i <= N 조건 때문에 진입 안하고 그대로 함수 종료

    for (int i = s; i <= N; i++) {
        if (vis[i]) continue;

        vis[i] = 1;
        DFS(i + 1, cnt + 1);
        vis[i] = 0;
    }    
}

void Input() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> arr[i][j];
        }
    }

    // 능력치 계산 시 대칭인 원소를 더하므로,
    // 처음부터 S_ij에 S_ji 를 미리 더해놓고 행렬의 upper triangle 부분만 사용
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            arr[i][j] += arr[j][i];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();

    vis[1] = 1;
    DFS(2, 1);

    cout << mindiff << "\n";
}
#endif


// 각 팀에 팀원이 추가될 때마다 기존 팀원들과의 능력치 합산하기
// 각 사원마다 두 가지 팀 선택권(경우의 수)이 있다.
#if 1
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int N;
int S[20 + 5][20 + 5]; // (1,1)부터 시작

vector<int> team[2];      // 팀원들 번호  (0: 스타트팀, 1: 링크팀)
int mindiff = 0x7fffffff; // 두 팀의 능력치 차이

int AddPower(int n, int i) {
    int power = 0;
    for (auto t : team[i]) {
        power += (S[t][n] + S[n][t]);
    }
    return power;
}

// n번 사원의 팀 배정 후, 해당 팀에 이미 선택된 팀원들과의 능력치 합산하기
void DFS(int n, int power0, int power1) {
    // 한 번이라도 두 팀의 능력치가 같았다면 최솟값 0이므로 탐색 중단
    if (mindiff == 0) return;

    // 1 ~ N번 사원 전부 팀 배정 완료
    if (n > N) {
        if (abs(power0 - power1) < mindiff) mindiff = abs(power0 - power1);
        return;
    } 

    // n번 사원을 0, 1번 팀 중 어디에 배정할 지 탐색
    for (int t = 0; t < 2; t++) {
        if (team[t].size() == N/2) continue;
        
        team[t].push_back(n);
        
        int plus = AddPower(n, t); // n번 사원이 t번 팀을 선택했을 때 팀에 더해질 능력치
        if (t == 0) DFS(n + 1, power0 + plus, power1);
        else DFS(n + 1, power0, power1 + plus);
        
        // 다음 경우의 수 탐색을 위해 복원
        team[t].pop_back();
    }
}

void Input() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> S[i][j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    
    // 1번 선수를 무조건 스타트 팀에 고정하고 2번 선수부터 탐색
    team[0].push_back(1);
    DFS(2, 0, 0);

    cout << mindiff << "\n";
}
#endif
