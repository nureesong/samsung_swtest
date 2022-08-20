# 14889. 스타트와 링크 (Silver 2)
'''
team1에 항상 1을 포함시키고, 나머지 2 ~ N-1 중에 (N/2 - 1)명만 선택한다.
team1 구성이 끝나면 선택받지 않은 나머지 N/2명이 자동으로 team2가 된다.
(예전에 풀었을 때, 1 ~ N 중에 N/2명 선택했는데 제출 시 4876ms 걸림 -> 거의 두 배)
'''

from itertools import combinations

N = int(input())
S = [list(map(int, input().split())) for _ in range(N)]
min_diff = 200000


def team_score(team):
    sum = 0
    for i in range(N//2):
        for j in range(i + 1, N//2):
            sum += S[team[i]-1][team[j]-1] + S[team[j]-1][team[i]-1]
    return sum


for team1 in combinations(range(2, N + 1), N//2 - 1):
    team1 = (1,) + team1
    team2 = [i for i in range(2, N + 1) if i not in team1]  # 2860ms
#     team2 = list(set(range(1,N+1)) - set(team1))            # 2904ms (차집합 연산 느림)
    
    s1 = team_score(team1)
    s2 = team_score(team2)
    min_diff = min(abs(s1 - s2), min_diff)

print(min_diff)
