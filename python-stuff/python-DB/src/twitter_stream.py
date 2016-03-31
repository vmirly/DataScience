import sys
import twitter
import json
#import oauth2 as oauth

States = ('AL', 'AK', 'AZ', 'AR', 'CA', 'CO', 'CT', 'DE', 'DC', 'FL', 'GA', 'HI', 'ID', 'IL', 'IN', 'IA', 'KS', 'KY', 'LA', 'ME', 'MD', 'MA', 'MI', 'MN', 'MS', 'MO', 'MT', 'NE', 'NV', 'NH', 'NJ', 'NM', 'NY', 'NV', 'ND', 'OH', 'OK', 'OR', 'PA', 'RI', 'SC', 'SD', 'TN', 'TX', 'UT', 'VT', 'VA', 'WA', 'WV', 'WI', 'WY')

def getApiKeys(json_file):
    """
      Get the API keys from input file
    """
    with open(json_file) as jf:
       data = json.load(jf)
    #for k in data.keys():
    #   val = data[k]
    return(data)  


sys.path.append("lib/")
import Pylibdb


def get_SQL_connection():
    conn = Pylibdb.connect()
    cursor = conn.cursor()
    return(conn, cursor)


def get_SQL_table():
    conn, cursor = get_SQL_connection()
    cursor.execute("SELECT state,id FROM twitter")
    allrows = cursor.fetchall()
    return(allrows)

def main():

    conn, cursor = get_SQL_connection()
#    cursor.execute('DROP TABLE twitter')
    try:
       cursor.execute("CREATE TABLE twitter (id INT UNSIGNED NOT NULL AUTO_INCREMENT, at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, user_id CHAR(20), state CHAR(2), city VARCHAR(30), tweet VARCHAR(140), PRIMARY KEY (id))")
    except:
       print("Table already exists")
    

    token_dict = getApiKeys(sys.argv[1])

    tw_stream = twitter.TwitterStream(auth=twitter.OAuth(
                     token_dict['access_token_key'], 
                     token_dict['access_token_secret'],
                     token_dict['consumer_key'],
                     token_dict['consumer_secret']))

    tw_iterator = tw_stream.statuses.sample()


    insert_string = "INSERT INTO twitter (user_id,state,city,tweet) VALUES (%s, %s, %s, %s)"

    i = 1
    for tw in tw_iterator:
       tw_userid, tw_text, tw_lang, tw_country, tw_state, tw_city = '', '', '', '', '', ''
       try:
          tw_userid = tw['id_str']
          tw_text =  tw['text']
          tw_lang =  tw['lang']
          tw_place = tw['place']
          if tw_text and tw_place and tw_lang == 'en':
             tw_country = tw_place['country']
             if tw_country == 'United States':
                tw_fullname = tw_place['full_name']
                tw_location = tw_fullname.split()
                for s in tw_location:
                   if s in States:
                      tw_state = s
                      tw_city = tw_place['name']
                      if tw_city:
                         data = (tw_userid, tw_state, tw_city, tw_text)
                         print (i, tw_state, tw_city, tw_text)
                         cursor.execute(insert_string, data)
                         i = i + 1
                         break
       except:
          continue

       if i%10 == 0:
           cursor.close()
           conn.commit()
           conn.close()

           print("Total size of Twitter table: {0}".format(len(get_SQL_table())))

           if i==20:
               break
           else:
               conn, cursor = get_SQL_connection()



if __name__=="__main__":
    main()

