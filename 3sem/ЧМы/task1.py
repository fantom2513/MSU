import numpy as np
from numpy import linalg


def gauss(matrix, f, n):
    step_view(matrix, f, n)
    x = np.zeros((n), dtype="float64")

    for i in range(n - 1, -1, -1):
        res = f[i]
        for j in range(n - 1, i, -1):
            res -= matrix[i, j] * x[j]
        x[i] = res / matrix[i, i]
    return x


def step_view(matrix, f, n):
    for k in range(n):
        for i in range(k, n):
            if matrix[i, k] != 0:
                matrix[k], matrix[i] = matrix[i], matrix[k]
                f[k], f[i] = f[i], f[k]
                break
        for i in range(k + 1, n):
            f[i] -= f[k] * matrix[i, k] / matrix[k, k]
            matrix[i] -= matrix[k] * matrix[i, k] / matrix[k, k]
    return


def main_gauss(matrix, f, n):
    swaps = main_step_view(matrix, f, n)
    x = np.zeros((n), dtype="float64")
    for i in range(n - 1, -1, -1):
        res = f[i]
        for j in range(n - 1, i, -1):
            res -= matrix[i, j] * x[j]
        x[i] = res / matrix[i, i]

    for i in range(n - 1, -1, -1):
        x[swaps[i][0]], x[swaps[i][1]] = x[swaps[i][1]], x[swaps[i][0]]
    return x


def main_step_view(matrix, f, n):
    swaps = []
    for k in range(n):
        idx = np.argmax(np.abs(matrix[k]))
        sup = matrix[k, idx]
        swaps.append((k, idx))
        matrix[:, [k, idx]] = matrix[:, [idx, k]]
        matrix[k] /= sup
        f[k] /= sup
        for i in range(k + 1, n):
            f[i] -= f[k] * matrix[i, k]
            matrix[i] -= matrix[k] * matrix[i, k]
    return swaps


def high_relax(matrix, f, eps, omega):
    n = matrix.shape[0]
    f = matrix.T @ f
    matrix = matrix.T @ matrix
    inv = linalg.inv(matrix)
    iters = 0
    x = np.zeros((n), dtype="float64")
    delta_f = matrix @ x - f
    norm = linalg.norm(inv) * linalg.norm(delta_f)
    denom = linalg.inv(np.diag(np.diag(matrix)) + omega * np.tril(matrix, k=-1))
    while norm >= eps:
        iters += 1
        x = omega * (f - matrix @ x) @ denom + x
        delta_f = matrix @ x - f
        norm = linalg.norm(inv) * linalg.norm(delta_f)
    return x, iters


matrix1 = np.array(
    [[2, 5, 4, 1], [1, 3, 2, 1], [2, 10, 9, 7], [3, 8, 9, 2]], dtype="float64"
)

f1 = np.array([20, 11, 40, 37], dtype="float64")
if linalg.det(matrix1)!=0:
    inv1 = linalg.inv(matrix1)


matrix2 = np.array(
    [[6, 4, 5, 2], [3, 2, 4, 1], [3, 2, -2, 1], [9, 6, 1, 3]], dtype="float64"
)

f2 = np.array([1, 3, -7, 2], dtype="float64")
if linalg.det(matrix2)!=0:
    inv2 = linalg.inv(matrix2)


matrix3 = np.array(
    [[2, 1, 1, 0], [1, 3, 1, 1], [1, 1, 5, 0], [2, 3, -3, -10]], dtype="float64"
)

f3 = np.array([2, 5, -7, 14], dtype="float64")
if linalg.det(matrix3)!=0:
    inv3 = linalg.inv(matrix3)

m = 20
n = 8
matrix = []
f = []
for i in range(1, n + 1):
    f.append(200 + 50 * i)
    for j in range(1, n + 1):
        if i != j:
            matrix.append((i + j) / (m + n))
        else:
            matrix.append(n + m * m + j / m + i / n)
matrix = np.reshape(np.array(matrix, dtype="float64"), (n, n))
f = np.array(f, dtype="float64")
inv = linalg.inv(matrix)


w = 0.4
count = w

print("СЛАУ 1")
print("Матрица")
print(matrix1)
print("\nf = ",f1)
print("\ndet(A) =", linalg.det(matrix1))
if linalg.det(matrix1)!=0:
    print("\nОбратная матрица:")
    print(inv1)
    print("\nЧисло обусловленности:", linalg.norm(matrix1, ord=1) * linalg.norm(inv1, ord=1))
    print("\nРешение методом Гаусса\n", gauss(matrix1.copy(), f1.copy(), 4))
    print("\nРешение модифицированным методом Гаусса\n",main_gauss(matrix1.copy(), f1.copy(), 4),)
    print("\nрешение методом верхней релаксации")
    count = w
    while count < 2:
        print("for w =", count)
        print(high_relax(matrix1.copy(), f1.copy(), 0.001, count))
        count = count + 0.4
print()

print("СЛАУ 2")
print("Матрица")
print(matrix2)
print("\nf = ",f2)
print("\ndet(A) =", linalg.det(matrix2))
if linalg.det(matrix2)!=0:
    print("\nОбратная матрица:")
    print(inv2)
    print("\nЧисло обусловленности:", linalg.norm(matrix2, ord=1) * linalg.norm(inv2, ord=1))
    print("\nРешение методом Гаусса\n", gauss(matrix2.copy(), f2.copy(), 4))
    print("\nРешение модифицированным методом Гаусса\n",main_gauss(matrix2.copy(), f2.copy(), 4),)
    print("\nрешение методом верхней релаксации")
    count = w
    while count < 2:
        print("for w =", count)
        print(high_relax(matrix1.copy(), f1.copy(), 0.001, count))
        count = count + 0.4
print()

print("СЛАУ 3")
print("Матрица")
print(matrix3)
print("\nf = ",f3)
print("\ndet(A) =", linalg.det(matrix3))
if linalg.det(matrix3)!=0:
    print("\nОбратная матрица:")
    print(inv3)
    print("\nЧисло обусловленности:", linalg.norm(matrix3, ord=1) * linalg.norm(inv3, ord=1))
    print("\nРешение методом Гаусса\n", gauss(matrix3.copy(), f3.copy(), 4))
    print("\nРешение модифицированным методом Гаусса\n",main_gauss(matrix3.copy(), f3.copy(), 4),)
    print("\nрешение методом верхней релаксации")
    count = w
    while count < 2:
        print("for w =", count)
        print(high_relax(matrix1.copy(), f1.copy(), 0.001, count))
        count = count + 0.4
print()

print("СЛАУ 4")
print("Матрица")
print(matrix)
print("\nf = ",f)
print("\ndet(A) =", linalg.det(matrix))
if linalg.det(matrix)!=0:
    print("\nОбратная матрица:")
    print(inv)
    print("\nЧисло обусловленности:", linalg.norm(matrix, ord=1) * linalg.norm(inv, ord=1))
    print("\nРешение методом Гаусса\n", gauss(matrix.copy(), f.copy(), n))
    print("\nРешение модифицированным методом Гаусса\n", main_gauss(matrix.copy(), f.copy(), n))
    print("\nрешение методом верхней релаксации")
    count = w
    while count < 2:
        print("for w =", count)
        print(high_relax(matrix1.copy(), f1.copy(), 0.001, count))
        count = count + 0.4
