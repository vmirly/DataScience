# Pylibdb.py - a python library (module) for connecting to MySQL DB

import MySQLdb

host_name = "localhost"
db_name   = "cookbook"
user_name = "cbuser"
password    = "cbpass"

## establish a connection to DB

def connect(dbname = db_name, hostname=host_name, username=user_name, psswd=password):
    return MySQLdb.connect(db = dbname,
                           host = hostname,
                           user = username,
                           passwd = psswd)


def sendQuery(conn):
   try:
       cursor = conn.cursor()
       cursor.execute("SELECT id, name, cats FROM profile")
       allrows = cursor.fetchall()
       for row in allrows:
           print "id: %s, name: %s, cats: %s" % (row[0], row[1], row[2])
       print("Number of rows selected: %d" % cursor.rowcount)
       cursor.close()
   except MySQLdb.Error, e:
       print("Error occured: query failed!")
       print(e)

