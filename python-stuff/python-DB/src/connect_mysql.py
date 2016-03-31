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
    print ("Error code: ", e.args[0])
    print ("Error message: ", e.args[1])
    sys.exit(1)

conn.close()
print("DB connection closed!")

