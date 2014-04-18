Data-Science
===========


Raw data -> Processing script -> tidy data -> data analysis -> data communication

<h2>Getting and Cleaning the Data</h2>

Sources of data
<ul>
<li> APIs: twitter, ...</li>
<li> data.baltimorecity.gov </li>

</ul>


<h3> R commands: Getting data</h3>

```
file.exists("somefile")
dir.create("newdirectory")

if (!file.exists("data")) {
  dir.create("date")
}

download.file(url, destfile, method)
```

method: for https on mac use "curl"

<b> Data-Science Tip: </b> always save the date that the file is downloaded
```
date.of.download <- date()
```

Reading local files:
```
df <- read.table("./data/data.csv", sep=",", header=TRUE)

read.csv("  ")

library(xlsx)
read.xlsx(" ")
```

options:
```
quote ==> to tell R whether there are any quoted values
na.strings ==> set the charcater that represents the missing values
nrows ==> howe many rows to read 
skip  ==> number of lines to skip before starting to read
```

<h4> Reading XML files </h4>

XML:

 start tags <section>

 end tags   </section>

 empty tags   </line-break />

Elements:
 <greeeting> Heello Worls </greetin>
