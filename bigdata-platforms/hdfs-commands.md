HDFS Commands
============

```
hdfs dfs -mkdir /test-hdfs

hdfs dfs -ls /
```


Create a random text file on host:

```
dd if=/dev/urandom of=sample.txt bs=64M count=16

du -h sample.txt
```

Copy this file to HDFS:
```
hdfs dfs -put sample.txt /test-hdfs/sample.txt
```

Run a file-system check on this file on HDFS:
```
hdfs fsck /test-hdfs/sample.txt
```

This will give output as follows
```
Connecting to namenode via http://localhost:50070/fsck?ugi=hadoop&path=%2Ftest-hdfs%2Fsample.txt
FSCK started by hadoop (auth:SIMPLE) from /127.0.0.1 for path /test-hdfs/sample.txt at Sun Dec 06 20:51:43 EST 2015
.Status: HEALTHY
 Total size:	536870896 B
 Total dirs:	0
 Total files:	1
 Total symlinks:		0
 Total blocks (validated):	4 (avg. block size 134217724 B)
 Minimally replicated blocks:	4 (100.0 %)
 Over-replicated blocks:	0 (0.0 %)
 Under-replicated blocks:	0 (0.0 %)
 Mis-replicated blocks:		0 (0.0 %)
 Default replication factor:	1
 Average block replication:	1.0
 Corrupt blocks:		0
 Missing replicas:		0 (0.0 %)
 Number of data-nodes:		1
 Number of racks:		1
FSCK ended at Sun Dec 06 20:51:43 EST 2015 in 10 milliseconds


The filesystem under path '/test-hdfs/sample.txt' is HEALTHY
```


Available HDFS commands:

| Command |                      Usage                      |
|:-------:|:-----------------------------------------------:|
|   -ls   |    List files and directories  the given path   |
|   -cp   |              Copy files within HDFS             |
|   -mv   |              Move files within HDFS             |
|   -rm   |                   Remove file                   |
|   -lsr  |             Recursive version of -ls            |
|   -rmr  |             Recursive version of -rm            |
|   -cat  |         Display content of file on HDFS         |
|  -tail  |         Show the last 1KB of a HDFS file        |
|   -get  | Transfer a file from HDFS to  local file system |
|   -put  |      Transfer a file from local FS to HDFS      |
