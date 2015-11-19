

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

Cloudera's Distribution for Hadoop:
   * Hue: for user interface
   * Oozie: for scheduling and workflow
   * Pig and Hive: for high level languages 

   * SQOOP: (SQL to Hadoop) a command-line tool for database capability, import data from SQL databases

   * HBASE: fast random access to HDFS data

   * PIG: a high level programming language for data analysis and manipulation

   * Hive: querying and managing large datasets, allowing SQL-like queries (HiveQL)

   * Oozie: scheduling Hadoop jobs, very scalable

   * Flume: for collecting, aggregating and moving large LOG data

   * Impala: query engine for Hadoop

   * Spark: Stream processing, in memory computing, providing advantages over the traditional Hadoop framework. Well suited for Machine Learning
     Multi-stage in memory primities, up tp 100 times speedup in certain applications.
