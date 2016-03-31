MySQL DataBase System
=============

1. [SQL: Structure Query Language](#SQL)
   * [Notes on MySQL](#mysql_notes)
   * [User Defined Variables](#udef_vars)
2. [Writing MySQL Python APIs](#mysql_python)
   * [Connect to DB in python](#connect_db)
   * [Writing Library Routines](#library)
3. [More Complex Queries to Select Data](#complex_queries)
   * [Order the output](#orderby)
   * [Views](#views)
   * [Multiple Tables](#multi-tables)

<a name="SQL"></a>
## SQL: Structure Query Language

MySQL database system uses a client-server architecture. MySQL is inherently a networked system.

For this turorial, we create a user called cbuser that can connect to server (on localhost). Only root user can do this, si first we need to connect as root. If you donot remember the root user, then:

   * To change the root password for MySQL: sudo dpkg-reconfigure mysql-server-5.5

After you have the root password:
```
sudo mysql -h localhost -p -u root

grant all on cookbook.* to 'cbuser'@'localhost' identified by 'cbpass';
```

Then verify that you can connect to mysql-server by 
```
mysql -h localhost -p -u cbuser
```

Then we create a database, and table, and insert new objects into the table as follows:

```
CREATE DATABASE cookbook;
USE cookbook;
CRATE TABLE limbs (thing VARCHAR(20), legs INT, arms INT);
INSERT INTO limbs (thing,legs,arms) VALUES ('human',2,2);
```

To generate a dumpfile that contains a backup of the database:
```
mysqldump -h localhost -p -u cbuser cookbook > cookbook.sql
```

<a name="mysql_notes"></a>
### Notes on MySQL

* to avoid entering command line options every time, put the options in my.cnf file
* To cancel a partially entered SQL command: use '\c'
```
SELECT *
FROM limbs
ORDER BY \c
```

* to read SQL commands from a file: redirect input (in batch mode) or use **source filename;** (in interactive mode)
```
mysql -h localhost -p -u cbuser cookbook < filename
```

* Use **-t** in batch mode for tabular (tab-delimited query output)
```
mysql -t -h localhost -p -u cbuser cookbook < mycommands.inp

+-------------------+------+------+------+------+------+-------+-------+------+------+------+------+
| name              | mpg  | cyl  | disp | hp   | drat | wt    | qsec  | vs   | am   | gear | carb |
+-------------------+------+------+------+------+------+-------+-------+------+------+------+------+
| Mazda RX4         |   21 |    6 |  160 |  110 |  3.9 |  2.62 | 16.46 |    0 |    1 |    4 |    4 |
| Mazda RX4 Wag     |   21 |    6 |  160 |  110 |  3.9 | 2.875 | 17.02 |    0 |    1 |    4 |    4 |
| Hornet 4 Drive    | 21.4 |    6 |  258 |  110 | 3.08 | 3.215 | 19.44 |    1 |    0 |    3 |    1 |
| Hornet Sportabout | 18.7 |    8 |  360 |  175 | 3.15 |  3.44 | 17.02 |    0 |    0 |    3 |    2 |
| Valiant           | 18.1 |    6 |  225 |  105 | 2.76 |  3.46 | 20.22 |    1 |    0 |    3 |    1 |
+-------------------+------+------+------+------+------+-------+-------+------+------+------+------+
```

* Use **-H** for HTML output:
```
mysql -H -h localhost -p -u cbuser cookbook < mycommands.inp
```

* Use **-e** for sending commands to mysql without any inputfile
* Use **-X** for XML output:
```
mysql -X -h localhost -p -u cbuser -e "SELECT * FROM mtcars" cookbook 
```

* To suppress column headings: use **-ss** or **--skip-column-names**

* Controlling verbosity: **-v** or **-vv**
* Commands used in an interactive session will be saved in ~/.mysql_history
* To log interactive sessions, use **--tee=filename.log** prior to starting mysql


<a name="udef_vars"></a>
### User defined variables

We can assign a value returned from SELECT statement to a variable, which can later be referred to.
* For assigning whitin SELECT statement: @myvar := value
```
SELECT @id:=userid FROM usertable WHERE userid='Matt';
```
This example, assign the highest mpg to variable maxmpg:
```
SELECT @maxmpg:=MAX(mpg) FROM mtcars WHERE cyl=6;
```
* To set a variable explicitly (not whitin SELECT): SET @var = value

<a name="mysql_python"></a>
## Writing MySQL Python APIs

Regardless of what programming language you use, all programs have to use an API that implements a communication protocol.

<a name="connect_db"></a>
## Connect to DB in python:

* import MySQLdb
* create a database connection object using **connect()** method
* close connection with object method **close()**

```
#!/usr/bin/python
 """
  To connect to a database
 """
import sys
import MySQLdb

try:
    conn = MySQLdb.connect(db="cookbook",
                           host="localhost",
                           user="cbuser",
                           passwd="cbpass")
    print ("DB connection established!")
except:
    print ("Cannot connect to server!")
    sys.exit(1)

conn.close()
print("DB connection closed!")

```

**NOTE:** On windows, you may have to use *127.0.0.1* instead of *localhost*

#### Additional connection parameters:
* For localhost connection, you can specify **unix_socket** which is a path to the UNIX domain socket file.
* For TCP/IP connections, you may provide a **port** number 

### Handling Exceptions
If an exception is raised, it can be handled as below:

```
try:
    conn = MySQLdb.connect(db="cookbook",
                           host="localhost",
                           user="cbuser",
                           passwd="cbpass")
    print ("DB connection established!")
except MySQLdb.Error, e:
    print ("Cannot connect to server!")
    print ("Error code: ", e.args[0])
    print ("Error message: ", e.args[1])
    sys.exit(1)
```

<a name="library"></a>
## Writing Library Routines

The tasks that are repeated in different programs, can be placed into a library, which can then be accessed multiple times.

We will install the library in */usr/local/lib/pydb/*. Therefore, *export PYTHONDB=/use/local/lib/pydb/*

Python libraries are in form of modules that can be imported to other python programs. The module name is the same as the script name.

The lib/ directory contains the library modules.

### Retrieving Results

We have a table created as follows:
```
CREATE TABLE profile
(
   id INT UNSIGNED NOT NULL AUTO_INCREMENT,
   name CHAR(20) NOT NULL,
   birth DATE,
   color ENUM('red', 'green', 'blue', 'brown', 'black', 'white'),
   foods SET('lutefisk', 'curry', 'burrito', 'eggroll', 'fadge', 'pizza'),
   cats INT,
   PRIMARY KEY (id)
);
```

SQL statements are divided into two categories:

* Those that do no return any result, rather result in changes to a table
  * UODATE, INSERT and DELETE
* Those that output some results
  * SELECT, SHOW, EXPLAIN, DESCRIBE

Pythin interface has a single method for both of these statements. To process a SQL statement, get a **cursor** object from the **connection** object, and then use the **execute()** method.

```
cursor = conn.cursor()
cursor.execute("UPDATE profile SET cats = cats - 1 WHERE cats >= 3")
print("Number of rows updated: %d" % cursor.rowcount)
```

To retrieve the results:
* **fetchone()** returns the next row 
* **fetchall()** returns the entire set

```
## Example fetch all rows
try:
    cursor = conn.cursor()
    cursor.execute("SELECT id, name, cats FROM profile")
    allrows = cursor.fetchall()
    for row in allrows:
        print "id: %s, name: %s, cats: %s" % (row[0], row[1], row[2])
    print("Number of rows updated: %d" % cursor.rowcount)
    cursor.close()
except MySQLdb.Error, e:
    print("Error occured: query failed!")
    print(e)
```

By putting the above example in a function *sendQuery()*, we can use our python module as below:
```
>>> import Pylibdb as db
>>> conn = db.connect()
>>> db.sendQuery(conn)
id: 1, name: Fred, cats: 0
id: 2, name: Mort, cats: 3
id: 3, name: Brit, cats: 1
id: 4, name: Carl, cats: 4
id: 5, name: Sean, cats: 5
id: 6, name: Alan, cats: 1
id: 7, name: Mara, cats: 1
id: 8, name: Shepard, cats: 2
id: 9, name: Dick, cats: 0
id: 10, name: Tony, cats: 0
Number of rows updated: 10
```

To retrieve the result as python dictionary, then we should construct the cursor object by specifying **DictCursor** type. This way, we can access results by their column names (keys).
```
## Example fetch all as dicttionary
try:
    cursor = conn.cursor(MySQLdb.cursors.DictCursor)
    cursor.execute("SELECT id, name, cats FROM profile")
    allrows = cursor.fetchall()
    for row in allrows:
        print "id: %s, name: %s, cats: %s" % (row["id"], row["name"], row["cats"])
    print("Number of rows updated: %d" % cursor.rowcount)
    cursor.close()
except MySQLdb.Error, e:
    print("Error occured: query failed!")
    print(e)
```

### Using Placeholders to Handle Special Characters & Security

If a name contains a special character such as single quote, or for HTML pages like < and >, then we can use placeholders:
```
INSERT INTO profile (name,birth,color,foods,cats)
VALUES (?,?,?,?,?)
```

Advantages of using placeholder:
* reuse statement strings over and over
* Handling NULL values
* Code is more readable

In Python, we use *format* specifier for placeholders in SQL statements:
```
cursor = conn.cursor()
cursor.execute("""
               INSERT INTO profile (name,birth,color,foods,cats)
               VALUES ({},{},{},{},{})
               """.format("De'mont", '1987-03-4', None, "pizza", 4) )

## or
s = "INSERT INTO profile (name,birth,color,foods,cats) VALUES ({},{},{},{},{})"
cursor.execute(s.format(c.literal('myname'),'1987-03-04',c.literal('blue'),c.literal('pizza'),0))
```

### Identifying *NULL* values

Python represents *NULL* values by *None*.
```
cursor = conn.cursor()
cursor.execute("SELECT name, birth, food FROM profile")
for row in cursor.fetchall():
    row = list(row) # convert mutable tuple to mutable list
    for i in range(0, len(row)):
        if (row[i] == None: 
           row[i] = "NULL"
    print ("name: %s, birth: %s, foods: %s".format(row[0], row[1], row[2]))
cursor.close()
```

### Getting command-line parameters

Command-line arguments are passed to Python scripts via *sys.argv* variable.
```
#!/usr/bin/python
# show command-line parsing

import sys
import getopt
import MySQLdb

try:
    opts, args = getopt.getopt( sys.argv[1:],
                                "h:p:u:",
                                ["host=", "password=", "user="])

except getopt.Error, e:
    print "%s: %s".format(sys.argv[0], e)
    sys.exit(1)

host_name = password = user_name = ""

for opt, arg in opts:
    if (opt in ("-h", "--host"):
        host_name = arg
    elif opt in ("-p", "--passord"):
        password = arg
    elif opt in ("-u", "--user"):
        user_name = arg

```

### Reading parameters from a file

Specify an option file os option group using *read_default_file* or *read_default_group* arguments to *connect()*.
```
conn = MySQLdb.connect(db="cookbook", read_default_group="cookbook")
```

To use *.my.cnf* file:
```
import os
option_file = os.environ("HOME") + "/" + ".my.cnf"
conn = MySQLdb.connect(db="cookbook", read_default_file=option_file)
```

<a name="complex_queries"></a>
# More Complex Queries to Select Data 

* Example 1:

```
## load the table
mysql -h localhost -p -u cbuser cookbook < mail.sql
mysql -h localhost -p -u cbuser -e "SELECT * FROM mail WHERE srcuser='barb' AND dstuser='tricia' " cookbook
```

* Example 2: change the column name in the output using *AS*
```
SELECT DATE_FORMAT(t, '%M %e, %Y') AS 'Date of message', srcuser AS 'Message Sender' FROM mail;
```

* Remove duplicate rows *DISTINCT*
```
SELECT DISTINCT srcuser FROM mail;
SELECT COUNT(DISTINCT srcuser) AS count FROM mail;
```

* To check whther a value is *NULL* or not: **IS NULL** or **IS NOT NULL**
```
SELECT * FROM taxpayer WHERE is IS NULL;

## map NULL values to another meaningful string in output:
SELECT name, IF (id IS NULL, 'Unknown', id) AS id FROM taxpayer;
+---------+---------+
| name    | id      |
+---------+---------+
| bernina | 198-48  |
| bertha  | Unknown |
| ben     | Unknown |
| bill    | 475-83  |
+---------+---------+
```

These two expressions are equivalent:

* IF (expr1 IS NOT NULL, expr1, expr2)
* IFNULL(expr1, expr2)

<a name="orderby"></a>
## Order the output:

* To order the output: **ORDER BY column_name**
* For descending order: **DESC**

### Subquery:

To find the maximum of a count:
```
SELECT a.state,a.cnt FROM (
   SELECT state,COUNT(id) AS cnt FROM twitter GROUP BY state) a 
ORDER BY a.cnt DESC LIMIT 10;

+-------+-----+
| state | cnt |
+-------+-----+
| CA    | 140 |
| TX    | 111 |
| NY    |  67 |
| FL    |  61 |
| NJ    |  48 |
| IL    |  48 |
| OH    |  46 |
| PA    |  44 |
| MI    |  32 |
| WA    |  29 |
+-------+-----+
10 rows in set (0.00 sec)

```

<a name="views"></a>
## Views:

Views are *virtual tables* created by a select command of a real table. Helps to make frequent queries

```
CREATE VIEW mail_view AS
SELECT 
DATE_FORMAT (t, '%M %e, %Y') AS date_sent,
CONCAT (srcuser,'@',srchost) AS sender,
CONCAT (dstuser,'@',dsthost) AS recipient,
size
FROM mail;
```
Then we can treat mail_view as a table:
```
SELECT * FROM mail_view WHERE size<1000;
+--------------+-------------+---------------+------+
| date_sent    | sender      | recipient     | size |
+--------------+-------------+---------------+------+
| May 13, 2006 | barb@saturn | tricia@venus  |  271 |
| May 15, 2006 | phil@venus  | phil@venus    |  978 |
| May 16, 2006 | gene@venus  | barb@mars     |  613 |
| May 17, 2006 | phil@mars   | tricia@saturn |  873 |
+--------------+-------------+---------------+------+

```

<a name="multi-tables"></a>
## Multiple Tables

Using join or subquery
* A *join* matches rows in one table with rows of another table
* A *subquery* is a query nested within another query

Example for join:
```
SELECT id,name,service FROM profile
INNER JOIN profile_contact ON id = profile_id;
```
Example for subquery:
```
SELECT * FROM profile_contact
WHERE profile_id = (SELECT id FROM profile WHERE name='Mort');
```
