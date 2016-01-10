# after executing doweathclass to make data then:
#exec(open("./doweathclass_naivebayes.py").read())
#
#
from pyspark.mllib.classification import NaiveBayes

#execute model, it can go in a single pass
my_nbmodel = NaiveBayes.train(datax_rdd)

#Some info on model 
print (my_nbmodel)
#some checks,get some of training data and test it:
datax_col=datax_rdd.collect()   #if datax_rdd was big, use sample or take

trainset_pred =[]
for x in datax_col:
    trainset_pred.append(my_nbmodel.predict(x.features))

print (trainset_pred)

#to see class conditionals
#you might have to install scipy
#import scipy
#print 'Class Cond Probabilities, ie p(attr|class= 0 or 1) '
#print scipy.exp(my_nbmodel.theta)
#print scipy.exp(my_nbmodel.pi)

#get a confusion matrix
#the row is the true class label 0 or 1, columns are predicted label
#
nb_cf_mat=np.zeros([2,2])  #num of classes
for pnt in datax_col:
    predctn = my_nbmodel.predict(np.array(pnt.features))
    nb_cf_mat[pnt.label][predctn]+=1

corrcnt=0
for i in range(2):
    corrcnt+=nb_cf_mat[i][i]
nb_per_corr=corrcnt/nb_cf_mat.sum()
print ('Naive Bayes: Conf.Mat. and Per Corr')
print (nb_cf_mat)
print (nb_per_corr)

#nb_cf_mat
#array([[ 3.,  2.],
#       [ 0.,  9.]])

#0.857142857143

# for 1st train class=1 0.785714285714
