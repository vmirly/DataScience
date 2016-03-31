Python-DB
Python-DataBase Management
=========


<h1> SQLite:</h1>

<p> <b> to create a new table: </b> </p>
```
CREATE TABLE database_name.table_name(
   column1 datatype  PRIMARY KEY(one or more columns),
   column2 datatype,
   column3 datatype,
   .....
   columnN datatype,
);
```

<p> <b> To insert a new query into a table: </b> </p>
```
INSERT INTO TABLE_NAME (column1, column2, column3,...columnN)]  
VALUES (value1, value2, value3,...valueN);
```
or
```
INSERT INTO TABLE_NAME VALUES (value1,value2,value3,...valueN);

```

<p> <b> Select query: </b> </p>
```
SELECT column1, column2, columnN FROM table_name;
```

```
SELECT * FROM table_name;
```
