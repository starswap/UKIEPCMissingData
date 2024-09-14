import random
import matplotlib.pyplot as plt

MAX_POINTS = 100 # 20


print("0 0")
print("100000 76543")

polygons = []
plt.figure()

DELTA = 100

# doesn't really zig zag and also crosses over
# consider using matplotlib on all the cases

for ROUGH_MAX_DIM in range(DELTA, 10000, DELTA):

    possibles = [*range(-ROUGH_MAX_DIM, ROUGH_MAX_DIM)]

    random.shuffle(possibles)
    bottomXs = sorted(possibles[:MAX_POINTS // 4])
    bottom = [(x, random.randint(round(-1.2 * DELTA - 100 * ROUGH_MAX_DIM), round(-1.1 * DELTA - 100 * ROUGH_MAX_DIM))) for x in bottomXs] 

    random.shuffle(possibles)
    rightYs = sorted(possibles[:MAX_POINTS // 4])
    right = [(random.randint(round(1.1 * DELTA +  100 * ROUGH_MAX_DIM), round(1.2 * DELTA +  100 * ROUGH_MAX_DIM)), y) for y in rightYs] 

    random.shuffle(possibles)
    topXs = sorted(possibles[:MAX_POINTS // 4], reverse=True)
    top = [(x, random.randint(round(1.1 * DELTA +  100 * ROUGH_MAX_DIM), round(1.2 * DELTA + 100 * ROUGH_MAX_DIM))) for x in topXs] 

    random.shuffle(possibles)
    leftYs = sorted(possibles[:MAX_POINTS // 4], reverse=True)
    left = [(random.randint(round(-1.2 * DELTA - 100 * ROUGH_MAX_DIM), round(-1.1 * DELTA - 100 * ROUGH_MAX_DIM)), y) for y in leftYs] 

    points = bottom + right + top + left
    polygons.append(points)
    
    xs, ys = zip(*(points + [points[0]]))
    plt.plot(xs, ys)
    plt.plot(4567, 768)

print(len(polygons))
for points in polygons:
    print(f"{len(points)} {random.randint(0,  1000000)} {' '.join(map(lambda pt: str(pt[0]) + ' '  + str(pt[1]), points))}")


plt.show()
