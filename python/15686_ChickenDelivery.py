# 15686. 치킨 배달 (Gold 5)
'''
* C언어 풀이와의 차이점 
  각각의 집과 치킨집 사이의 거리를 계산한 dist 룩업 테이블을 1차원 배열로 구성

* 시간 단축 연습
1. min() 함수보다 if문으로 직접 비교하는 게 빠르다. 508ms -> 344ms

2. 비교 연산은 정수보다 문자가 느리다. 344ms -> 372ms

3. 전부 입력받고 list comprehension으로 조건에 맞게 필터링 344ms
   C언어처럼 2중 for문으로 입력 받자마자 조건 확인 후 필터링  348ms
'''

from itertools import combinations

N, M = map(int, input().split())

map = [ list(map(int, input().split())) for _ in range(N) ]
map = [ input().split() for _ in range(N) ]

house = [(i, j) for i in range(N) for j in range(N) if map[i][j] == 1]
store = [(i, j) for i in range(N) for j in range(N) if map[i][j] == 2]
cnth, cnts = len(house), len(store)


# C언어처럼 2중 for문으로 입력받자마자 house, store를 구해보자
# house, store = [], []
# cnth, cnts = 0, 0
# for i in range(N):
#     input_ = list(map(int, input().split()))
#     for j, v in enumerate(input_):
#         if v == 1:
#             house.append((i, j))
#             cnth += 1
#         if v == 2:
#             store.append((i, j))
#             cnts += 1

dist = [ abs(h[0]-s[0]) + abs(h[1]-s[1]) for h in house for s in store ]


ans = 1000000
for opened in combinations(range(cnts), M):
    
    min_sum = 0
    for i in range(cnth):
        min_each = 1000
        
        for s in opened:
            tmp = dist[i * cnts + s]
            if tmp < min_each:
                min_each = tmp
            # min_each = min(min_each, dist[i * cnts + s])
        min_sum += min_each
    
    if (min_sum < ans):
        ans = min_sum
    # ans = min(ans, min_sum)
    
print(ans)
