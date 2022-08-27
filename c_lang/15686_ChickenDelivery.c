/***********************************************************/
// [15686] 치킨 배달 (Gold 5)
// 런타임 에러(OutOfBounds)
// 문제에서 집은 최대 100개 치킨집은 최대 13개라 해서
// house, store 배열을 100, 13 + 5 로 줬는데
// 왜 컨테이너 또는 배열에서 할당된 경계를 넘어가는 접근이 발생하지??
// 여유 버퍼 100으로 바꾸면 통과하기는 함...
/***********************************************************/

#include <stdio.h>
#include <stdlib.h>

int N, M;

struct _st {
    int r, c;
};

struct _st house[100 + 100];
struct _st store[13 + 100];
int cnth = 0, cnts = 0;

int dist[13 + 100][100 + 100];
int opened[13 + 100];
int min_dist = 1000000;


void input(void) {
    int tmp;
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &tmp);
            if (tmp == 1) {
                house[cnth].r = i;
                house[cnth].c = j;
                cnth++;
            }
            else if (tmp == 2) {
                store[cnts].r = i;
                store[cnts].c = j;
                cnts++;
            }
        }
    }
}


void dist_table(void) {
    for (int i = 0; i < cnth; i++) {
        for (int j = 0; j < cnts; j++) {
            dist[i][j] = abs(house[i].r - store[j].r) + abs(house[i].c - store[j].c);
        }
    }
}


void combination(int n, int r) {
    int min, sum = 0, tmp;

    if (r == 0) {
        // 선택된 치킨집으로 각 집과의 치킨 거리 게산
        for (int h = 0; h < cnth; h++) {
            min = 1000;
            for (int m = 0; m < M; m++) {
                tmp = dist[h][opened[m]];
                if (tmp < min) min = tmp;
            }
            sum += min;
        }
        
        // 도시의 치킨 거리 최솟값 갱신
        if (sum < min_dist) min_dist = sum;
    }
    else if (n < r) {
        return;
    }
    else {
        opened[r - 1] = n - 1;
        combination(n - 1, r - 1);
        combination(n - 1, r);
    }
}


int main(void) {
    //freopen("in.txt", "r", stdin);
    
    input();
    dist_table();
    combination(cnts, M);
    printf("%d\n", min_dist);

    return 0;
}
