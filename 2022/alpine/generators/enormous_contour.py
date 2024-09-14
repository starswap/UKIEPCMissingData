import random
import matplotlib.pyplot as plt

MAX_POINTS = 200 # 20
ROUGH_MAX_DIM = 100

possibles = [*range(-ROUGH_MAX_DIM, ROUGH_MAX_DIM)]

random.shuffle(possibles)
bottomXs = sorted(possibles[:MAX_POINTS // 4])
bottom = [(x, random.randint(round(-1.2 * ROUGH_MAX_DIM), round(-1.1 * ROUGH_MAX_DIM))) for x in bottomXs] 

random.shuffle(possibles)
rightYs = sorted(possibles[:MAX_POINTS // 4])
right = [(random.randint(round(1.1 * ROUGH_MAX_DIM), round(1.2 * ROUGH_MAX_DIM)), y) for y in rightYs] 

random.shuffle(possibles)
topXs = sorted(possibles[:MAX_POINTS // 4], reverse=True)
top = [(x, random.randint(round(1.1 * ROUGH_MAX_DIM), round(1.2 * ROUGH_MAX_DIM))) for x in topXs] 

random.shuffle(possibles)
leftYs = sorted(possibles[:MAX_POINTS // 4], reverse=True)
left = [(random.randint(round(-1.2 * ROUGH_MAX_DIM), round(-1.1 * ROUGH_MAX_DIM)), y) for y in leftYs] 

points = bottom + right + top + left

xs, ys = zip(*(points + [points[0]]))
plt.figure()
plt.plot(xs, ys)
plt.show()

print("0 0")
print("1 1")
print(1)
print(f"{len(points)} {random.randint(0,  1000000)} {' '.join(map(lambda pt: str(pt[0]) + ' '  + str(pt[1]), points))}")
