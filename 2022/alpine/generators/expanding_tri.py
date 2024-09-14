from random import shuffle

N = 3333
print("1 1")
print("100000 100000")
print(N)

contours = []

for i in range(1, N):
    if i < N / 2:
        h = 5 * i
    else:
        h = 3 * i    
    contours.append((3, h, 0, i, i, -i, -i,  -i))

contours.append((4, 789, -1000000, -1000000, -1000000, 1000000, 1000000, 1000000, 1000000, -1000000))

shuffle(contours)
for contour in contours:
    print(*contour)

