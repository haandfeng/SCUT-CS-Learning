a = []
n = 0
for i in range(50, 1000):
    for j in range(2, i + 1):
        if i == j:
            a.append(i)
            n += 1
        if i % j == 0:
            break
print(n)
print(a)