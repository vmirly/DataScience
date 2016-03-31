import sys
import os
sys.path.append("lib/")
import Pylibdb
import re


def get_dbinfo(dbinfo):
    with open(dbinfo, "r") as fp:
       for line in fp:
           line = line.strip().split(" ")
           if line[0] == "host_name":
               host_name = line[1]
           elif line[0] == "db_name":
               db_name = line[1]
           elif line[0] == "user_name":
               user_name = line[1]
           elif line[0] == "password":
               password = line[1]

    return (host_name, db_name, user_name, password)

def get_SQL_connection(db_name, host_name, user_name, password):
    conn = Pylibdb.connect(dbname   = db_name, 
                           hostname = host_name, 
                           username = user_name,
                           psswd    = password)
    cursor = conn.cursor()
    return(conn, cursor)


def read_tablefile(filename, cursor):
    with open(filename, "r") as fp:
       table_name = fp.readline().strip()

       attribs = fp.readline().strip()
       attribs = re.sub(' +', ' ', attribs)
       attrib_list = attribs.strip().split(" ")
       cursor.execute('DROP TABLE IF EXISTS ' + table_name)

       typline = fp.readline()
       typline = re.sub(' +', ' ', typline)
       typ_list = typline.strip().split(" ")

       keyline = fp.readline().strip()

       n_col = len(attrib_list)

       commstr='CREATE TABLE ' + table_name + ' ( '
       for i in range(n_col):
           commstr += attrib_list[i] + ' ' + typ_list[i]
           if i != n_col-1:
               commstr += ', '
           else:
               commstr += ', ' + keyline + ')'
 
       print(commstr)
       cursor.execute(commstr)

       col_names = re.sub(' ', ',', attribs)
       val_placeholder = ''
       for i in range(n_col):
           val_placeholder += '%s'
           if i != n_col-1:
               val_placeholder += ','
       print(col_names)
       insert_string = 'INSERT INTO ' + table_name + ' ( ' + col_names + ' ) VALUES ( ' + val_placeholder + ' )'
       print(insert_string)
       for line in fp:
           line = re.sub(' +', ' ', line)
           line = line.strip().split(" ")
           cursor.execute(insert_string, line)
           print(line)
           #print(len(line))


def main():
    assert len(sys.argv) == 3
    assert os.path.exists(sys.argv[1]) == 1
    host, dbname, username, passwd = get_dbinfo(sys.argv[1])
    print (dbname, host, username, passwd)
    conn, cursor = get_SQL_connection(dbname, host, username, passwd)
    read_tablefile(sys.argv[2], cursor)
    assert os.path.exists(sys.argv[2]) == 1
    cursor.close()
    conn.commit()
    conn.close()

if __name__ == "__main__":
    main()
