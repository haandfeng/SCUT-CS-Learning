import numpy as np

np.random.seed(100456)
a = np.random.uniform(2, 10, (5, 5))
print("Seed: 100456")
print("变化前")
print(a)
print("均值", a.mean())
print("方差", a.var())
a[[1, 2], :] = a[[2, 1], :]
a[:, [0, 4]] = a[:, [4, 0]]
print("变化后")
print(a)
print("均值", a.mean())
print("方差", a.var())
