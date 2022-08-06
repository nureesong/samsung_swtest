/***********************************************************/
// [13458] 시험 감독 (Bronze 2)
// 항상 결과값의 최대를 생각하자!!!
// N = 100만, 모든 Ai 100만, B = C = 1일 때 cnt = 10^12 이므로 42억 초과
/***********************************************************/

#if 0
#include <stdio.h>

int N, a[1000000+10], b, c;

void input(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d %d", &b, &c);
}

unsigned long long int solve(void) {
    unsigned long long int cnt = N; // 모든 시험장에 총감독 1명씩 필요
    
    for (int i = 0; i < N; i++) {
        if (a[i] <= b) continue; // 부감독 필요 없음
        
        cnt += ( (a[i] - b) / c );
        if ( (a[i] - b) % c ) cnt++;
    }
    
    return cnt;
}

int main(void) {
    input();
    printf("%llu\n", solve());
    return 0;
}
#endif


// ceil 함수는 double형으로 리턴!!
// 실수 나눗셈을 위해 double로 바꾸고 다시 int로 바꿨더니 느린듯..
#if 0
#include <stdio.h>
#include <math.h>

int N, a[1000000+10], b, c;

void input(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d %d", &b, &c);
}

unsigned long long int solve(void) {
    unsigned long long int cnt = N;
    
    for (int i = 0; i < N; i++) {
        if (a[i] <= b) continue;
        
        cnt += (int)ceil( (a[i]-b) / ((double)c) );
    }
    
    return cnt;
}

int main(void) {
    input();
    printf("%llu\n", solve());
    return 0;
}

#endif
