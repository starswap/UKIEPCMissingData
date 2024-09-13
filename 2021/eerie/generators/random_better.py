from random import randint, shuffle
W = randint(1, 500)
L = randint(1, 10000)
N = randint(1, 1000)
H_MAX = 10000

print(f"{W} {L}")
print(N)

s = -1
e = -1

points = [*range(0, H_MAX)]
shuffle(points)
points = sorted(points[:N + 1])

for i in range(N):
    print(f"{points[i]} {points[i + 1] - 1}")