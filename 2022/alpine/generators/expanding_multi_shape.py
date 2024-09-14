from random import shuffle, randint
from math import pi, cos, sin

print("0 0")
print("0 300")

contours = []

for i in range(99):
    sides = i + 3

    points = []
    for j in range(sides):
        angle = (2 * pi) / sides * j
        points.append(round(cos(angle) * (5 * i + 5)))
        points.append(round(sin(angle) * (5 * i + 5)))
     
    h = randint(1, 10000)
    contours.append((sides, h, *points))

print(len(contours))
shuffle(contours)
for contour in contours:
    print(*contour)

