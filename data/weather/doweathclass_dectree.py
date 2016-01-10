#exec(open("./doweathclass_dectree.py").read())

# ---------------- now try decision tree ------------
from pyspark.mllib.tree import DecisionTree
dt_model = DecisionTree.trainClassifier(datax_rdd,2,{},impurity='entropy',
          maxDepth=3,maxBins=32, minInstancesPerNode=2)  

#maxDepth and maxBins
#{} could be categorical feature list,
# To do regression, have no numclasses,and use trainRegression function
print (dt_model.toDebugString())

#results in this:
#DecisionTreeModel classifier of depth 3 with 9 nodes
#  If (feature 1 <= 0.0)
#   If (feature 4 <= 80.0)
#    If (feature 3 <= 68.0)
#     Predict: 0.0
#    Else (feature 3 > 68.0)
#     Predict: 1.0
#   Else (feature 4 > 80.0)
#    If (feature 0 <= 0.0)
#     Predict: 0.0
#    Else (feature 0 > 0.0)
#     Predict: 0.0
#  Else (feature 1 > 0.0)
#   Predict: 1.0

#notice number of nodes are the predict (leaf nodes) and the ifs
           
#some checks,get some of training data and test it:
datax_col=datax_rdd.collect()   #if datax_rdd was big, use sample or take

#redo the conf. matrix code (it would be more efficient to pass a model)
dt_cf_mat=np.zeros([2,2])  #num of classes
for pnt in datax_col:
    predctn = dt_model.predict(np.array(pnt.features))
    dt_cf_mat[pnt.label][predctn]+=1
corrcnt=0
for i in range(2): 
    corrcnt+=dt_cf_mat[i][i]
dt_per_corr=corrcnt/dt_cf_mat.sum()
print ('Decision Tree: Conf.Mat. and Per Corr')
print (dt_cf_mat)
print (dt_per_corr)

#maxdepth 5
# print cf_mat
#[[ 5.  0.]
# [ 2.  7.]]
#>>> print per_corr
#0.857142857143


#maxdepty 3 sis same ass 5
#maxdepth 2 gives me a core dump!

