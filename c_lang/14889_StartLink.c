/***********************************************************/
// [14889] 스타트와 링크 (Silver 2)
// 등번호가 1번부터 시작하므로 능력치 정보 S와 team1,2의 인덱스도 1부터 시작
// ---- Combination 연산 재귀 구현 ----
// team1에 항상 N을 포함시키고, 나머지 1 ~ N-1 중에 (N/2 - 1)개만 선택한다.
// team1 구성이 끝나면 선택받지 않은 나머지 N/2명이 자동으로 team2가 된다.
// ---- 팀 능력치 합 계산 ----
// combination으로 팀원 선택 시 번호가 오름차순이므로
// S[i][j] = S_ij + S_ji 으로 바꿔두고 upper triangle만 사용한다.
// 즉, i < j인 두 명이 한 팀일 때 S[i][j]만 읽어오면 된다.
/***********************************************************/

#include <stdio.h>

int N;
int S[20+2][20+2];
int arr[20 + 2];
int team1[10 + 2], team2[10 + 2];
int min_diff = 200000;

void input(void) {
    scanf("%d", &N);
    
    // Initialize
    for (int i = 1; i <= N; i++) arr[i] = i;
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &S[i][j]);
            // 팀 번호가 오름차순이므로 upper triangle만 사용하기 위해 S_ij와 S_ji 더하기
            S[j][i] += S[i][j];
        }
    }
}

int is_team1(int i) {
    for (int j = 1; j <= N/2; j++) {
        if (i == team1[j]) return 1;
    }
    return 0;
}

int team_score(int *p) {
    int sum = 0;
    
    for (int i = 1; i < N/2; i++) {
        for (int j = i + 1; j <= N/2; j++) {
            sum += S[p[i]][p[j]];
        }
    }
    return sum;
}

void combination(int n, int r) {
    int s1, s2, cnt, diff;
    
    if (r == 0) {
        // team1이 완성되었으니 나머지 번호로 team2를 구성
        cnt = 1;
        for (int i = 1; i < N; i++) {
            if (!is_team1(i)) {team2[cnt] = i; cnt++;}
        }
      
        // 각 팀 능력치 차이 계산
        s1 = team_score(team1);
        s2 = team_score(team2);

        diff = (s1 > s2) ? s1 - s2 : s2 - s1;
        if (diff < min_diff) min_diff = diff;
    }
    else if (n < r) {
        return;
    }
    else {
        team1[r] = n;
        combination(n - 1, r - 1);
        combination(n - 1, r);
    }
}

int main(void) {
    input();
    
    // team1에 항상 N을 포함시키고, 나머지 1 ~ N-1 중에 (N/2 - 1)개만 선택한다.
    team1[N/2] = N;
    combination(N - 1, N/2 - 1);  // 마지막 값부터 N으로 고정시키는 방식: 456 -> 356 -> 256 ...
    //combination_head(1, 1);  // 맨 앞부터 1로 고정시키는 방식: 123 -> 124 -> 125 ...
    
    printf("%d\n", min_diff);
    return 0;
}


#if 0
void combination_head(int n, int r) {
    if (r > N/2) {
        for (int i = 1; i <= N/2; i++) {
            printf("%d ", team1[i]);
        }
        printf("\n");
    }
    else if (n > N) {
        //printf("n = %d > %d\n\n", n, N);
        return;
    }
    else {
        team1[r] = n;
        
        //printf("[1] n = %d, r = %d, team = %d %d %d\n", n, r, team1[1], team1[2], team1[3]);
        combination_head(n + 1, r + 1);
        
        //printf("[2] n = %d, r = %d, team = %d %d %d\n", n, r, team1[1], team1[2], team1[3]);
        combination_head(n + 1, r);
    }
}
#endif
