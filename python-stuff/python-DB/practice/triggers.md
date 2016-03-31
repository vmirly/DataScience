```
    mysql> CREATE TABLE student (
           sid INT NOT NULL,
           sname CHAR(20),
           avg_score REAL,
           PRIMARY KEY (sid));
    Query OK, 0 rows affected (0.24 sec)
    
    mysql> CREATE TABLE course (
           cid INT NOT NULL,
           cname CHAR(20),
           PRIMARY KEY (cid));
    Query OK, 0 rows affected (0.12 sec)

    mysql> CREATE TABLE stucourse ( 
           sid INT NOT NULL, 
           cid INT NOT NULL, 
           grade REAL, 
           PRIMARY KEY (sid,cid), 
           FOREIGN KEY (sid) REFERENCES student(sid), 
           FOREIGN KEY (cid) REFERENCES course(cid));
    Query OK, 0 rows affected (0.18 sec)
```

The avg_score is a derived attribute for each student. Every time an entry is inserted or update in stucourse table, the avg_score of the student corresponding to that entry should be set appropriately.

So, I created this trigger for this purpose:

```
     mysql> delimiter //
     mysql> CREATE TRIGGER calavgscore 
            AFTER INSERT ON stucourse 
            FOR EACH ROW 
            BEGIN
               UPDATE student SET avg_score=(SELECT AVG(grade) FROM stucourse WHERE NEW.sid=stucourse.sid GROUP BY sid); 
            END;//
     mysql> delimiter
```
