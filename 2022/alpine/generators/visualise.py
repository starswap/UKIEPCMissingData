import matplotlib.pyplot as plt

ax, ay = map(int, input().split())
bx, by = map(int, input().split())
N = int(input())
plt.figure()

for n in range(N):
    v, h, *pts = map(int, input().split())
    xs = [pts[i] for i in range(0, 2 * v, 2)]
    ys = [pts[i] for i in range(1, 2 * v, 2)]

    plt.plot(xs + [xs[0]], ys + [ys[0]])

plt.show()
