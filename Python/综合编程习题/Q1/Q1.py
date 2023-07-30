sum = 0
for i in range(10,20):
    print(i)
for i in range(10, 100001):
    if i % 5 == 0 or i % 7 == 0:
        sum += i
print(sum)
