#s1a
import pandas as pd

training = pd.read_csv("titanic_train.csv")

# s1b
training.info()

# <class 'pandas.core.frame.DataFrame'>
# RangeIndex: 891 entries, 0 to 890
# Data columns (total 12 columns):
#  #   Column       Non-Null Count  Dtype
# ---  ------       --------------  -----
#  0   PassengerId  891 non-null    int64
#  1   Survived     891 non-null    int64
#  2   Pclass       891 non-null    int64
#  3   Name         891 non-null    object
#  4   Sex          891 non-null    object
#  5   Age          714 non-null    float64
#  6   SibSp        891 non-null    int64
#  7   Parch        891 non-null    int64
#  8   Ticket       891 non-null    object
#  9   Fare         891 non-null    float64
#  10  Cabin        204 non-null    object
#  11  Embarked     889 non-null    object
# dtypes: float64(2), int64(5), object(5)
# memory usage: 83.7+ KB

# s2a
training["Sex"] = training["Sex"].apply(lambda toLabel: 0 if toLabel == 'male' else 1)

# s2b
training.info()

# <class 'pandas.core.frame.DataFrame'>
# RangeIndex: 891 entries, 0 to 890
# Data columns (total 12 columns):
#  #   Column       Non-Null Count  Dtype
# ---  ------       --------------  -----
#  0   PassengerId  891 non-null    int64
#  1   Survived     891 non-null    int64
#  2   Pclass       891 non-null    int64
#  3   Name         891 non-null    object
#  4   Sex          891 non-null    int64
#  5   Age          714 non-null    float64
#  6   SibSp        891 non-null    int64
#  7   Parch        891 non-null    int64
#  8   Ticket       891 non-null    object
#  9   Fare         891 non-null    float64
#  10  Cabin        204 non-null    object
#  11  Embarked     889 non-null    object
# dtypes: float64(2), int64(6), object(4)
# memory usage: 83.7+ KB


# s2c
# print(training["Age"].mean())

training["Age"].fillna(training["Age"].mean(), inplace=True)
# s2d
training.info()

# <class 'pandas.core.frame.DataFrame'>
# RangeIndex: 891 entries, 0 to 890
# Data columns (total 12 columns):
#  #   Column       Non-Null Count  Dtype
# ---  ------       --------------  -----
#  0   PassengerId  891 non-null    int64
#  1   Survived     891 non-null    int64
#  2   Pclass       891 non-null    int64
#  3   Name         891 non-null    object
#  4   Sex          891 non-null    int64
#  5   Age          891 non-null    float64
#  6   SibSp        891 non-null    int64
#  7   Parch        891 non-null    int64
#  8   Ticket       891 non-null    object
#  9   Fare         891 non-null    float64
#  10  Cabin        204 non-null    object
#  11  Embarked     889 non-null    object
# dtypes: float64(2), int64(6), object(4)
# memory usage: 83.7+ KB

# s3a
Training_target = training["Survived"].values

# s3b
columns = ["Fare", "Pclass", "Sex", "Age", "SibSp"]
Training_input = training[list(columns)].values
#
# s3c
from sklearn import tree
import six
import sys
sys.modules['sklearn.externals.six'] = six

clf_train = tree.DecisionTreeClassifier(criterion="entropy", max_depth=3)
clf_train = clf_train.fit(Training_input, Training_target)

# # s3d
clf_train.score(Training_input, Training_target)

# s4a
from sklearn.externals.six import StringIO

with open("titanic.dot", 'w') as f:
    f = tree.export_graphviz(clf_train, out_file=f, feature_names=columns)

# s5a
testing = pd.read_csv("titanic_test.csv")
testing.info()

# <class 'pandas.core.frame.DataFrame'>
# RangeIndex: 418 entries, 0 to 417
# Data columns (total 11 columns):
#  #   Column       Non-Null Count  Dtype
# ---  ------       --------------  -----
#  0   PassengerId  418 non-null    int64
#  1   Pclass       418 non-null    int64
#  2   Name         418 non-null    object
#  3   Sex          418 non-null    object
#  4   Age          332 non-null    float64
#  5   SibSp        418 non-null    int64
#  6   Parch        418 non-null    int64
#  7   Ticket       418 non-null    object
#  8   Fare         417 non-null    float64
#  9   Cabin        91 non-null     object
#  10  Embarked     418 non-null    object
# dtypes: float64(2), int64(4), object(5)
# memory usage: 36.1+ KB

# s5b
testing["Sex"] = testing["Sex"].apply(lambda toLabel: 0 if toLabel == 'male' else 1)

# s5c
testing["Age"].fillna(testing["Age"].mean(), inplace=True)

# s5d
testing.info()

# <class 'pandas.core.frame.DataFrame'>
# RangeIndex: 418 entries, 0 to 417
# Data columns (total 11 columns):
#  #   Column       Non-Null Count  Dtype
# ---  ------       --------------  -----
#  0   PassengerId  418 non-null    int64
#  1   Pclass       418 non-null    int64
#  2   Name         418 non-null    object
#  3   Sex          418 non-null    int64
#  4   Age          418 non-null    float64
#  5   SibSp        418 non-null    int64
#  6   Parch        418 non-null    int64
#  7   Ticket       418 non-null    object
#  8   Fare         417 non-null    float64
#  9   Cabin        91 non-null     object
#  10  Embarked     418 non-null    object
# dtypes: float64(2), int64(5), object(4)
# memory usage: 36.1+ KB

# s6a
Testing_input = testing[list(columns)].values

# s6b
target_labels = clf_train.predict(Testing_input)
target_labels = pd.DataFrame({'Est_Survival':target_labels, 'Name':testing['Name']})

# s6c
import numpy as np

all_data = pd.read_csv("titanic_all.csv")

testing_results = pd.merge(target_labels, all_data[['Name','Survived']], on=['Name'])
acc = np.sum(testing_results['Est_Survival'] == testing_results['Survived']) / float(len(testing_results))

# s7a
all_data = pd.read_csv("titanic_all.csv", usecols=['Survived','Pclass','Sex','Age','SibSp','Fare'])
all_data.info()

# <class 'pandas.core.frame.DataFrame'>
# RangeIndex: 1309 entries, 0 to 1308
# Data columns (total 6 columns):
#  #   Column    Non-Null Count  Dtype
# ---  ------    --------------  -----
#  0   Survived  1309 non-null   int64
#  1   Pclass    1309 non-null   int64
#  2   Sex       1309 non-null   int64
#  3   Age       1046 non-null   float64
#  4   SibSp     1309 non-null   int64
#  5   Fare      1308 non-null   float64
# dtypes: float64(2), int64(4)
# memory usage: 61.5 KB

# s8a
all_data["Sex"] = all_data["Sex"].apply(lambda toLabel: 0 if toLabel == 'male' else 1)

# s8b
all_data["Age"].fillna(all_data["Age"].mean(), inplace=True)
all_data.info()

# <class 'pandas.core.frame.DataFrame'>
# RangeIndex: 1309 entries, 0 to 1308
# Data columns (total 6 columns):
#  #   Column    Non-Null Count  Dtype
# ---  ------    --------------  -----
#  0   Survived  1309 non-null   int64
#  1   Pclass    1309 non-null   int64
#  2   Sex       1309 non-null   int64
#  3   Age       1309 non-null   float64
#  4   SibSp     1309 non-null   int64
#  5   Fare      1308 non-null   float64
# dtypes: float64(2), int64(4)
# memory usage: 61.5 KB

# s9a
from sklearn.cross_validation import train_test_split

X = all_data[list(columns)].values
y = all_data["Survived"].values
X_train,X_test,y_train,y_test=train_test_split(X, y, test_size=0.40, random_state=0)

# s9b
clf_train = tree.DecisionTreeClassifier(criterion="entropy", max_depth=3)
clf_train = clf_train.fit(X_train, y_train)

# # s9c
train_score = str(clf_train.score(X_train,y_train))
test_score = str(clf_train.score(X_test,y_test))
print('Training score = '+ train_score+' Testing score = '+test_score)
