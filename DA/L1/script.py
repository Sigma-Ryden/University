import pandas as pd
pd.set_option('display.max_rows', None)
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sns
sns.set()
from sklearn.datasets import make_blobs
from sklearn.cluster import Birch

wine_data = pd.read_csv("wine_data.csv")
wine_data.head()
print(wine_data.shape)
wine_data.describe()
X = wine_data.iloc[:,[1,2]].values
print(X.shape)
wine_data.info()

# (63, 3)
# (63, 2)
# <class 'pandas.core.frame.DataFrame'>
# RangeIndex: 63 entries, 0 to 62
# Data columns (total 3 columns):
#  #   Column      Non-Null Count  Dtype
# ---  ------      --------------  -----
#  0   name        63 non-null     object
#  1   Pinot Noir  63 non-null     int64
#  2   Champagne   63 non-null     int64
# dtypes: int64(2), object(1)
# memory usage: 1.6+ KB

plt.figure(figsize=(10,6))
plt.scatter(wine_data['Pinot Noir'], wine_data['Champagne'])
plt.title("Exhibit 2A: The Data")
plt.xlabel("Pinot Noir")
plt.ylabel("Champagne")
# plt.show()

import scipy.cluster.hierarchy as sch
dendrogram = sch.dendrogram(sch.linkage(X,method='ward'))
plt.title("Dendrogram")
plt.xlabel("Wine")
plt.ylabel("Euclidian Distance")
# plt.show()

X, clusters = make_blobs(n_samples=63, centers=3, cluster_std=0.50, random_state=0)
plt.scatter(X[:,0], X[:,1], alpha=0.7, edgecolor='b')
# plt.show()

brc = Birch(branching_factor=50, n_clusters=3, threshold=1.5)
brc.fit(X)
Birch(threshold=1.5)

labels = brc.predict(X)
plt.scatter(X[:,0], X[:,1], c=labels, cmap='rainbow', alpha=0.7, edgecolors='b')
# plt.show()

model = Birch(branching_factor=50, n_clusters=None, threshold=1.5)
model.fit(X)
Birch(n_clusters=None, threshold=1.5)

pred = model.predict(X)
plt.scatter(X[:,0], X[:,1], c=pred)
# plt.show()

from sklearn.preprocessing import StandardScaler
import pandas as pd
data = pd.read_csv('dataset.csv')

num_features = ['InstallmentCredit', 'Yearly Period', 'Class']
for feature in num_features:
    data[feature] = data[feature].apply(lambda label: 0 if label=='?' else label)
X = data[num_features]
scaler = StandardScaler()
X_normalized = scaler.fit_transform(X)
print(X_normalized)

# [[-0.33623128 -1.11677851  1.31508711]
#  [-0.88904815 -0.97504435 -1.15953917]
#  [ 0.00549133 -0.15119038 -1.15953917]
#  ...
#  [-0.89200006 -1.68157698         nan]
#  [-0.75124352 -0.80235046         nan]
#  [-0.1505662  -0.26312192         nan]]
