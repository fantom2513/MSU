import numpy as np
from collections import defaultdict


def kfold_split(num_objects, num_folds):
    m = []
    group_size = num_objects // num_folds
    pos = [i for i in range(num_objects)]
    for i in range(num_folds):
        first = pos[:(i * group_size)]
        if i == (num_folds - 1):
            second = pos[i * group_size:]
        else:
            first += (pos[(i + 1) * group_size:])
            second = pos[i * group_size:(i + 1) * group_size]
        m.append((np.array(first), np.array(second)))
    return m


def knn_cv_score(X, y, parameters, score_function, folds, knn_class):
    dict = {}
    total_size = len(folds)
    for neighbour in parameters['n_neighbors']:
        for weight in parameters['weights']:
            for metric in parameters['metrics']:
                for normalizer in parameters['normalizers']:
                    summ = 0
                    for fold in folds:
                        x_train = X[fold[0]]
                        y_train = y[fold[0]]
                        x_test = X[fold[1]]
                        y_test = y[fold[1]]
                        if normalizer[0] is not None:
                            normalizer[0].fit(x_train)
                            x_train = normalizer[0].transform(x_train)
                            x_test = normalizer[0].transform(x_test)
                        model = knn_class(n_neighbors=neighbour, metric=metric, weights=weight)
                        model.fit(x_train, y_train)
                        y_predict = model.predict(x_test)
                        summ += score_function(y_test, y_predict)
                    dict[(normalizer[1], neighbour, metric, weight)] = summ / total_size
    return dict
