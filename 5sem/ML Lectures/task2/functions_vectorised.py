import numpy as np


def sum_non_neg_diag(X: np.ndarray) -> int:
    """
    Вернуть  сумму неотрицательных элементов на диагонали прямоугольной матрицы X. 
    Если неотрицательных элементов на диагонали нет, то вернуть -1
    """
    #sum=(np.trace(X)+np.trace(abs(X)))/2
    tmp=np.diag(X)
    s = sum(tmp[(tmp>=0)[:]])
    z = tmp[(tmp<0)[:]]
    if len(z)>0:
        return -1
    return s

def are_multisets_equal(x: np.ndarray, y: np.ndarray) -> bool:
    """
    Проверить, задают ли два вектора одно и то же мультимножество.
    """
    return np.array_equiv(np.sort(x), np.sort(y))


def max_prod_mod_3(x: np.ndarray) -> int:
    """
    Вернуть максимальное прозведение соседних элементов в массиве x, 
    таких что хотя бы один множитель в произведении делится на 3.
    Если таких произведений нет, то вернуть -1.
    """


def convert_image(image: np.ndarray, weights: np.ndarray) -> np.ndarray:
    """
    Сложить каналы изображения с указанными весами.
    """
    return np.sum(image * weights[None, None, :], axis = -1)


def rle_scalar(x: np.ndarray, y: np.ndarray) -> int:
    """
    Найти скалярное произведение между векторами x и y, заданными в формате RLE.
    В случае несовпадения длин векторов вернуть -1.
    """
    x=np.repeat(x[:,0], x[:,1])
    y=np.repeat(y[:,0], y[:,1])
    if len(x)==len(y):
        return x.dot(y)
    return -1
    


def cosine_distance(X: np.ndarray, Y: np.ndarray) -> np.ndarray:
    """
    Вычислить матрицу косинусных расстояний между объектами X и Y.
    В случае равенства хотя бы одно из двух векторов 0, косинусное расстояние считать равным 1.
    """
    x_ind = np.any(np.linalg.norm(X, axis=1, keepdims=True) ==0, axis=1)
    y_ind = np.any(np.linalg.norm(Y, axis=1, keepdims=True) ==0, axis=1)
    X[x_ind] = np.ones(X.shape[1])
    Y[y_ind] = np.ones(Y.shape[1])
    res = np.matmul(X/np.linalg.norm(X, axis=1, keepdims=True), (Y/np.linalg.norm(Y, axis=1, keepdims=True)).T)
    res[x_ind,:] = 1
    res[:, y_ind] = 1

    return res