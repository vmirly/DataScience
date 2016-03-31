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
    """ Start a connection to a database given usename, password
    """
    conn = Pylibdb.connect(dbname   = db_name, 
                           hostname = host_name, 
                           username = user_name,
                           psswd    = password)
    cursor = conn.cursor()
    return(conn, cursor)

def membership(A, x):
    """ Calculates the membershib degree of x in set A
    returns A(x)
    """ 
    a, b, c, d = A
    assert b>=a and c>=b and d>=c
    if x < a or x > d:
       return 0.0
    elif x>a and x<b:
       return (x-a)/float(b-a)
    elif x>=b and x<=c:
       return 1.0
    else:
       return (d-x)/float(d-c)

def frange(x, y, step=1):
    while x<y:
       yield x
       x += step

def fuzzy_CDEG_FEQ(A, B):
    """ Calculates compatibility degree among fuzzy attributes of type 1&2
    for possibility fuzzy equility comparison
    """
    if A[3]<B[0] or A[0]>B[3]:
        return 0
    elif B[0] == B[3]:
       if A[0] == A[3]:
           return 1
       else:
           return 0
    else:
        if A[3]>B[0]:
            start = B[0]
            end = A[3]
        else:
            start = A[0]
            end = B[3]
        vmax = 0.0
        for x in frange(start, end, (end-start)/10):
            mem_A = membership(A, x)
            mem_B = membership(B, x)
            #print(x, mem_A, mem_B)
            vmax = max(min(mem_A, mem_B), vmax)
        return vmax

def fuzzy_CDEG_NFEQ(A, B):
    """ Calculates compatibility degree among fuzzy attributes of type 1&2
    for necessity fuzzy equility comparison
    """
    if A[3]<B[0] or A[0]>B[3]:
        return 0
    elif B[0] == B[3]:
       if A[0] == A[3]:
           return 1
       else:
           return 0
    else:
        if A[3]>B[0]:
            start = B[0]
            end = A[3]
        else:
            start = A[0]
            end = B[3]
        vmin = 1.0
        for x in frange(start, end, (end-start)/10):
            mem_A = membership(A, x)
            mem_B = membership(B, x)
            #print(x, mem_A, mem_B)
            vmin = min(max(1-mem_A, mem_B), vmin)
        return vmin

def fuzzy_CDEG_FGT(A, B):
    """ Calculates compatibility degree among fuzzy attributes of type 1&2
    for greater.than comparison
    """
    if A[2] >= B[3]:
        return 1.0
    elif A[2]<B[3] and A[3]>B[2]:
        return (A[3] - B[2]) / ((B[3]-B[2]) - (A[2]-A[3]))
    else:
        return 0.0


def fuzzy_CDEG_Typ3_FEQ(A_dict, B_dict, distrct_sim):
    """ Calculates the compatibility degree for fuzzy attributes of type 3
    Input arguments are three dictionaries 
    two comparison distruct options + district_similarity.
    """
    vmax = 0.0
    for ka,va in A_dict.iteritems():
        for kb,vb in B_dict.iteritems():
            simVal = distrct_sim[(ka, kb)]
            #print (ki, kj, simVal)
            vmax = max(simVal*va*vb, vmax)
    return(vmax)


def process_selcommand(selcomm, cur, dsim):
    """ Process the select command input bu user
    divides the command into price and district subcommands (if exists)
    """
    cond_price, cond_distrct = 0, 0
    thresh_price, thresh_distrct, thresh = 0.0, 0.0, 0.1
    if ' price ' in selcomm:
        start_inx = selcomm.find(' price ')
        last_inx = len(selcomm)
        if ' AND ' in selcomm:
            last_inx = selcomm.find(' AND')
            if start_inx > last_inx:
                last_inx = len(selcomm)
        subcomm = selcomm[start_inx : last_inx].lstrip()
        print(subcomm)
        if ' FEQ ' in subcomm:
            cond_price = 1
        elif ' NFEQ ' in subcomm:
            cond_price = 2
        elif ' FLT ' in subcomm:
            cond_price = 3
        #price_range = re.sub(' +', ' ', price_range)
        #print(price_range)
        price_range = subcomm.split(' ')
        B = [float(price_range[2]), float(price_range[3]),
             float(price_range[4]), float(price_range[5])]
        if len(price_range)>6:
            try:
                thresh_price = float(price_range[6])
            except:
                thresh_price = 0.0
            #print(price_range[6], thresh_price)

    if ' district ' in selcomm:
        start_inx = selcomm.find(' district ')
        last_inx = len(selcomm)
        if ' AND ' in selcomm:
            last_inx = selcomm.find(' AND')
            if start_inx > last_inx:
                last_inx = len(selcomm)
        subcomm = selcomm[start_inx : last_inx].lstrip()
        print(subcomm)

        if ' FEQ ' in subcomm:
            cond_distrct = 1
        elif ' FDIF ' in subcomm:
            cond_distrct = 2

        desired_distrct = subcomm.split(' ')
        B_dict = {}
        B_dict[desired_distrct[2]] = float(desired_distrct[3])
        B_dict[desired_distrct[4]] = float(desired_distrct[5])

        if len(desired_distrct)>6:
            try:
                thresh_distrct = float(desired_distrct[6])
            except:
                thresh_distrct = 0.0
        #print(Bdict)

    if ' thresh ' in selcomm:
        #substr = desired_d
        subcomm = selcomm[selcomm.find('thresh '):].split(' ')
        thresh = float(subcomm[1])

    cur.execute('SELECT * FROM district_table as t1 INNER JOIN price_table as t2 ON t1.id=t2.id')
    rows = cur.fetchall()
    selrows = []
    for r in rows:
        #print(r)
        A_dict = {r[1]:float(r[2]), r[3]:float(r[4])}
        cdeg_distrct, cdeg_price = 1.0, 1.0
        if cond_distrct > 0:
            cdeg_distrct = fuzzy_CDEG_Typ3_FEQ(A_dict, B_dict, dsim)
            if cond_distrct == 2:
               cdeg_distrct = 1 - cdeg_distrct

            if cdeg_distrct < thresh_distrct:
               cdeg_distrct = 0.0

        if cond_price > 0:
               A = r[6:10]
               if cond_price == 1:
                   cdeg_price = fuzzy_CDEG_FEQ(A, B)
               elif cond_price == 2:
                   cdeg_price = fuzzy_CDEG_NFEQ(A, B)
               elif cond_price == 3:
                   cdeg_price = fuzzy_CDEG_FGT(B, A)

               if cdeg_price < thresh_price:
                   cdeg_price = 0.0
               #print(A, B, cdeg_price, thresh_price)
        cdeg = min(cdeg_price, cdeg_distrct)
        if cdeg >= thresh:
            selrows.append(int(r[0]))

    return(selrows)


def get_similarity(cur):
    """ Read the similarity table stored in the database,
    and sotr it in a dictionary
    """
    cur.execute("SHOW COLUMNS FROM district_similarity")
    rows = cur.fetchall()
    colnames = []
    for r in rows:
       colnames.append(r[0])
    cur.execute("SELECT * FROM district_similarity")
    rows = cur.fetchall()
    dsim = {}
    for r in rows:
       nelem = len(r)
       for (j,col) in zip(range(1,nelem), r[1:]):
           dsim[r[0],colnames[j]] =  col
    return(dsim)


######################################################
def main():
    host, dbname, username, passwd = get_dbinfo()
    print (dbname, host, username, passwd)
    conn, cursor = get_SQL_connection(dbname, host, username, passwd)

    distct_sim = get_similarity(cursor)
    done = False
    while not done:
         selcommand = input('fuzzydb> ')
         selcommand = re.sub(' +', ' ', selcommand)
         print ("   INPUT QUERY:  {0}".format(selcommand))
         if selcommand == 'quit':
             done = True
         else:
             res = process_selcommand(selcommand, cursor, distct_sim)
             for i in res:
                 print("   {0}".format(i))

    cursor.close()
    conn.commit()
    conn.close()

if __name__ == "__main__":
    print(__doc__)
    main()
