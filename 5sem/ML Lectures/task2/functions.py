from typing import List


def sum_non_neg_diag(X: List[List[int]]) -> int:
    """
    Вернуть  сумму неотрицательных элементов на диагонали прямоугольной матрицы X. 
    Если неотрицательных элементов на диагонали нет, то вернуть -1
    """ 
    sum=0
    ind=0
    for i in range(min(len(X), len(X[0]))):
        if(X[i][i]>=0):
            sum=sum+X[i][i]
            ind=1
    if(ind == 0):
        return -1
    else:
        return sum


def are_multisets_equal(x: List[int], y: List[int]) -> bool:
    """
    Проверить, задают ли два вектора одно и то же мультимножество.
    """
    if len(x) != len(y):
        return False
    
    x.sort()
    y.sort()

    for i in range(len(x)):
        if x[i] != y[i]:
            return False

    return True


def max_prod_mod_3(x: List[int]) -> int:
    """
    Вернуть максимальное прозведение соседних элементов в массиве x, 
    таких что хотя бы один множитель в произведении делится на 3.
    Если таких произведений нет, то вернуть -1.
    """

    max=-1
    for i in range(len(x)-1):
        if(x[i]%3==0 or x[i+1]%3==0):
            if(x[i]*x[i+1]>max):
                max=x[i]*x[i+1]
    return max


def convert_image(image: List[List[List[float]]], weights: List[float]) -> List[List[float]]:
    """
    Сложить каналы изображения с указанными весами.
    """
    conv_image = [[0] * len(image[0]) for i in range(len(image))]

    for i in range(len(image)):
        for j in range(len(image[0])):
            for k in range (len(image[0][0])):
                conv_image[i][j] += image[i][j][k] * weights[k]
    
    return conv_image

def Len(x):
    length=0
    for i in range(len(x)):
        length=length + (x[i][1])
    return length
def unrle(x):
    res=[]
    for i in range(len(x)):
        for j in range(x[i][1]):
            res.append(x[i][0])
    return res


def rle_scalar(x: List[List[int]], y:  List[List[int]]) -> int:
    """
    Найти скалярное произведение между векторами x и y, заданными в формате RLE.
    В случае несовпадения длин векторов вернуть -1.
    """
    x1=unrle(x)
    y1=unrle(y)
    if(len(x1)!=len(y1)):
        return -1
    s=0
    for i in range(len(x1)):
        s=s+x1[i]*y1[i]
    return s


def cosine_distance(X: List[List[float]], Y: List[List[float]]) -> List[List[float]]:
    """
    Вычислить матрицу косинусных расстояний между объектами X и Y. 
    В случае равенства хотя бы одно из двух векторов 0, косинусное расстояние считать равным 1.
    """
    pass
