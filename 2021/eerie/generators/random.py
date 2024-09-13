from random import randint
W = randint(1, 10)
L = randint(1, 10)
N = randint(1, 10)
H_MAX = 200

print(f"{W} {L}")
print(N)

s = -1
e = -1
for i in range(N):
    s = randint(e + 1, H_MAX - 2*(N - i))
    e = randint(s, H_MAX - 2*(N - i) + 1)
    print(s, e)