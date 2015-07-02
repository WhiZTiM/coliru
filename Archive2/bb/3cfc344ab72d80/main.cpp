
a = [10, 20, 30, 40]
b = [1, 2, 3, 4, 5]

print sum(map(lambda i: a[i] * 2 - b[i + 1], range(len(a))))
