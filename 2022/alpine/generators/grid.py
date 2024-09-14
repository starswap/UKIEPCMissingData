import random
import matplotlib.pyplot as plt

print("0 0")
print("500000 100000")

contours = [(4, 789, (-989898, -989898), (-989898, 989898), (989898, 989898), (989898, -989898))]

for r in range(1, 148, 3):
    for c in range(1, 148, 3):
        contours.append((4, random.randint(0, 1000), (r * 5000, c * 5000), ((r + 1) * 5000, c * 5000), ((r + 1) * 5000, (c + 1) * 5000), (r * 5000, (c + 1) * 5000)))

print(len(contours))

for c in contours:
    n, h, *pts = c
    print(n, h, *map(lambda p: f"{p[0]} {p[1]}", pts))
    xs, ys = zip(*(pts + [pts[0]]))
