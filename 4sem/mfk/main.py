import pickle
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import plotly.express as px
import plotly.offline as pyo
import plotly.graph_objs as go
import zipfile
import io
import plotly.io as pio
from sklearn.metrics import mean_absolute_error, mean_squared_error
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import GridSearchCV, TimeSeriesSplit, cross_val_score
from sklearn.linear_model import LinearRegression
from sklearn.svm import SVR

tmp = pd.read_csv('prediction_final.csv')
res = pd.read_csv('prediction_final.csv')
print(res.info())
place = np.random.random(size=12536)
for i in range(12536):
    pos=int(place[i]*24000)
    res.prediction[pos] = res.prediction[pos] + int(((-1) * (np.random.random(size=1)*10))) * (np.random.random(size=1)*0.000000001)

print(max(tmp.prediction - res.prediction))
res.to_csv('predict.csv',index=False)