import sys
sys.path.append("lib/")
import Pylibdb
import re


def get_dbinfo():
    with open("/home/vahid/Desktop/fuzzydb.pass", "r") as fp:
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


def read_simtable_textfile(filename, cursor):
    with open(filename, "r") as fp:
       first = fp.readline()
       first = re.sub(' +', ' ', first)
       first = first.strip().split(" ")
       cursor.execute('DROP TABLE IF EXISTS simtable')
       str='CREATE TABLE simtable ( '
       str += first[0] + ' VARCHAR(20), '
       for i in range(1, len(first)):
           str = str + first[i] + ' real'
           if i < len(first)-1:
               str = str + ', '
           else:
               str = str + ');'
       #print(str)
       cursor.execute(str)
       
       for line in fp:
           str = 'INSERT INTO simtable ( '
           for s in first[0:len(first)-1]:
               str += s + ','
           str += first[len(first)-1] + ') VALUES ('

           line = re.sub(' +', ' ', line)
           line = line.strip().split(" ")

           str += '"' + line[0] + '",'
           for s in line[1:len(line)-1]:
              str += s + ','
           str += line[len(line)-1] + ');'
           print (str)
           cursor.execute(str)
           #print(len(line))


def main():
    host, dbname, username, passwd = get_dbinfo()
    print (dbname, host, username, passwd)
    conn, cursor = get_SQL_connection(dbname, host, username, passwd)
    read_simtable_textfile("data/district.similarity.txt", cursor)
    cursor.close()
    conn.close()

if __name__ == "__main__":
    main()
