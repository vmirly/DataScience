# after executing doweathclass to make data then:
#exec(open("./doweathclass.py").read())

#try dir() to see what objects
#datax_rdd is the rdd to use, datax_rdd.take(3) will show some points
# or .count()  etc...

#then run naivebays, then 


import numpy as np
from pyspark.mllib.linalg import Vectors
from pyspark.mllib.regression import LabeledPoint

#outlook,temperature,humidity,windy,play, copied from Weka's data example
rawdata=[
['sunny',85,85,'FALSE',0],
['sunny',80,90,'TRUE',0],
['overcast',83,86,'FALSE',1],
['rainy',70,96,'FALSE',1],
['rainy',68,80,'FALSE',1],
['rainy',65,70,'TRUE',0],
['overcast',64,65,'TRUE',1],
['sunny',72,95,'FALSE',0],
['sunny',69,70,'FALSE',1],
['rainy',75,80,'FALSE',1],
['sunny',75,70,'TRUE',1],
['overcast',72,90,'TRUE',1],
['overcast',81,75,'FALSE',1],
['rainy',71,91,'TRUE',0]
]

from pyspark.sql import SQLContext,Row
sqlContext = SQLContext(sc)

data_df=sqlContext.createDataFrame(rawdata,
   ['outlook','temp','humid','windy','play'])

#transform categoricals into indicator variables
out2index={'sunny':[1,0,0],'overcast':[0,1,0],'rainy':[0,0,1]}

#make RDD of labeled vectors
def newrow(dfrow):
    outrow = list(out2index.get((dfrow[0])))  #get dictionary entry for outlook
    outrow.append(dfrow[1])   #temp
    outrow.append(dfrow[2])   #humidity
    if dfrow[3]=='TRUE':      #windy
        outrow.append(1)
    else:
        outrow.append(0)
    return (LabeledPoint(dfrow[4],outrow))

datax_rdd=data_df.map(newrow)

#

