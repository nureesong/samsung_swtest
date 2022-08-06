# 13458. 시험 감독 (Bronze 2)

N = int(input())
a = list(map(int, input().split()))
b, c = map(int, input().split())

cnt = N

for i in range(N):
    if a[i] <= b: continue
    cnt += (a[i] - b) // c
    if ((a[i] - b) % c):
        cnt += 1;
        
print(cnt)
