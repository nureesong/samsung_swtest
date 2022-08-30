# 16236. 아기 상어 (Gold 3)
'''
문제를 제대로 읽자..ㅇㅅㅇ
- 크기 조건 만족하는 가까운 물고기부터 잡아먹기!! (크기 순으로 먹는 거 아님)
- 거리가 동률일 때는 더 위쪽, 더 왼쪽에 있는 물고기 먹기 (탐색 방향 순서: 상좌우하)
- DFS 재귀로 풀다가 떄려침..
- 거리 순으로 먹을 수 있는 물고기를 찾는 게 우선이므로 BFS 사용
- 무조건 상좌우하 순서로 큐에 넣어서 틀림.. -> 일단 4방향 큐에 넣고 거리,행,열 오름차순으로 정렬!!
- 시간초과....
'''

from collections import deque

N = int(input())
arr = [list(map(int, input().split())) for _ in range(N)]

shark = [(0, i, j) for i in range(N) for j in range(N) if arr[i][j] == 9][0]
arr[shark[1]][shark[2]] = 0


# 현재 상어 위치에서 거리순으로 먹을 수 있는 물고기들을 탐색
def BFS(shark):
    global N
    vis = [[0]*N for _ in range(N)]
    fish = []  # 먹을 수 있는 물고기 정보 저장
    
    q = deque([shark])
    
    while (q):
        d, r, c = q.popleft()
        vis[r][c] = 1
        
        for dr, dc in ((-1,0), (0,-1), (0,1), (1,0)):  # up, left, right, down
            nr = r + dr
            nc = c + dc
            
            if (0 <= nr < N and 0 <= nc < N) and vis[nr][nc] == 0 and arr[nr][nc] <= sz:
                q.append((d+1, nr, nc))
                vis[nr][nc] = 1
                
                if (0 < arr[nr][nc] < sz): # 먹을 수 있는지만 체크한다.
                    fish.append((d+1, nr, nc))
      
      
    if fish: # 먹을 수 있는 물고기 존재
        # (거리, 행, 열 오름차순)으로 물고기들을 정렬해서 타겟 물고기 리턴
        return sorted(fish, key = lambda x: (x[0], x[1], x[2]))[0]
    else:
        return 0
    

sz = 2
cnt = 0
total_dist = 0

while 1:
    fish = BFS(shark)
    if fish:  # 잡아먹을 수 있는 물고기가 있으면 (거리, 위치)를 리턴 받음
        # print(f"\n[Eat] shark = {shark[1:]}, fish = {fish}")
        
        d, r, c = fish
        
        cnt += 1
        if cnt == sz:
            sz += 1
            cnt = 0
        
        total_dist += d
        arr[r][c] = 0
        shark = (0, r, c)
        
        # print(f"cnt = {cnt}, sz = {sz}, total = {total_dist}")
    else:
        break

print(total_dist)
