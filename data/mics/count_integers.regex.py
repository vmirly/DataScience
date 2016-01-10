import re
import sys

def main():
   if len(sys.argv)>1:
      x = 0
      fp = open(sys.argv[1])
      for line in fp:
         numbers = re.findall('[0-9]+', line)
         for n in numbers:
            x += int(n)
      
      fp.close()
      print(x)
   else:
      exit()

if __name__ == "__main__":
    main()
