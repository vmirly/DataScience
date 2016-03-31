import sqlite3

def create_db(dbname="example.db"):
    """ Function to create a new SQLite database"""
    # make a connection
    conn = sqlite3.connect(dbname)
    c = conn.cursor()
    
    # Create table
    c.execute('''CREATE TABLE stocks
             (date text, trans text, symbol text, qty real, price real)''')
    
    # Insert a row of data
    c.execute("INSERT INTO stocks VALUES ('2006-01-05','BUY','RHAT',100,35.14)")
    
    # Save (commit) the changes
    conn.commit()
    
    conn.close()
