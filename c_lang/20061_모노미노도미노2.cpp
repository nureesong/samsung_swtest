/*************************************/
// [20061] 모노미노도미노2 (골드2)
// 구현 - 4ms, 2136KB (2시간 45분 소요)
// 파란색 보드를 90도 돌려서 보면 초록색 보드와 똑같다.
// 배열을 포인터로 넘겨서 블록 놓고 점수 계산하는 행동들을 하나의 함수로 구현
/*************************************/

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N;
int G[6][4], B[6][4];
struct BLOCK {
    int x, y, t;
}block[10000];


void Input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> block[i].t >> block[i].x >> block[i].y;
    }
}

void Print() {
    cout << "\nGreen\n";
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            cout << G[i][j] << " ";
        }
        cout << "\n";
    }
    
    cout << "\nBlue\n";
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            cout << B[i][j] << " ";
        }
        cout << "\n";
    }
}

void SetBlock(int (*arr)[4], int c, int t) {
    int r = (t < 3) ? 0 : 1;
    if (t != 2) {
        while (r < 6 && arr[r][c] == 0) r++;
        arr[r-1][c] = t;
        if (t == 3) arr[r-2][c] = t;
    }
    else {
        while (r < 6 && arr[r][c] == 0 && arr[r][c+1] == 0) r++;
        arr[r-1][c] = arr[r-1][c+1] = 2;
    }   
}

int GetScore(int (*arr)[4]) {
    vector<int> full; // 타일이 가득찬 행 번호 (최대 2개 연속)
    for (int r = 5; r >= 0; r--) {
        if (arr[r][0] && arr[r][1] && arr[r][2] && arr[r][3]) {
            full.push_back(r);
            memset(arr + r, 0, 4*4);
        }
    }

    if (full.empty()) return 0;

    // 빈 공간에 타일 내리기 (점수 칸만큼 끌어내리기)
    // 1점이면 i행만, 2점이면 i, i-1행 비어있음
    int cnt = full.size();
    for (int r = full[0]; r >= cnt; r--) {
        memcpy(arr + r, arr + r-cnt, 4*4);
    }
    memset(arr, 0, 4*4*cnt); // 전부 끌어내리면 0 / 0,1행은 빈 칸

    return cnt;
}

void ClearBuffer(int (*arr)[4]) {
    // 연한 칸에 블록 존재하는 개수 세기
    int cnt = 0;
    if (arr[0][0] || arr[0][1] || arr[0][2] || arr[0][3]) cnt++;
    if (arr[1][0] || arr[1][1] || arr[1][2] || arr[1][3]) cnt++;

    // cnt칸 만큼 밑으로 끌어내리기
    for (int r = 5; r >= cnt; r--) {
        memcpy(arr + r, arr + r-cnt, 4*4);
    }
    memset(arr, 0, 4*8);
}

int Simulation() {
    int score = 0;
    int rot_t[] = {0, 1, 3, 2};

    for (int i = 0; i < N; i++) {
        SetBlock(G, block[i].y, block[i].t);
        SetBlock(B, block[i].x, rot_t[block[i].t]);
        // cout << "\n----  i = " << i << "  ----";
        // Print();

        // 타일로 가득찬 행 찾기
        score += GetScore(G);
        score += GetScore(B);
        // cout << "\nscore = " << score;
        // Print();

        // 연한 칸 블록 처리
        ClearBuffer(G);
        ClearBuffer(B);
        // cout << "\nClear";
        // Print();
    }
    
    return score;
}

int CountBoard(int (*arr)[4]) {
    int cnt = 0;
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            if (arr[i][j]) cnt++;
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Input();
    
    cout << Simulation() << "\n";
    cout << CountBoard(G) + CountBoard(B) << "\n";
}
