import sqlite3

def select_db(dbname, tablename, cond):
    """ To retrieve data from a database 
        database name, column name, value
    """
    conn = sqlite3.connect(dbname)
    c = conn.cursor()
    
    for row in c.execute('SELECT * FROM {tn} WHERE {cn}'.format(tn=tablename, cn=cond)):
       print(row)


def dbinfo(dbname, tabname):
   """To print number of rows and columns in a database, and 
      all its column names 
   """
   
   conn = sqlite3.connect(dbname)
   c = conn.cursor()

   nrow = 0
   for row in c.execute('SELECT * FROM {tn}'.format(tn=tabname)):
      nrow = nrow + 1
   print("Number of rows: {0}".format(nrow))
