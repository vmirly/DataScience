Data-Science
===========

Links to ipython notebooks: 
 
  <a href="http://nbviewer.ipython.org/github/mirjalil/DataScience/blob/master/R_Programming.ipynb"> R-Programming Reference</a>
  
  <a href="http://nbviewer.ipython.org/github/mirjalil/DataScience/blob/master/R_gettingData.ipynb"> R-Getting and Cleaning Data </a>

# Intro to Data Science 

The types of questions that data science tries to answer includes

* Descriptive
* Exploratory
* Inferential
* Predictive
* Causal
* Mechanistic

### Descriptive analysis:
 Goal: Describe a set of data. For example census data. 
 Without trying to predict any variable.

### Exploratory analysis
 Goal: Find relationships you didn't know about.

### Inferential analysis
 Goal: Use a small sample of data to say something about a bigger population
 Inference is commonly the goal of statistical analysis
 
### Predictive analysis
 Goal: To use data on some objects to predict values for another objects

### Causal analysis
 Goal: To find out what happens to one variable when you make changes to another variable
 
### Mechanistic analysis
 Goal: Understant the exact changes in variabes that lead to changes in other variable for individual objects



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

<ul>
<li> start tags \<section\> </li>
<li> end tags   \</section\> </li>
<li> empty tags   \</line-break /\> </li>
</ul>

Elements:
 \<greeeting\> Hello Worls \</greetin\>

Attribute: components of the label
 \<img src="" alt="instructor" /\>


```
library(xml)

fileUrl <- "http://www.w3schools.com/xml/simple.xml"
doc <- xmlTreeParse(fileUrl, useInternal=TRUE)

rootNode <- xmlRoot(doc)
xmlName(rootNode)

names(rootNode)

rootNode[[1]]

rootNode[[1]][[1]]

xmlSApply(rootNode, xmlvalue)

``` 

XPath:

<ul>
<li> /npde : top level node </li>
<li> //node : node at any level </li>
<li> node[@attr-name] : node with an attribute name </li>
<li> node[@attr-name='bob']  </li>
</ul>

```
xpathSApply(rootNode, "//name", xmlValue)

xpathSApply(rootNode, "//price", xmlValue)
```

Example:
```
# ESPN xml
fileUrl.espn <- "http://espn.go.com/nfl/team/_/name/bal/baltimore-ravens" 

doc.espn <- htmlTreeParse(fileUrl.espn, useInternal=TRUE)
scores.espn <- xpathSApply(doc.espn, "//li[@class='score']", xmlValue)
teams.espn <- xpathSApply(doc.espn, "//li[@class='team-name']", xmlValue)

```

<h4> Reading JSON >/h4>

Common format for data from application programmin interfaces (APIs)

```
library(jsonlite)

jsonData <- fromJSON("https://api.github.com/users/jtleek/repos")
names(jsonData)

names(jsonData$owner)

jsonData$owner$login

```

Writing (converting) data.frames to json format:
```
myjson <- toJSON(iris, pretty=TRUE)
cat(myjson)
```
convert back to data.frame:
```
iris2 <- fromJSON(myjson)
head(iris2)
```

<h3> Package data.table </h3>

Faster version of data.frame

```
library(data.table)

DF = data.frame(x=rnorm(9), y=rep(c("a","b","c"),each=3), z=rnorm(9))
head(DF,3)

DT = data.table(x=rnorm(9), y=rep(c("a","b","c"),each=3), z=rnorm(9))
head(DT,3)

tables()

DT[2,]

DT[DT$y=="a",]

#subsetting is based on rows:
DT[c(2,3)]

#subset columns is diifenet than data.frame
DT[,c(2,3)]

DT[,list(mean(x), sum(z))]

# to add a new column:
DT[,w:=z^2]

DT2 <- DT
DT[,y:=2] # this will also affect DT2

## Multiple operations
DT[,m:= {tmp <- (x+z); log2(tmp+5)}] #multistep operation

DT[,a:=x>0]

# mean of x+w group by a:
DT[, b:=mean(x+w), by=a]


## Keys:
DT <- data.table(x=rep(c("a","b","c"),each=100), y=rnorm(300))
setkey(DT, x)
DT['a']

DT1 <- data.table(x=c('a','a','b','dt1'), y=1:4)
DT2 <- data.table(x=c('a','b','dt2'), z=5:7)
setkey(DT1, x)
setkey(DT2, x)
merge(DT1, DT2)

```

tables() ==> shows all the data.tables in the memory, and their name, nrows, ..

Fast Reading:
```
big_df <- data.frame(x=rnorm(1E6), y=rnorm(1E6))

file <- tempfile()
write.table(big_df, file=file, row.names=FALSE, col.names=TRUE, sep="\t", quote=FALSE)

system.time(fread(file))

system.time(read.table(file, header=TRUE, sep="\t"))

```

<b>fread </b>is much faster than read.table 

