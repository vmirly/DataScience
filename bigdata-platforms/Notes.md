

## Hadoop Basic Components

    * Hadoop common
    * Hadoop Distributed File System (HDFS)
    * Hadoop YARN (introduced in Hadoop 2.0)
    * Hadoop Map/Reduce

Hadoop common: contains libraries and modules

HDFS: for storing data

Hadoop YARN: a resource management platform

Hadoop Map/Reduce: a programming model to scale computations across different machines.

Other Apache applications such as Apache PIG, and Apache Hive sit on these components.

HDFS stores large files, (a few Gigabytes), and it provide reliability by repplicating files across multiple hosts (no REID storage on hosts).
Each node is name node, cluster of data nodes. 
A namenode contains directory information, and which system contains which part of data.

Job submission framework: 
  * jobtracker
  * tasktracker

YARN focuses strictly on scheduling --> achieved great scalibility.
With YARN, other complex analyses such as graph processing, Iterative models, and machine learning has been enabled.


## Hadoop Applications
